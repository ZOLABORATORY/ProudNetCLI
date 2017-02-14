// 기본 DLL 파일입니다.

#include "stdafx.h"
#include "PNWrap2.h"


namespace PNWrap2 {

	MainClass::MainClass() : manager(NULL)
	{	
		
	}

	MainClass::~MainClass()
	{
		if(manager != NULL)
			delete manager;
		manager = NULL;
	}

	bool MainClass::ConnectSucceeded()
	{
		return manager->Connected;
	}

	void MainClass::Start(System::String^ db_cache_server_ip, int db_cache_server_port)
	{
		manager = new Manager(db_cache_server_ip, db_cache_server_port);		
	}

	void MainClass::RequestExclusiveLoadData(SString^ table, SString^ column, System::Object^ column_value, System::Object^ comment)
	{	
		Proud::String tbname = SStringToProud(table);
		Proud::String clname = SStringToProud(column);
		Proud::String clvalue = SStringToProud(column_value->ToString());

		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		//System::IntPtr ip = (System::IntPtr)comment;		
		DBClient->RequestExclusiveLoadData(tbname, clname, clvalue, ip.ToInt32());
	}

	void MainClass::RequestExclusiveLoadDataByGuid(SString^ rootTableName, WrapGUID^ rootUUID, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestExclusiveLoadDataByGuid(SStringToProud(rootTableName), rootUUID->original, ip.ToInt32());
	}

	void MainClass::RequestExclusiveLoadDataByQuery(SString^ rootTableName, SString^ queryString, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestExclusiveLoadDataByQuery(SStringToProud(rootTableName), SStringToProud(queryString), ip.ToInt32());
	}

	void MainClass::RequestExclusiveLoadNewData(SString^ rootTableName, WrapCPropNodePtr^ addData, bool transaction, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestExclusiveLoadNewData(SStringToProud(rootTableName), addData->original, ip.ToInt32(), transaction);
	}

	void MainClass::RequestExclusiveLoadNewData(SString^ rootTableName, WrapCPropNodePtr^ addData, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestExclusiveLoadNewData(SStringToProud(rootTableName), addData->original, ip.ToInt32());
	}

	void MainClass::RequestAddData(WrapGUID^ rootUUID, WrapGUID^ ownerUUID, WrapCPropNodePtr^ addData, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestAddData(rootUUID->original, ownerUUID->original, addData->original, ip.ToInt32());
	}

	void MainClass::RequestUpdateData(WrapCPropNodePtr^ updateData, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestUpdateData(updateData->original, ip.ToInt32());
	}

	void MainClass::RequestRemoveData(WrapGUID^ rootUUID, WrapGUID^ removeUUID, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestRemoveData(rootUUID->original, removeUUID->original, ip.ToInt32());
	}

	void MainClass::RequestRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestRecursiveUpdateData(loadedData->original, ip.ToInt32());
	}

	void MainClass::RequestRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestRecursiveUpdateData(loadedData->original, ip.ToInt32(), transactional);
	}

	void MainClass::BlockedAddData(WrapGUID^ rootUUID, WrapGUID^ ownerUUID, WrapCPropNodePtr^ addData, UINT32 timeOutTime, System::Object^ comment)
	{
		DBClient->BlockedAddData(rootUUID->original, ownerUUID->original, addData->original, timeOutTime);
	}

	void MainClass::BlockedUpdateData(WrapCPropNodePtr^ updateData, UINT32 timeOutTime, System::Object^ comment)
	{
		DBClient->BlockedUpdateData(updateData->original, timeOutTime);
	}

	void MainClass::BlockedRemoveData(WrapGUID^ rootUUID, WrapGUID^ ownerUUID, UINT32 timeOutTime, System::Object^ comment)
	{
		DBClient->BlockedRemoveData(rootUUID->original, ownerUUID->original, timeOutTime);
	}

	void MainClass::BlockedRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, System::Object^ comment)
	{
		DBClient->BlockedRecursiveUpdateData(loadedData->original);
	}

	void MainClass::BlockedRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional, System::Object^ comment)
	{
		DBClient->BlockedRecursiveUpdateData(loadedData->original, transactional);
	}

	void MainClass::BlockedRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional, UINT32 timeOutTime, System::Object^ comment)
	{
		DBClient->BlockedRecursiveUpdateData(loadedData->original, transactional, (uint32_t)timeOutTime);
	}

	void MainClass::UnilateralAddData(WrapGUID^ rootUUID, WrapGUID^ ownerUUID, WrapCPropNodePtr^ addData)
	{
		DBClient->UnilateralAddData(rootUUID->original, ownerUUID->original, addData->original);
	}

	void MainClass::UnilateralUpdateData(WrapCPropNodePtr^ updateData)
	{
		DBClient->UnilateralUpdateData(updateData->original);
	}

	void MainClass::UnilateralUpdateData(WrapCPropNodePtr^ updateData, bool writeDbmsImmediately)
	{
		DBClient->UnilateralUpdateData(updateData->original, writeDbmsImmediately);
	}

	void MainClass::UnilateralMoveData(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ nodeUUID, WrapGUID^ destRootUUID, WrapGUID^ destNodeUUID)
	{
		DBClient->UnilateralMoveData(SStringToProud(rootTableName), rootUUID->original, nodeUUID->original, destRootUUID->original, destNodeUUID->original);
	}

	void MainClass::UnilateralMoveData(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ nodeUUID, WrapGUID^ destRootUUID, WrapGUID^ destNodeUUID, bool writeDbmsImmediately)
	{
		DBClient->UnilateralMoveData(SStringToProud(rootTableName), rootUUID->original, nodeUUID->original, destRootUUID->original, destNodeUUID->original, writeDbmsImmediately);
	}

	void MainClass::UnilateralRemoveData(WrapGUID^ rootUUID, WrapGUID^ removeUUID)
	{
		DBClient->UnilateralRemoveData(rootUUID->original, removeUUID->original);
	}

	void MainClass::UnilateralRemoveData(WrapGUID^ rootUUID, WrapGUID^ removeUUID, bool writeDbmsImmediately)
	{
		DBClient->UnilateralRemoveData(rootUUID->original, removeUUID->original, writeDbmsImmediately);
	}

	void MainClass::UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData)
	{
		DBClient->UnilateralRecursiveUpdateData(loadedData->original);
	}

	void MainClass::UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional)
	{
		DBClient->UnilateralRecursiveUpdateData(loadedData->original, transactional);
	}

	void MainClass::UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr^ loadedData, bool transactional, bool writeDbmsImmediately)
	{
		DBClient->UnilateralRecursiveUpdateData(loadedData->original, transactional, writeDbmsImmediately);
	}

	void MainClass::UnloadDataBySessionGuid(WrapGUID^ sessionGuid, System::Object^ comment)
	{
		DBClient->UnloadDataBySessionGuid(sessionGuid->original);
	}

	void MainClass::DenyUnloadData(WrapGUID^ sessionGuid, System::Object^ comment)
	{
		DBClient->DenyUnloadData(sessionGuid->original);
	}

	void MainClass::ForceCompleteUnload(WrapGUID^ rootGuid, System::Object^ comment)
	{
		DBClient->ForceCompleteUnload(rootGuid->original);
	}

	void MainClass::RequestNonExclusiveSnapshotData(SString^ rootTableName, SString^ fieldName, WrapCVariant^ cmpValue, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestNonExclusiveSnapshotData(SStringToProud(rootTableName), SStringToProud(fieldName), cmpValue->original, ip.ToInt32());
	}

	void MainClass::RequestNonExclusiveSnapshotDataByGuid(SString^ rootTableName, WrapGUID^ rootUUID, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestNonExclusiveSnapshotDataByGuid(SStringToProud(rootTableName), rootUUID->original, ip.ToInt32());
	}

	void MainClass::RequestNonExclusiveSnapshotDataByQuery(SString^ rootTableName, SString^ searchString, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestNonExclusiveSnapshotDataByQuery(SStringToProud(rootTableName), SStringToProud(searchString), ip.ToInt32());
	}

	void MainClass::RequestNonExclusiveAddData(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ ownerUUID, WrapCPropNodePtr^ addData, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestNonExclusiveAddData(SStringToProud(rootTableName), rootUUID->original, ownerUUID->original, addData->original, ip.ToInt32());
	}

	void MainClass::RequestNonExclusiveRemoveData(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ removeUUID, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestNonExclusiveRemoveData(SStringToProud(rootTableName), rootUUID->original, removeUUID->original, ip.ToInt32());
	}

	void MainClass::RequestNonExclusiveSetValueIf(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ nodeUUID, SString^ propertyName, WrapCVariant^ newValue, WrapValueCompareType compareType, WrapCVariant^ compareValue, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestNonExclusiveSetValueIf(SStringToProud(rootTableName), rootUUID->original, nodeUUID->original, SStringToProud(propertyName), newValue->original, (Proud::ValueCompareType)compareType, compareValue->original, ip.ToInt32());
	}

	void MainClass::RequestNonExclusiveModifyValue(SString^ rootTableName, WrapGUID^ rootUUID, WrapGUID^ nodeUUID, SString^ propertyName, WrapValueOperType operType, WrapCVariant^ value, System::Object^ comment)
	{
		System::IntPtr ip = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(comment);
		System::Runtime::InteropServices::Marshal::Release(ip);

		DBClient->RequestNonExclusiveModifyValue(SStringToProud(rootTableName), rootUUID->original, nodeUUID->original, SStringToProud(propertyName), (Proud::ValueOperType)operType, value->original, ip.ToInt32());
	}

	void MainClass::RequestIsolateData(WrapGUID^ rootUUID, SString^ rootTableName, WrapGUID^ outSessionGuid, System::Object^ comment)
	{
		DBClient->RequestIsolateData(rootUUID->original, SStringToProud(rootTableName), outSessionGuid->original);
	}

	void MainClass::RequestDeisolateData(WrapGUID^ rootUUID, SString^ filterText, WrapGUID^ outSessionGuid, System::Object^ comment)
	{
		DBClient->RequestDeisolateData(rootUUID->original, SStringToProud(filterText), outSessionGuid->original);
	}

	void MainClass::GetClonedLoadedDataBySessionGuid(WrapGUID^ sessionGuid, System::Object^ comment)
	{
		DBClient->GetClonedLoadedDataBySessionGuid(sessionGuid->original);
	}

	void MainClass::GetClonedLoadedDataByUUID(WrapGUID^ rootUUID, System::Object^ comment)
	{
		DBClient->GetClonedLoadedDataByUUID(rootUUID->original);
	}

	PNWrap2::WrapHostID MainClass::GetLocalHostID()
	{
		return (PNWrap2::WrapHostID)DBClient->GetLocalHostID();
	}

	bool MainClass::IsLoggedOn()
	{
		return DBClient->IsLoggedOn();
	}

}

