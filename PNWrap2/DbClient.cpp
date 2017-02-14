#include "DbClient.h"
#include "stdafx.h"

using namespace Proud;
namespace PNWrap2
{
	CDbClient::CDbClient(Manager *pOwner) :m_pOwner(pOwner)
	{
		m_DbClient.Attach(CDbCacheClient2::New());
		bRequestComplete = false;

		//tag?
		// It made for custom setting ID by user.
		// Example) INT_PTR arg = new object; Request...(...,arg);
		// OnNotify...(CCallbackArgs args){ args.m_tag;// Value has returned which put here.}
		// This may use for ID or pointer.

		//����ڰ� custom�ϰ� ���̵� �����ϱ� ���� ����������ϴ�.
		//��� ��) INT_PTR arg = new object; Request...(...,arg);
		// OnNotify...(CCallbackArgs args){ args.m_tag;//����� �־��� ���� ���ɴϴ�.}
		//�̰��� idȤ�� pointer�� ���ɼ� �ֽ��ϴ�.
		m_diffCustomArg = 10;
	}

	CDbClient::~CDbClient(void)
	{
		m_DbClient.Free();
	}

	void CDbClient::SimpleTest()
	{
		// TODO: Adds control report precessor code to here.
		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		static int ClickNum = 1;

			// Check whether received request or not.
			// request �� �Դ��� Ȯ�� �մϴ�.
			if (!GetRequestComplete())
			{
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING119));
				return;
			}

			switch (ClickNum)
			{
			case 1:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"1st------------------AddGamerData---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->RequestExclusiveLoadNewData()");
				if (!AddGamerData())			//Request type sample  //Request �� ���� 
					m_pOwner->LogError(L"AddGamerData " + m_pOwner->LoadString(IDS_STRING113));
				break;

			case 2:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"2nd------------------AddHeroData---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->RequestAddData()");

				if (!AddHeroData()) 			//Request type sample  //Request �� ����
					m_pOwner->LogError(L"AddHeroData " + m_pOwner->LoadString(IDS_STRING113));


				break;

			case 3:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"3rd------------------UpdateHeroData---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->RequestUpdateData()");
				if (!UpdateHeroData())	//Request type sample  //Request �� ����
					m_pOwner->LogError(L"Failed to send. Hero UUID is wrong.");
				break;

			case 4:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"4th------------------BlockedAddItem---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->BlockedAddData()");
				if (!BlockedAddItem())		//Blocked type sample  //Blocked �� ����
					m_pOwner->LogError(L"BlockedAddItem " + m_pOwner->LoadString(IDS_STRING113));
				break;
			case 5:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"5th------------------BlockedUpdateItem---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->BlockedUpdateData()");
				if (!BlockedUpdateItem())		//Blocked type sample  //Blocked �� ����
					m_pOwner->LogError(L"BlockedUpdateItem " + m_pOwner->LoadString(IDS_STRING113));
				break;

			case 6:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"6th------------------BlockedRemoveItem---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->BlockedRemoveData()");
				if (!BlockedRemoveItem())	//Blocked type sample  //Blocked �� ����
					m_pOwner->LogError(L"BlockedRemoveItem " + m_pOwner->LoadString(IDS_STRING113));
				break;

			case 7:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"7th------------------AddFriend---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->UnilateralAddData()");
				// General type sample - It is based on success.
				// �Ϲ��� ���� - �ݵ�� ������ ������ �մϴ�.
				if (!AddFriend())
					m_pOwner->LogError(L"AddFriend failed");
				break;

			case 8:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"8th------------------UpdateFriend---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->UnilateralUpdateData()");
				// General type sample - It is based on success.
				// �Ϲ��� ���� - �ݵ�� ������ ������ �մϴ�.
				if (!UpdateFriend())
					m_pOwner->LogError(L"UpdateFriend " + m_pOwner->LoadString(IDS_STRING113));
				break;

				// RemoveFriend Ȥ�� RemoveHeroData�� �������� �ʾƵ� Root�� ����� �������� ���� �����ǵ��� �����Ǿ����ϴ�.
			case 9:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"9th------------------RemoveGamerData---------------------");
				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING112) + L": m_DbClient->RemoveGamerData()");
				if (!RemoveGamerData())		//Request type sample  //Request �� ����
					m_pOwner->LogError(L"RemoveGamerData " + m_pOwner->LoadString(IDS_STRING113));
				break;

			default:
				m_pOwner->LogEvent(L"");
				m_pOwner->LogEvent(L"======================================================");
				m_pOwner->LogEvent(L"======================================================");
				m_pOwner->LogEvent(L"Test End. If you click once more, you will back to beginning.");
				ClickNum = 0;
				break;
			}
// 		}
// 		else if (m_pOwner->m_sampleCase == 2)
// 		{
// 			// NonExclusive type does not use DB Cache.
// 			// NonExclusive is based on that do not use functions supporting Cache.
// 
// 			// NonExclusive �迭�� DB Cache�� ������� �ʽ��ϴ�.
// 			// NonExclusive �� Cache�� �����ϴ� �Լ���� ���� ������� �ʴ� ���� �⺻ �������� �մϴ�.
// 
// 			// Check whether received request or not.
// 			// request �� �Դ��� Ȯ�� �մϴ�.
// 			if (!GetRequestComplete())
// 			{
// 				m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING119));
// 				return;
// 			}
// 
// 			switch (ClickNum)
// 			{
// 			case 1:
// 				m_pOwner->LogEvent(L"");
// 				m_pOwner->LogEvent(L"1st----------------LoadRootAddExclusive-------------------");
// 				LoadRootAddExclusive();
// 				break;
// 			case 2:
// 				m_pOwner->LogEvent(L"");
// 				m_pOwner->LogEvent(L"2nd------------------LoadDataSnapshot---------------------");
// 				LoadDataSnapshot();
// 				break;
// 
// 			case 3:
// 				m_pOwner->LogEvent(L"");
// 				m_pOwner->LogEvent(L"3rd------------------AddNonExclusive---------------------");
// 				AddNonExclusive();
// 				break;
// 			case 4:
// 				m_pOwner->LogEvent(L"");
// 				m_pOwner->LogEvent(L"4th------------------AddChildNonExclusive---------------------");
// 				AddChildNonExclusive();
// 				break;
// 			case 5:
// 				m_pOwner->LogEvent(L"");
// 				m_pOwner->LogEvent(L"5th----------------RequestModify-------------------");
// 				RequestModify(ValueOperType_Plus, 10);
// 				break;
// 			case 6:
// 				m_pOwner->LogEvent(L"");
// 				m_pOwner->LogEvent(L"6th----------------RequestSetIfValue-------------------");
// 				RequestSetIfValue(ValueCompareType_NotEqual, 10, 20);
// 				break;
// 			case 7:
// 				m_pOwner->LogEvent(L"");
// 				m_pOwner->LogEvent(L"7th----------------RemoveNonExclusive-------------------");
// 				m_pOwner->LogEvent(L"");
// 
// 				// Item Ȥ�� Hero�� �������� �ʾƵ� Root�� ����� �������� ���� �����ǵ��� �����Ǿ����ϴ�.
// 				m_pOwner->LogEvent(L"Gamer data remove");
// 				RemoveNonExclusive(m_data->RootUUID);
// 				break;
// 
// 
// 			default:
// 				m_pOwner->LogEvent(L"");
// 				m_pOwner->LogEvent(L"======================================================");
// 				m_pOwner->LogEvent(L"======================================================");
// 				m_pOwner->LogEvent(L"Test End. If you click once more, you will back to beginning.");
// 				ClickNum = 0;
// 				break;
// 			}
// 
// 		}

		++ClickNum;

	}

	bool CDbClient::AddGamerData()
	{
		bRequestComplete = false;
		// Adds Gamer to DB. Exclusive loading.
		// DB�� Gamer�� �߰��Ѵ�.�����ε�.
		CPropNodePtr newNode = CPropNodePtr(new CPropNode(L"Gamer"));
		newNode->Fields[L"GamerID"] = m_GamerName;
		newNode->Fields[L"Password"] = L"TestPass";

		m_DbClient->RequestExclusiveLoadNewData(L"Gamer", newNode, 0, true);
		return true;
	}

	bool CDbClient::AddHeroData()
	{
		bRequestComplete = false;
		// Adds Hero to gamer.
		// ���̸ӿ� Hero�� �߰��Ѵ�.
		CPropNodePtr newNode = CPropNodePtr(new CPropNode(L"Hero"));
		newNode->Fields[L"Name"] = m_heroName;
		newNode->Fields[L"Removed"] = 0;
		newNode->Fields[L"HeroType"] = 1;

		if (!m_DbClient->RequestAddData(m_data->RootUUID, m_data->RootUUID, newNode, m_diffCustomArg))
		{
			m_pOwner->LogError(L"AddHeroData " + m_pOwner->LoadString(IDS_STRING114));
			return false;
		}

		return true;
	}

	bool CDbClient::UpdateHeroData()
	{
		bRequestComplete = false;
		CPropNodePtr heroNode = m_data->GetNode(m_heroGuid);
		if (!heroNode || heroNode->UUID == Proud::Guid())
			return false;

		// Change information of hero.
		// ������� ������ �ٲ۴�.
		heroNode->Fields[L"HeroType"] = 2;

		// Update information of hero.
		// ������� ������ ������Ʈ�Ѵ�.
		if (!m_DbClient->RequestUpdateData(heroNode, m_diffCustomArg))
		{
			m_pOwner->LogError(L"UpdateHeroData " + m_pOwner->LoadString(IDS_STRING114));
			return false;
		}
		// !!! If Request has joined, it can do other thing when it receives request response.
		// If you want to use function that automatically waiting and return then use Blocked function.
		// !!! Request�� ������ �ݵ�� ��ٷȴٰ� ��밡 ���ƿ��� ������ �ٸ� ���𰡸� �� �� �ֽ��ϴ�.
		// �ڵ����� ��ٷȴٰ� �����ϴ� �Լ��� ����ϰ��� �� ������ Blocked �Լ��� ����ϸ� �˴ϴ�.
		return true;
	}

	bool CDbClient::RemoveHeroData()
	{
		bRequestComplete = false;
		// Delete information of hero.
		// ������� ������ �����Ѵ�.
		// 	if(!m_DbClient->RequestRemoveData(m_data->RootUUID, m_heroGuid, m_diffCustomArg))
		// 	{
		// 		m_pOwner->LogError(L"RemoveHeroData " + m_pOwner->LoadString(IDS_STRING114));
		// 		return false;
		// 	}
		// !!! If Request has joined, it can do other thing when it receives request response.
		// If you want to use function that automatically waiting and return then use Blocked function.
		// !!! Request�� ������ �ݵ�� ��ٷȴٰ� ��밡 ���ƿ��� ������ �ٸ� ���𰡸� �� �� �ֽ��ϴ�.
		// �ڵ����� ��ٷȴٰ� �����ϴ� �Լ��� ����ϰ��� �� ������ Blocked �Լ��� ����ϸ� �˴ϴ�.
		return true;
	}

	bool CDbClient::BlockedAddItem()
	{
		// Adds Item as lower of hero.
		// ������� ������ Item�� �߰��Ѵ�.
		CPropNodePtr newNode = CPropNodePtr(new CPropNode(L"Item"));
		newNode->Fields[L"Name"] = L"15Sword";
		newNode->Fields[L"Type"] = 1;

		ErrorInfoPtr outerror = ErrorInfoPtr(new ErrorInfo);
		if (!m_DbClient->BlockedAddData(m_data->RootUUID, m_data->RootUUID, newNode, 10000, outerror))
		{
			m_pOwner->LogError(L"BlockedAddData " + m_pOwner->LoadString(IDS_STRING114));

			String txt;
			txt.Format(L"%s occured at %s", (LPCWSTR)outerror->ToString(), __FUNCTIONW__);
			m_pOwner->LogError(txt.GetString());

			return false;
		}

		// Item Guid update
		m_itemGuid = newNode->UUID;
		// It only returns when it receive message that called Blocked so data update can available after return.
		// Blocked�� �޽����� �����ؾ����� ���ϵǱ� ������ ���� ���� �� data�� ������Ʈ�� �� �ֽ��ϴ�.
		m_data = m_DbClient->GetClonedLoadedDataBySessionGuid(m_SessionGuid);
		return true;
	}

	bool CDbClient::BlockedUpdateItem()
	{
		CPropNodePtr newNode2 = m_data->GetNode(m_itemGuid);
		if (!newNode2 || newNode2->UUID == Proud::Guid())
			return false;
		newNode2->Fields[L"Name"] = L"18Sword";
		newNode2->Fields[L"Type"] = 18;

		//virtual bool BlockedUpdateData(CLoadedData2Ptr loadedData,bool transactional = true,DWORD timeOutTime = 30000,ErrorInfoPtr outError = ErrorInfoPtr()) = 0;
		//virtual bool BlockedUpdateData(CPropNodePtr updateData,DWORD timeOutTime = 30000,ErrorInfoPtr outError = ErrorInfoPtr()) = 0;
		ErrorInfoPtr outerror = ErrorInfoPtr(new ErrorInfo);
		if (!m_DbClient->BlockedUpdateData(newNode2, 30000, outerror))
		{
			m_pOwner->LogError(L"BlockedUpdateData " + m_pOwner->LoadString(IDS_STRING114));

			String txt;
			txt.Format(L"%s occured at %s", (LPCWSTR)outerror->ToString(), __FUNCTIONW__);
			m_pOwner->LogError(txt.GetString());

			return false;
		}
		m_itemGuid = newNode2->UUID;
		m_data = m_DbClient->GetClonedLoadedDataBySessionGuid(m_SessionGuid);
		return true;

	}

	bool CDbClient::BlockedRemoveItem()
	{
		ErrorInfoPtr errorout = ErrorInfoPtr(new ErrorInfo);
		if (!m_DbClient->BlockedRemoveData(m_data->RootUUID, m_itemGuid, 10000, errorout))
		{
			m_pOwner->LogError(L"BlockedRemoveItem " + m_pOwner->LoadString(IDS_STRING114));

			String txt;
			txt.Format(L"%s occured at %s", (LPCWSTR)errorout->ToString(), __FUNCTIONW__);
			m_pOwner->LogError(txt.GetString());

			return false;
		}

		// It only returns when it receive message that called Blocked so data update can available after return.
		// Blocked�� �޽����� �����ؾ����� ���ϵǱ� ������ ���� ���� �� data�� ������Ʈ�� �� �ֽ��ϴ�.
		m_data = m_DbClient->GetClonedLoadedDataBySessionGuid(m_SessionGuid);
		return true;
	}

	bool CDbClient::AddFriend()
	{
		CPropNodePtr newFriend = CPropNodePtr(new CPropNode(L"Friend"));
		newFriend->Fields[L"charLevel"] = 100;
		newFriend->Fields[L"Name"] = L"I'm your father";

		if (!m_DbClient->UnilateralAddData(m_data->RootUUID, m_data->RootUUID, newFriend, true))
		{
			m_pOwner->LogError(L"AddFriend " + m_pOwner->LoadString(IDS_STRING114));
			return false;
		}

		// Friend Guid Update
		// ģ�� Guid Update
		m_friendGuid = newFriend->UUID;

		// Adds to m_data.
		// It is for synchronize with internal data of dbclient and data at here.
		//m_data���� �߰��Ͽ� �ݴϴ�.
		//dbclient�� ���� �����Ϳ� ������ �����͸� ����ȭ �ϱ� �����Դϴ�.
		m_data->InsertChild(m_data->GetRootNode(), newFriend);

		// Or,
		// You can synchronize like this.
		//Ȥ��,
		//�̷��� ����ȭ�� �Ͽ��� �ǰڽ��ϴ�.
		//m_data = m_DbClient->GetClonedLoadedDataBySessionGuid(m_SessionGuid);
		return true;
	}

	bool CDbClient::UpdateFriend()
	{
		CPropNodePtr node = m_data->GetNode(m_friendGuid);
		if (!node || node->UUID == Proud::Guid())
		{
			m_pOwner->LogError(L"UpdateFriend " + m_pOwner->LoadString(IDS_STRING114) + m_pOwner->LoadString(IDS_STRING115));
			return false;
		}

		node->Fields[L"charLevel"] = 300;

		if (!m_DbClient->UnilateralUpdateData(node, true))
		{
			m_pOwner->LogError(L"UpdateFriend " + m_pOwner->LoadString(IDS_STRING114));
			return false;
		}
		return true;
	}

	bool CDbClient::RemoveFriend()
	{
		if (!m_DbClient->UnilateralRemoveData(m_data->RootUUID, m_friendGuid, true))
		{
			m_pOwner->LogError(L"RemoveFriend " + m_pOwner->LoadString(IDS_STRING114));
			return false;
		}

		CPropNodePtr friendNode = m_data->GetNode(m_friendGuid);
		m_data->RemoveNode(friendNode);

		return true;
	}

	bool CDbClient::RemoveGamerData()
	{
		/*if(!m_DbClient->RequestRemoveData(m_data->RootUUID, m_data->RootUUID, m_diffCustomArg))
		{
		m_pOwner->LogError(L"RemoveGamerData " + m_pOwner->LoadString(IDS_STRING114));
		return false;
		}
		*/

		// UnilateralRemoveData test
		/*if(!m_DbClient->UnilateralRemoveData(m_data->RootUUID, m_data->RootUUID, true))
		{
		m_pOwner->LogError(L"RemoveGamerData " + m_pOwner->LoadString(IDS_STRING114));
		return false;
		}*/

		return true;
	}

	void CDbClient::RequestCompleteTrue()
	{
		CriticalSectionLock TRLock(m_CSLock, true);
		bRequestComplete = true;
	}

	bool CDbClient::GetRequestComplete()
	{
		CriticalSectionLock TRLock(m_CSLock, true);
		return bRequestComplete;
	}

	/************************ NonExclusive **************************/

	void CDbClient::LoadRootAddExclusive()
	{
		// Request Add&Loading Root information
		// Root ������ Add&�ε� ��û
		m_pOwner->LogEvent(m_pOwner->LoadString(IDS_STRING111));
		Proud::CPropNodePtr newprop = CPropNodePtr(new CPropNode(L"Gamer"));
		newprop->SetField(L"GamerID", m_GamerName);
		newprop->SetField(L"Password", L"1234");

		bRequestComplete = false;

		m_DbClient->RequestExclusiveLoadNewData(L"Gamer", newprop, m_diffCustomArg, false);
	}

	void CDbClient::LoadDataSnapshot()
	{
		bRequestComplete = false;
		m_DbClient->RequestNonExclusiveSnapshotData(L"Gamer", L"GamerID", m_GamerName, m_diffCustomArg);
	}

	void  CDbClient::AddNonExclusive()
	{
		// Add Hero 
		// Hero Table�� Hero ���� ����
		CPropNodePtr newData = CPropNodePtr(new CPropNode(L"Hero"));
		newData->SetField(L"Name", m_heroName);
		newData->SetField(L"Removed", 0);
		newData->SetField(L"HeroType", 1);

		if (!m_data)
			m_pOwner->LogError(L"AddNonExclusive m_data is NULL.");

		// DB�� Hero ������ �߰� �մϴ�.
		bRequestComplete = false;
		m_DbClient->RequestNonExclusiveAddData(m_data->GetRootNode()->TypeName,
			m_data->RootUUID, m_data->RootUUID, newData, m_diffCustomArg, Proud::ByteArray());
	}

	void CDbClient::AddChildNonExclusive()
	{
		// addItem - Insert Field information at Item table
		// addItem - Item ���̺��� Field���� ����
		CPropNodePtr newData = CPropNodePtr(new CPropNode(L"Item"));
		newData->SetField(L"Name", L"Sword");
		newData->SetField(L"Type", 2);

		if (!m_data)
			m_pOwner->LogError(L"AddChildNonExclusive m_data is NULL.");

		// Adds item to DB.
		// DB�� �������� �߰��մϴ�.
		bRequestComplete = false;
		m_DbClient->RequestNonExclusiveAddData(L"Gamer", m_data->RootUUID, m_heroGuid, newData, m_diffCustomArg, ByteArray());
	}


	void CDbClient::RequestModify(Proud::ValueOperType type, int value)
	{
		if (!m_data)
			m_pOwner->LogError(L"RequestModify m_data is NULL.");


		CPropNodePtr modifyData = m_data->GetNode(m_itemGuid);
		if (!modifyData)
			m_pOwner->LogError(L"RequestModify m_itemGuid is wrong.");


		int var = modifyData->GetField(L"Type");

		switch (type)
		{
		case ValueOperType_Plus:
			var += value;
			break;
		case ValueOperType_Minus:
			var -= value;
			break;
		case ValueOperType_Multiply:
			var *= value;
			break;
		case ValueOperType_Division:
			var /= value;
			break;
		}
		bRequestComplete = false;


		// Change data value of DB. 
		// DB�� �������� ���� ��ȭ ��ŵ�ϴ�. 
		m_DbClient->RequestNonExclusiveModifyValue(L"Gamer", m_data->RootUUID, modifyData->UUID, L"Type", type, value, m_diffCustomArg, ByteArray());
	}


	void CDbClient::RemoveNonExclusive(Proud::Guid &removeUUID)
	{
		// RemoveNonExclusive is repeatly calling at source.
		// So wait under message has arrived then process Remove command.
		// RemoveNonExclusive�� ���� �ҽ����� �������� ȣ��ǰ� �ֽ��ϴ�.
		// ������ �޽����� �� ������ ��ٷȴٰ� ���� Remove����� �����մϴ�.
		while (!GetRequestComplete())
		{
			Sleep(100);
		}

		bRequestComplete = false;
		// Delete information of DB.
		// DB�� ������ ���� �մϴ�.
		m_DbClient->RequestNonExclusiveRemoveData(L"Gamer", m_data->RootUUID, removeUUID, m_diffCustomArg, ByteArray());
	}


	void CDbClient::RequestSetIfValue(Proud::ValueCompareType tyep, int value, int value2)
	{
		Proud::Guid waitTicket;

		m_data = m_DbClient->GetClonedLoadedDataByUUID(m_data->RootUUID);

		// Get PropNode of changing item.
		// ��ȭ��ų �������� PropNode�� ���ɴϴ�.
		CPropNodePtr modifyData = m_data->GetNode(m_itemGuid);
		int var = value;

		bRequestComplete = false;

		//  Changing value by Proud::ValueCompareType option.
		//  Proud::ValueCompareType ���ǿ� ���Ͽ� ���� ��ȭ��ŵ�ϴ�.
		m_DbClient->RequestNonExclusiveSetValueIf(L"Gamer", m_data->RootUUID, modifyData->UUID, L"Type", value, tyep, value2, m_diffCustomArg, ByteArray());
	}
}