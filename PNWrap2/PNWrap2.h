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
		//manager->m_client->m_DbClient �̰� Ÿ���� �ϱ� �Ⱦ ���� ������Ƽd
		property CAutoPtr<CDbCacheClient2>& DBClient
		{
			CAutoPtr<CDbCacheClient2>& get()
			{
				return manager->m_client->m_DbClient;
			}
		}
	public:
		//����
		MainClass();

		//�İ�
		~MainClass();

		//�ſ� ������ Start, ����� ȣ���ϸ� ��
		void Start(System::String^ db_cache_server_ip, int db_cache_server_port);

		//Start�� �����ߴ��� ���θ� �˷��ִ� bool �Լ� ( ������� while(ConnectSucceeded() ) �ϸ��
		bool ConnectSucceeded();

		//wrapping �Լ��� : intptr tag�� ������ �ϴ� 0����, ByteArray message�� �ϴ� �Ű� �Ⱦ�
		//�� �ܿ��� �ܼ��� wrapping
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


