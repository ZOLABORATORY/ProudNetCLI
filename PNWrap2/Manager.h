#pragma once
#include "stdafx.h"

namespace PNWrap2
{
	class Manager : public Proud::IDbCacheClientDelegate2
	{
		
	public:
		void LogEvent(CStringW str);
		void LogError(CStringW text);
		static CStringW LoadString(int);
		bool Connected = false;
		CAutoPtr<CDbClient> m_client;
		//������ݿ����� �α� ���Ǳ���
	private:
		
		void Connect(System::String^ db_cache_server_ip, int db_cache_server_port);

		CFastList<Proud::String> m_LogMsgList;
		CriticalSection m_CSLogLock;

		
		bool m_leaveServer;
		// �Ϲ��� �޼��带 Ȯ���ϱ����� guid
		// Guid that to check one-sided method
		Proud::Guid m_lastWriteDoneGuid;

		/** ���� ���� �õ� ����� �����Ѵ�. */
		/** Return server connectnion attempt */
		virtual void OnJoinDbCacheServerComplete(ErrorInfo *info)PN_OVERRIDE;

		/** DB cache server���� ������ ���������� ��Ƽ�Ѵ�.
		- �̰��� ȣ��� ��Ȳ������, �̹� DB cache client�� ��� �����Ͱ� unload�� �����̴�. */
		/** Notify disconnected with DB cache server.
		- When this called, all data of DB cache client has already unloaded. */
		virtual void OnLeaveDbCacheServer(ErrorType reason)PN_OVERRIDE;

		/** DB cache server���� DBMS�� ����ϴ� ������ ���� ������ �����ϴ� �̺�Ʈ
		\param type �Ϸ�� ����� ����
		\param loadedDataGuid �Ϸ�� ����� ����Ű�� Guid. RootNode�� UUID�̴�. */

		/** Arriving event when it has done writing process to DBMS at DB cache server
		\param type Type of finished writing
		\param loadedDataGuid Guid that point finished writing. UUID of RootNode. */
		virtual void OnDbmsWriteDone(DbmsWritePropNodePendType type, Proud::Guid loadedDataGuid) PN_OVERRIDE;

		virtual void OnExclusiveLoadDataComplete(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnDataUnloadRequested(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnDataForceUnloaded(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnAddDataFailed(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnAddDataSuccess(CCallbackArgs& args)PN_OVERRIDE;


		virtual void OnUpdateDataFailed(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnUpdateDataSuccess(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnRemoveDataFailed(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnRemoveDataSuccess(CCallbackArgs& args)PN_OVERRIDE;

		// 	virtual void OnNonExclusiveSnapshotDataFailed(CCallbackArgs& args)PN_OVERRIDE;
		// 	virtual void OnNonExclusiveSnapshotDataSuccess(CCallbackArgs& args)PN_OVERRIDE;
		virtual void OnNonExclusiveSnapshotDataComplete(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnNonExclusiveAddDataAck(CCallbackArgs& args)PN_OVERRIDE;
		virtual void OnNonExclusiveRemoveDataAck(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnNonExclusiveModifyValueSuccess(CCallbackArgs& args)PN_OVERRIDE;
		virtual void OnNonExclusiveModifyValueFailed(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnNonExclusiveSetValueIfSuccess(CCallbackArgs& args)PN_OVERRIDE;
		virtual void OnNonExclusiveSetValueIfFailed(CCallbackArgs& args)PN_OVERRIDE;


		virtual void OnSomeoneAddData(CCallbackArgs& args)PN_OVERRIDE;
		virtual void OnSomeoneRemoveData(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnSomeoneModifyValue(CCallbackArgs& args)PN_OVERRIDE;
		virtual void OnSomeoneSetValue(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnException(Proud::Exception &e) PN_OVERRIDE;
		virtual void OnWarning(ErrorInfo *errorInfo)PN_OVERRIDE;
		virtual void OnError(ErrorInfo *errorInfo)PN_OVERRIDE;

		virtual void OnAccessError(CCallbackArgs& args)PN_OVERRIDE;

		virtual void OnIsolateDataFailed(CCallbackArgs& args)PN_OVERRIDE {}
		virtual void OnIsolateDataSuccess(CCallbackArgs& args)PN_OVERRIDE {}
		virtual void OnDeisolateDataFailed(CCallbackArgs& args)PN_OVERRIDE {}
		virtual void OnDeisolateDataSuccess(CCallbackArgs& args)PN_OVERRIDE {}

	public:
		Manager(System::String^ db_cache_server_ip, int db_cache_server_port);
		~Manager();
	};
}