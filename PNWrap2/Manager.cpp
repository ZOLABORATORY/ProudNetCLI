#include "stdafx.h"
#include "WrapCCallbackArgs.h"
#include "DbClient.h"
#include "Manager.h"

using namespace Proud;
namespace PNWrap2
{
	Manager::Manager(System::String^ db_cache_server_ip, int db_cache_server_port)
	{
		m_client.Attach(new CDbClient(this));
		Connect(db_cache_server_ip, db_cache_server_port);
		m_leaveServer = false;
	}

	Manager::~Manager()
	{
		m_client.Free();
	}
	
	void Manager::Connect(System::String^ db_cache_server_ip, int db_cache_server_port)
	{
		m_client->RequestCompleteTrue();

		Proud::CDbCacheClient2ConnectParameter p1;
		p1.m_authenticationKey = L"1234";
		p1.m_delegate = this;
		p1.m_serverAddr = msclr::interop::marshal_as<std::wstring>(db_cache_server_ip).c_str();
		p1.m_serverPort = db_cache_server_port;
		if (!m_client->m_DbClient->Connect(p1))
		{
			// DB cache2 Ŭ���� ���� ���� �õ� ����
			// Failed to server connecting of DB cache2 client
			throw Proud::Exception(L"Failed to server connecting of DB cache2 client");
			Connected = false;
		}	
	}

	/************************************************************* override ****************************************************************/

	void Manager::OnJoinDbCacheServerComplete(ErrorInfo *info)
	{
		Connected = true;

		if (info->m_errorType == ErrorType_Ok)
		{
			m_leaveServer = false;
			// Succeed to connect DbCacheServer.
			LogEvent(LoadString(IDS_STRING117));
		}
		else
			// Failed to connect DbCacheServer.
			LogEvent(LoadString(IDS_STRING118));

		m_client->RequestCompleteTrue();
	}

	void Manager::OnLeaveDbCacheServer(ErrorType reason)
	{
		m_leaveServer = true;
	}

	void Manager::OnDbmsWriteDone(DbmsWritePropNodePendType type, Proud::Guid loadedDataGuid)
	{
		// ���� �ð��� �ѹ��� cache�������� DB�� �����͸� �Է��ϸ� ���� �Ǵ� �̺�Ʈ �Դϴ�.
		// �� �̺�Ʈ ����� ������ cache�� ������ �ִٸ� ���� �ð� �� Db�� ������ �Ŀ� �̺�Ʈ�� �߻��˴ϴ�.
		// Receiving event when enter data to DB from cache server every specific time.
		// Apart from each event, if cache has changed then event occur after saving to DB.
		m_lastWriteDoneGuid = loadedDataGuid;

		LogEvent(L"OnDbmsWriteDone");

		String strType = Proud::TypeToString(type);

		// "Client : Dbms�� Write�� �����߽��ϴ�. HostID : %d Ÿ�� : %s, Guid : %s "
		// "Client : Succeed to Write at Dbms. HostID : %d Type : %s, Guid : %s "
		String text;
		text.Format(LoadString(IDS_STRING103),
			(int)m_client->m_DbClient->GetLocalHostID(), String((LPCWSTR)strType), String((LPCWSTR)loadedDataGuid.ToString()));
		LogEvent(text.GetString());
	}

	void Manager::OnExclusiveLoadDataComplete(CCallbackArgs& args)
	{
		for (int i = 0; i < args.m_items.GetCount(); ++i)
		{
			if (args.m_items[i].m_reason == ErrorType_Ok)
			{
				LogEvent(LoadString(IDS_STRING116) + L" : OnExclusiveLoadData");

				m_client->m_data = args.m_items[i].m_loadedData; // ������ �ֽ�ȭ // Data renewal
				m_client->m_SessionGuid = args.m_items[i].m_sessionGuid;

				if (!m_client->m_data)
				{
					// Guid�� �߸��Ǿ� ���ϴ�.
					// Wrong Guid.
					LogError(LoadString(IDS_STRING105));
					m_client->m_DbClient->UnloadDataBySessionGuid(args.m_items[i].m_sessionGuid);
					return;
				}

				// "�ε� ��û ��� ��� ����"
				// "Succeed to wait loading request result"
				LogEvent(LoadString(IDS_STRING106));

				// Request���� ��� �ݵ�� ������ ���� ���� Ȯ���� �Ŀ� ó�� �մϴ�.
				// If it is Request type then process it once check about receiving request.
				m_client->RequestCompleteTrue();
			}
			else
			{
				m_client->RequestCompleteTrue();
				LogEvent(LoadString(IDS_STRING113) + L" : OnExclusiveLoadData");

				// "���� ������ �ε� ����! ����: "	
				// "Failed exclusive data loading! Reason: "	
				LogError(LoadString(IDS_STRING104) + ErrorInfo::TypeToString(args.m_items[i].m_reason));
			}
		}

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		//cc->comment = "OnExclusiveLoadDataCompleted!!!";
		if (NULL != callbacks::When_OnExclusiveLoadDataComplete) callbacks::When_OnExclusiveLoadDataComplete(cc);
	}

	void Manager::OnDataUnloadRequested(CCallbackArgs& args)
	{
		LogEvent(L"OnDataUnload");
		m_client->m_data = args.m_items[0].m_loadedData; // ������ �ֽ�ȭ // Data renewal

														 // Request���� ��� �ݵ�� ������ ���� ���� Ȯ���� �Ŀ� ó�� �մϴ�.
														 // If it is Request type then process it once check about receiving request.
		m_client->RequestCompleteTrue();
		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);		
		if (NULL != callbacks::When_OnDataUnloadRequested) callbacks::When_OnDataUnloadRequested(cc);
	}
	void Manager::OnDataForceUnloaded(CCallbackArgs& args)
	{
		LogEvent(L"OnDataForceUnloaded");
		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnDataForceUnloaded) callbacks::When_OnDataForceUnloaded(cc);
	}

	void Manager::OnAddDataFailed(CCallbackArgs& args)
	{

		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->RequestCompleteTrue();

		// "OnAddData ����. ����:%s �ڸ�Ʈ:%s"
		// "OnAddData failed. Reason:%s Comment:%s"
		String text;
		text.Format(LoadString(IDS_STRING108), ErrorInfo::TypeToString(args.m_items[0].m_reason), args.m_items[0].m_comment);
		LogError(text.GetString());

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnAddDataFailed) callbacks::When_OnAddDataFailed(cc);
	}

	void Manager::OnAddDataSuccess(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->m_data = args.m_items[0].m_loadedData;

		// TypeName���� �빮�ڷ� ���ɴϴ�.
		// TypeName value enteringt as upper case.
		if (!args.m_items[0].m_data->GetStringTypeName().Compare(L"HERO"))
		{
			m_client->m_heroGuid = args.m_items[0].m_data->UUID;
		}
		else if (!args.m_items[0].m_data->GetStringTypeName().Compare(L"ITEM"))
		{
			m_client->m_itemGuid = args.m_items[0].m_data->UUID;
		}
		else if (!args.m_items[0].m_data->GetStringTypeName().Compare(L"FRIEND"))
		{
			m_client->m_friendGuid = args.m_items[0].m_data->UUID;
		}

		// Request���� ��� �ݵ�� ������ ���� ���� Ȯ���� �Ŀ� ó�� �մϴ�.
		// If it is Request type then process it once check about receiving request.
		m_client->RequestCompleteTrue();
		LogEvent(LoadString(IDS_STRING116) + L" : AddData");

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnAddDataSuccess) callbacks::When_OnAddDataSuccess(cc);
	}

	void Manager::OnUpdateDataFailed(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}
		// Request���� ��� �ݵ�� ������ ���� ���� Ȯ���� �Ŀ� ó�� �մϴ�.
		// If it is Request type then process it once check about receiving request.
		m_client->RequestCompleteTrue();

		String text;
		text.Format(L"%s : UpdateData - %s:%s Comment:%s", LoadString(IDS_STRING113), LoadString(IDS_STRING120), ErrorInfo::TypeToString(args.m_items[0].m_reason), args.m_items[0].m_comment);
		LogError(text.GetString());

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnUpdateDataFailed) callbacks::When_OnUpdateDataFailed(cc);
	}

	void Manager::OnUpdateDataSuccess(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->m_data = args.m_items[0].m_loadedData; // ������ �ֽ�ȭ // Data renewal

														 // Request���� ��� �ݵ�� ������ ���� ���� Ȯ���� �Ŀ� ó�� �մϴ�.
														 // If it is Request type then process it once check about receiving request.
		m_client->RequestCompleteTrue();


		LogEvent(LoadString(IDS_STRING116) + L" : UpdateData ");

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnUpdateDataSuccess) callbacks::When_OnUpdateDataSuccess(cc);
	}

	void Manager::OnRemoveDataFailed(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		// Request���� ��� �ݵ�� ������ ���� ���� Ȯ���� �Ŀ� ó�� �մϴ�.
		// If it is Request type then process it once check about receiving request.
		m_client->RequestCompleteTrue();

		String text;
		text.Format(L"%s : RemoveData - %s:%s Comment:%s", LoadString(IDS_STRING113), LoadString(IDS_STRING120), ErrorInfo::TypeToString(args.m_items[0].m_reason), args.m_items[0].m_comment);
		LogError(text.GetString());

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnRemoveDataFailed) callbacks::When_OnRemoveDataFailed(cc);
	}

	void Manager::OnRemoveDataSuccess(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->m_data = args.m_items[0].m_loadedData; // ������ �ֽ�ȭ // Data renewal

														 // Request���� ��� �ݵ�� ������ ���� ���� Ȯ���� �Ŀ� ó�� �մϴ�.
														 // If it is Request type then process it once check about receiving request.
		m_client->RequestCompleteTrue();

		LogEvent(LoadString(IDS_STRING116) + L"RemoveData");

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnRemoveDataSuccess) callbacks::When_OnRemoveDataSuccess(cc);
	}

	void Manager::OnException(const Proud::Exception &e)
	{
		String str;
		str.Format(L"Exception! %s: %s", LoadString(IDS_STRING120), e.what());
		LogError(str.GetString());
	}

	void Manager::OnWarning(ErrorInfo *errorInfo)
	{
		Proud::String s;
		s.Format(L"Warning! %s: %s", LoadString(IDS_STRING120), errorInfo->ToString());
		LogError(s.GetString());
	}

	void Manager::OnError(ErrorInfo *errorInfo)
	{
		Proud::String s;
		s.Format(L"Error! %s: %s", LoadString(IDS_STRING120), errorInfo->ToString());
		LogError(s.GetString());
	}

	void Manager::OnAccessError(CCallbackArgs& args)
	{
		Proud::String s;
		s.Format(L"AccessError! Comment: %s", args.m_items[0].m_comment);
		LogError(s.GetString());
	}

	/************* NonExclusive ***************/

	// void DBCacheClient::OnNonExclusiveSnapshotDataFailed( CCallbackArgs& args )
	// {
	// 	if(m_client->m_diffCustomArg != args.m_tag)
	// 	{
	// 		// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
	// 		// "Waiting ticket does not match. It is wrong setting or server error."
	// 		LogError(LoadString(IDS_STRING107));
	// 	}
	// 	
	// 	m_client->RequestCompleteTrue();
	// 	
	// 	// "���� �ε� ������ ����. ����:  "
	// 	// "Failed unexclusive load snapshot. Reason:  "
	// 	LogError(LoadString(IDS_STRING109) + ErrorInfo::TypeToString(args.m_reason));
	// }
	// 
	// void DBCacheClient::OnNonExclusiveSnapshotDataSuccess(CCallbackArgs& args )
	// {
	// 	if(m_client->m_diffCustomArg != args.m_tag)
	// 	{
	// 		// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
	// 		// "Waiting ticket does not match. It is wrong setting or server error."
	// 		CStringW logString;
	// 		logString.LoadStringW(IDS_STRING107);
	// 		LogError(logString);
	// 	}
	// 	
	// 	m_client->m_data = args.m_loadedData;
	// 
	// 	m_client->RequestCompleteTrue();
	// 
	// 	// "���� �ε� ������ ����!"
	// 	// "Succeed unexclusive load snapshot!"
	// 	LogEvent(LoadString(IDS_STRING110));
	// }

	void Manager::OnNonExclusiveSnapshotDataComplete(CCallbackArgs& args)
	{
		for (int i = 0; i < args.m_items.GetCount(); ++i)
		{
			if (args.m_items[i].m_reason == ErrorType_Ok)
			{
				if (m_client->m_diffCustomArg != args.m_tag)
				{
					// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
					// "Waiting ticket does not match. It is wrong setting or server error."
					CStringW logString;
					logString.LoadStringW(IDS_STRING107);
					LogError(logString);
				}

				m_client->m_data = args.m_items[i].m_loadedData;

				m_client->RequestCompleteTrue();

				// "���� �ε� ������ ����!"
				// "Succeed unexclusive load snapshot!"
				LogEvent(LoadString(IDS_STRING110));
			}
			else
			{
				if (m_client->m_diffCustomArg != args.m_tag)
				{
					// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
					// "Waiting ticket does not match. It is wrong setting or server error."
					LogError(LoadString(IDS_STRING107));
				}

				m_client->RequestCompleteTrue();

				// "���� �ε� ������ ����. ����:  "
				// "Failed unexclusive load snapshot. Reason:  "
				LogError(LoadString(IDS_STRING109) + ErrorInfo::TypeToString(args.m_items[i].m_reason));
			}
		}
	}

	// �Ʒ��� ���ܼ� �̺�Ʈ ���� args.m_loadedData���� ���� �ʽ��ϴ�.
	// �Ʒ��� ���ܼ� �̺�Ʈ������ args.m_loadedData�� NULL �̸�, args.m_data���� �����մϴ�.
	// Following snapshot events do not provide args.m_loadedData value.
	// args.m_loadedData of following snapshot event is NULL and only support args.m_data.
	void Manager::OnNonExclusiveAddDataAck(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
			return;
		}

		if (args.m_items[0].m_reason != ErrorType_Ok)
		{
			String text;
			text.Format(L"%s : NonExclusiveAddData - %s", LoadString(IDS_STRING113), args.m_items[0].m_comment);
			LogError(text.GetString());
			return;
		}
		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnNonExclusiveAddDataAck) callbacks::When_OnNonExclusiveAddDataAck(cc);
	}

	void Manager::OnNonExclusiveRemoveDataAck(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->RequestCompleteTrue();

		if (args.m_items[0].m_reason != ErrorType_Ok)
		{
			CStringW txt;
			txt.Format(L"%s : NonExclusiveRemoveData - %s", LoadString(IDS_STRING113), args.m_items[0].m_comment);
			LogError(txt.GetString());
		}

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnNonExclusiveRemoveDataAck) callbacks::When_OnNonExclusiveRemoveDataAck(cc);
	}

	void Manager::OnNonExclusiveModifyValueSuccess(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->RequestCompleteTrue();

		if (args.m_items[0].m_reason != ErrorType_Ok)
		{
			CStringW txt;
			txt.Format(L"%s : NonExclusiveModifyValue - %s", LoadString(IDS_STRING113), args.m_items[0].m_comment);
			LogError(txt.GetString());
		}

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnNonExclusiveModifyValueSuccess) callbacks::When_OnNonExclusiveModifyValueSuccess(cc);
	}

	void Manager::OnNonExclusiveModifyValueFailed(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->RequestCompleteTrue();

		if (args.m_items[0].m_reason != ErrorType_Ok)
		{
			CStringW txt;
			txt.Format(L"%s : NonExclusiveModifyValue - %s", LoadString(IDS_STRING113), args.m_items[0].m_comment);
			LogError(txt.GetString());
		}

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnNonExclusiveModifyValueFailed) callbacks::When_OnNonExclusiveModifyValueFailed(cc);
	}

	void Manager::OnNonExclusiveSetValueIfSuccess(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->RequestCompleteTrue();

		if (args.m_items[0].m_reason != ErrorType_Ok)
		{
			CStringW txt;
			txt.Format(L"%s : NonExclusiveSetValue - %s", LoadString(IDS_STRING113), args.m_items[0].m_comment);
			LogError(txt.GetString());
		}

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnNonExclusiveSetValueIfSuccess) callbacks::When_OnNonExclusiveSetValueIfSuccess(cc);
	}

	void Manager::OnNonExclusiveSetValueIfFailed(CCallbackArgs& args)
	{
		if (m_client->m_diffCustomArg != args.m_tag)
		{
			// "���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�."
			// "Waiting ticket does not match. It is wrong setting or server error."
			LogError(LoadString(IDS_STRING107));
		}

		m_client->RequestCompleteTrue();

		if (args.m_items[0].m_reason != ErrorType_Ok)
		{
			CStringW txt;
			txt.Format(L"%s : NonExclusiveSetValue - %s", LoadString(IDS_STRING113), args.m_items[0].m_comment);
			LogError(txt.GetString());
		}

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		if (NULL != callbacks::When_OnNonExclusiveSetValueIfFailed) callbacks::When_OnNonExclusiveSetValueIfFailed(cc);
	}

	// ���� �̺�Ʈ ���� �ε��ϰ� �ִ� Client���� �߻��˴ϴ�.
	// It occurs to Client who does exclusive loading of following event.
	void Manager::OnSomeoneAddData(CCallbackArgs& args)
	{
		m_client->m_data = args.m_items[0].m_loadedData;

		// TypeName���� �빮�ڷ� ���ɴϴ�.
		// TypeName value receive as upper case.
		if (!args.m_items[0].m_data->GetStringTypeName().Compare(L"HERO"))
		{
			m_client->m_heroGuid = args.m_items[0].m_data->UUID;
		}
		else if (!args.m_items[0].m_data->GetStringTypeName().Compare(L"ITEM"))
		{
			m_client->m_itemGuid = args.m_items[0].m_data->UUID;
		}
		else if (!args.m_items[0].m_data->GetStringTypeName().Compare(L"FRIEND"))
		{
			m_client->m_friendGuid = args.m_items[0].m_data->UUID;
		}

		m_client->RequestCompleteTrue();

		LogEvent(L"SomeoneAddData ack");

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		RunDelegate(callbacks::When_OnSomeoneAddData, cc);
	}

	void Manager::OnSomeoneRemoveData(CCallbackArgs& args)
	{
		m_client->m_data = args.m_items[0].m_loadedData;

		m_client->RequestCompleteTrue();

		LogEvent(L"SomeoneRemoveData ack");

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		RunDelegate(callbacks::When_OnSomeoneRemoveData, cc);
	}

	void Manager::OnSomeoneModifyValue(CCallbackArgs& args)
	{
		m_client->m_data = args.m_items[0].m_loadedData;

		m_client->RequestCompleteTrue();

		LogEvent(L"SomeoneModifyValue ack");

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		RunDelegate(callbacks::When_OnSomeoneModifyValue, cc);
	}

	void Manager::OnSomeoneSetValue(CCallbackArgs& args)
	{
		m_client->m_data = args.m_items[0].m_loadedData;

		m_client->RequestCompleteTrue();

		LogEvent(L"SomeoneSetValue ack");

		WrapCCallBackArgs^ cc = gcnew WrapCCallBackArgs(args);
		RunDelegate(callbacks::When_OnSomeoneSetValue, cc);
	}


	/*************************************************************** LOG ******************************************************************/
	void Manager::LogEvent(CStringW text)
	{
		CriticalSectionLock TRLock(m_CSLogLock, true);

		String logString;
		logString.Format(L"[Info] %s", text);
		m_LogMsgList.AddTail(logString);

		//���� �α׸� ����� ����
		//PostMessage(MESSAGE_LOG, NULL, NULL);
		return;
	}

	void Manager::LogError(CStringW text)
	{
		CriticalSectionLock TRLock(m_CSLogLock, true);

		String logString;
		logString.Format(L"[Info] %s", text);
		m_LogMsgList.AddTail(logString);

		//���� �α׸� ����� ����
		//PostMessage(MESSAGE_LOG, NULL, NULL);
		return;
	}

	CStringW Manager::LoadString(int stringResourceNum)
	{
		switch (stringResourceNum)
		{
		case IDS_ABOUTBOX: return L"SimpleDB2Client ����(&A)...";
		case IDS_STRING102: return L"DB cache2 Ŭ���� ���� ���� �õ� ����";
		case IDS_STRING103: return L"Client : Dbms�� Write�� �����߽��ϴ�. HostID : %d Ÿ�� : %s, Guid : %s ";
		case IDS_STRING104: return L"���� ������ �ε� ����! ����: ";
		case IDS_STRING105: return L"Guid�� �߸��Ǿ� ���ϴ�.";
		case IDS_STRING106: return L"�ε� ��û ��� ��� ����";
		case IDS_STRING107: return L"���ǥ�� ���� �ʽ��ϴ�. ������ �߸��Ǿ��ų� ���� �����Դϴ�.";
		case IDS_STRING108: return L"OnAddData ����. ����:%s �ڸ�Ʈ:%s";
		case IDS_STRING109: return L"���� �ε� ������ ����. ����:  ";
		case IDS_STRING110: return L"���� �ε� ������ ����!";
		case IDS_STRING111: return L"Root ������ Add&�ε� ��û";
		case IDS_STRING112: return L"ȣ��";
		case IDS_STRING113: return L"����";
		case IDS_STRING114: return L"���� ����";
		case IDS_STRING115: return L"UUID ������ �߸��Ǿ����ϴ�.";
		case IDS_STRING116: return L"����";
		case IDS_STRING117: return L"DbCacheServer ���� ����.";
		case IDS_STRING118: return L"DbCacheServer ���� ����.";
		case IDS_STRING119: return L"���� request�� ���� ������ �������� �ʾҽ��ϴ�.";
		case IDS_STRING120: return L"����";
		}
		return L"�� �� ����";
	}

}