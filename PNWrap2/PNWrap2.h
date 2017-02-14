// PNWrap2.h
#pragma once
#include "stdafx.h"
#include "WrapCVariant.h"
#include "WrapCCallbackArgs.h"

using namespace System;

namespace PNWrap2 {

	//		delegate void EventJoinDbCacheServerComplete(ErrorInfo *info);

	//void EventLeaveDbCacheServer(ErrorType reason);

	//void EventDbmsWriteDone(DbmsWritePropNodePendType type, Proud::Guid loadedDataGuid) ;
	
	

	//void EventDataUnloadRequested(CCallbackArgs& args);

	//void EventDataForceUnloaded(CCallbackArgs& args);

	//void EventAddDataFailed(CCallbackArgs& args);

	// 		void EventAddDataSuccess(CCallbackArgs& args);
	// 
	// 
	// 		void EventUpdateDataFailed(CCallbackArgs& args);
	// 
	// 		void EventUpdateDataSuccess(CCallbackArgs& args);
	// 
	// 		void EventRemoveDataFailed(CCallbackArgs& args);
	// 
	// 		void EventRemoveDataSuccess(CCallbackArgs& args);
	// 
	// 		void EventNonExclusiveSnapshotDataComplete(CCallbackArgs& args);
	// 
	// 		void EventNonExclusiveAddDataAck(CCallbackArgs& args);
	// 		void EventNonExclusiveRemoveDataAck(CCallbackArgs& args);
	// 
	// 		void EventNonExclusiveModifyValueSuccess(CCallbackArgs& args);
	// 		void EventNonExclusiveModifyValueFailed(CCallbackArgs& args);
	// 
	// 		void EventNonExclusiveSetValueIfSuccess(CCallbackArgs& args);
	// 		void EventNonExclusiveSetValueIfFailed(CCallbackArgs& args);
	// 
	// 
	// 		void EventSomeoneAddData(CCallbackArgs& args);
	// 		void EventSomeoneRemoveData(CCallbackArgs& args);
	// 
	// 		void EventSomeoneModifyValue(CCallbackArgs& args);
	// 		void EventSomeoneSetValue(CCallbackArgs& args);
	// 
	// 		void EventException(Exception &e) ;
	// 		void EventWarning(ErrorInfo *errorInfo);
	// 		void EventError(ErrorInfo *errorInfo);
	// 
	// 		void EventAccessError(CCallbackArgs& args);
	// 
	// 		void EventIsolateDataFailed(CCallbackArgs& args) {}
	// 		void EventIsolateDataSuccess(CCallbackArgs& args) {}
	// 		void EventDeisolateDataFailed(CCallbackArgs& args) {}
	// 		void EventDeisolateDataSuccess(CCallbackArgs& args) {}

	
	public ref class MainClass
	{
		Manager* manager;
		//manager->m_client->m_DbClient 이거 타이핑 하기 싫어서 만든 프로퍼티d
		property CAutoPtr<CDbCacheClient2>& DBClient
		{
			CAutoPtr<CDbCacheClient2>& get()
			{
				return manager->m_client->m_DbClient;
			}
		}
	public:
		//생성
		MainClass();

		//파개
		~MainClass();

		//매우 심플한 Start, 만들고 호출하면 끝
		void Start(System::String^ db_cache_server_ip, int db_cache_server_port);

		//Start가 성공했는지 여부를 알려주는 bool 함수 ( 예를들어 while(ConnectSucceeded() ) 하면됨
		bool ConnectSucceeded();

		//wrapping 함수들 : intptr tag는 무조건 일단 0넣음, ByteArray message도 일단 신경 안씀
		//그 외에는 단순한 wrapping
		void RequestExclusiveLoadData(SString^ table, SString^ column, System::Object^ column_value, System::Object^ comment);
		void RequestExclusiveLoadDataByGuid(SString^ rootTableName, WrapGUID^ rootUUID, System::Object^ comment);
		void RequestExclusiveLoadDataByQuery(SString^ rootTableName, SString^ queryString, System::Object^ comment);
		void RequestExclusiveLoadNewData(SString^ rootTableName, WrapCPropNodePtr^ addData, bool transaction, System::Object^ comment);
		void RequestExclusiveLoadNewData(SString^ rootTableName, WrapCPropNodePtr^ addData, System::Object^ comment);
		void RequestAddData(WrapGUID^ rootUUID, WrapGUID^ ownerUUID, WrapCPropNodePtr^ addData, System::Object^ comment);
		void RequestUpdateData(WrapCPropNodePtr^ updateData, System::Object^ comment);
		void RequestRemoveData(WrapGUID^ rootUUID, WrapGUID^ removeUUID, System::Object^ comment);
		void RequestRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, System::Object^ comment);
		void RequestRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional, System::Object^ comment);
		void BlockedAddData(WrapGUID^ rootUUID, WrapGUID^ ownerUUID, WrapCPropNodePtr^ addData, UINT32 timeOutTime, System::Object^ comment);
		void BlockedUpdateData(WrapCPropNodePtr^ updateData, UINT32 timeOutTime, System::Object^ comment);
		void BlockedRemoveData(WrapGUID^ rootUUID, WrapGUID^ ownerUUID, UINT32 timeOutTime, System::Object^ comment);
		void BlockedRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, System::Object^ comment);
		void BlockedRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional, System::Object^ comment);
		void BlockedRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional, UINT32 timeOutTime, System::Object^ comment);
		void UnilateralAddData(WrapGUID^ rootUUID, WrapGUID^ ownerUUID, WrapCPropNodePtr^ addData);
		void UnilateralUpdateData(WrapCPropNodePtr^ updateData);
		void UnilateralUpdateData(WrapCPropNodePtr^ updateData, bool writeDbmsImmediately);
		void UnilateralMoveData(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ nodeUUID, WrapGUID^ destRootUUID, WrapGUID^ destNodeUUID);
		void UnilateralMoveData(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ nodeUUID, WrapGUID^ destRootUUID, WrapGUID^ destNodeUUID, bool writeDbmsImmediately);
		void UnilateralRemoveData(WrapGUID^ rootUUID, WrapGUID^ removeUUID);
		void UnilateralRemoveData(WrapGUID^ rootUUID, WrapGUID^ removeUUID, bool writeDbmsImmediately);
		void UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData);
		void UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional);
		void UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional, bool writeDbmsImmediately);		
		void UnloadDataBySessionGuid(WrapGUID^ sessionGuid, System::Object^ comment);
		void DenyUnloadData(WrapGUID^ sessionGuid, System::Object^ comment);
		void ForceCompleteUnload(WrapGUID^ rootGuid, System::Object^ comment);
		void RequestNonExclusiveSnapshotData(SString^ rootTableName, SString^ fieldName, WrapCVariant^ cmpValue, System::Object^ comment);
		void RequestNonExclusiveSnapshotDataByGuid(SString^ rootTableName, WrapGUID^ rootUUID, System::Object^ comment);

		void RequestNonExclusiveSnapshotDataByQuery(SString^ rootTableName, SString^ searchString, System::Object^ comment);
		void RequestNonExclusiveAddData(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ ownerUUID, WrapCPropNodePtr^ addData, System::Object^ comment);
		void RequestNonExclusiveRemoveData(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ removeUUID, System::Object^ comment);
		void RequestNonExclusiveSetValueIf(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ nodeUUID, SString^ propertyName, WrapCVariant^ newValue, WrapValueCompareType compareType, WrapCVariant^ compareValue, System::Object^ comment);
		void RequestNonExclusiveModifyValue(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ nodeUUID, SString^ propertyName, WrapValueOperType operType, WrapCVariant^ value, System::Object^ comment);
		void RequestIsolateData(WrapGUID^ rootUUID, SString^ rootTableName, WrapGUID^ outSessionGuid, System::Object^ comment);
		void RequestDeisolateData(WrapGUID^ rootUUID, SString^ filterText, WrapGUID^ outSessionGuid, System::Object^ comment);
		void GetClonedLoadedDataBySessionGuid(WrapGUID^ sessionGuid, System::Object^ comment);
		void GetClonedLoadedDataByUUID(WrapGUID^ rootUUID, System::Object^ comment);
		WrapHostID GetLocalHostID();
		bool IsLoggedOn();
		//
		
	};
}


