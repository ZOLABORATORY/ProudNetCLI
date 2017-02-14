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
		//프라우드넷예제의 로그 임의구현
	private:
		
		void Connect(System::String^ db_cache_server_ip, int db_cache_server_port);

		CFastList<Proud::String> m_LogMsgList;
		CriticalSection m_CSLogLock;

		
		bool m_leaveServer;
		// 일방적 메서드를 확인하기위한 guid
		// Guid that to check one-sided method
		Proud::Guid m_lastWriteDoneGuid;

		/** 서버 연결 시도 결과를 리턴한다. */
		/** Return server connectnion attempt */
		virtual void OnJoinDbCacheServerComplete(ErrorInfo *info)PN_OVERRIDE;

		/** DB cache server와의 연결이 해제됐음을 노티한다.
		- 이것이 호출된 상황에서는, 이미 DB cache client의 모든 데이터가 unload된 상태이다. */
		/** Notify disconnected with DB cache server.
		- When this called, all data of DB cache client has already unloaded. */
		virtual void OnLeaveDbCacheServer(ErrorType reason)PN_OVERRIDE;

		/** DB cache server에서 DBMS에 기록하는 과정이 끝날 때마다 도착하는 이벤트
		\param type 완료된 기록의 종류
		\param loadedDataGuid 완료된 기록을 가리키는 Guid. RootNode의 UUID이다. */

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