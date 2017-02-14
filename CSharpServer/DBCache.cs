using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PNWrap2;

namespace CSharpServer
{
    
    public class DBCache
    {
        public enum Result
        {
            OnExclusiveLoadDataComplete,
            OnDataUnloadRequested,
		    OnDataForceUnloaded,
		    OnAddDataFailed,
		    OnAddDataSuccess,
		    OnUpdateDataFailed,
		    OnUpdateDataSuccess,
		    OnRemoveDataFailed,
		    OnRemoveDataSuccess,
		    // 	OnNonExclusiveSnapshotDataFailed,
		    // 	OnNonExclusiveSnapshotDataSuccess,
		    OnNonExclusiveSnapshotDataComplete,
		    OnNonExclusiveAddDataAck,
		    OnNonExclusiveRemoveDataAck,
		    OnNonExclusiveModifyValueSuccess,
		    OnNonExclusiveModifyValueFailed,
		    OnNonExclusiveSetValueIfSuccess,
		    OnNonExclusiveSetValueIfFailed,
		    OnSomeoneAddData,
		    OnSomeoneRemoveData,
		    OnSomeoneModifyValue,
		    OnSomeoneSetValue,
		    OnException,
		    OnWarning,
		    OnError,
		    OnAccessError,
		    OnIsolateDataFailed,
		    OnIsolateDataSuccess,
		    OnDeisolateDataFailed,
		    OnDeisolateDataSuccess,

            NumberOf,
        }

        public class QueryParameter
        {
            public Result result = Result.NumberOf;
            public bool progressing;
            public WrapCPropNodePtr m_firstRootNode = null;
            public WrapCLoadedData2Ptr m_firstLoadData = null;
            public List<WrapCPropNodePtr> m_RootNodes = null;
            public List<WrapCLoadedData2Ptr> m_LoadedDatas = null;
            public List<WrapCPropNodePtr> m_rootNodesCreateIfNull
            {
                get
                {
                    if (m_RootNodes == null)
                        m_RootNodes = new List<WrapCPropNodePtr>();
                    return m_RootNodes;
                }
            }

            public List<WrapCLoadedData2Ptr> m_LoadedDatasCreateIfNull
            {
                get
                {
                    if (m_LoadedDatas == null)
                        m_LoadedDatas = new List<WrapCLoadedData2Ptr>();
                    return m_LoadedDatas;
                }
            }

            public WrapCPropNodePtr RootNode
            {
                get
                {
                    return m_firstRootNode;
                }
            }

            public WrapCLoadedData2Ptr LoadedData
            {
                get
                {
                    return m_firstLoadData;
                }
            }
        }

        public DBCache(PNWrap2.MainClass dbcache_client_class)
        {
            mc = dbcache_client_class;
        }

        PNWrap2.MainClass mc;

        public IEnumerator BlockedAddData(WrapGUID rootUUID, WrapGUID ownerUUID, WrapCPropNodePtr addData, uint timeOutTime, QueryParameter b)
        {
            b.progressing = true;
            mc.BlockedAddData(rootUUID, ownerUUID, addData, timeOutTime, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator BlockedRecursiveUpdateData(WrapCLoadedData2Ptr loadedData, QueryParameter b)
        {
            b.progressing = true;
            mc.BlockedRecursiveUpdateData(loadedData, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator BlockedRecursiveUpdateData(WrapCLoadedData2Ptr loadedData, bool transactional, QueryParameter b)
        {
            b.progressing = true;
            mc.BlockedRecursiveUpdateData(loadedData, transactional, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator BlockedRecursiveUpdateData(WrapCLoadedData2Ptr loadedData, bool transactional, uint timeOutTime, QueryParameter b)
        {
            b.progressing = true;
            mc.BlockedRecursiveUpdateData(loadedData, transactional, timeOutTime);
            while (b.progressing) yield return null;
        }
        public IEnumerator BlockedRemoveData(WrapGUID rootUUID, WrapGUID ownerUUID, uint timeOutTime, QueryParameter b)
        {
            b.progressing = true;
            mc.BlockedRemoveData(rootUUID, ownerUUID, timeOutTime, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator BlockedUpdateData(WrapCPropNodePtr updateData, uint timeOutTime, QueryParameter b)
        {
            b.progressing = true;
            mc.BlockedUpdateData(updateData, timeOutTime, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator DenyUnloadData(WrapGUID sessionGuid, QueryParameter b)
        {
            b.progressing = true;
            mc.DenyUnloadData(sessionGuid, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator ForceCompleteUnload(WrapGUID rootGuid, QueryParameter b)
        {
            b.progressing = true;
            mc.ForceCompleteUnload(rootGuid, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator GetClonedLoadedDataBySessionGuid(WrapGUID sessionGuid, QueryParameter b)
        {
            b.progressing = true;
            mc.GetClonedLoadedDataBySessionGuid(sessionGuid, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator GetClonedLoadedDataByUUID(WrapGUID rootUUID, QueryParameter b)
        {
            b.progressing = true;
            mc.GetClonedLoadedDataByUUID(rootUUID, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestAddData(WrapGUID rootUUID, WrapGUID ownerUUID, WrapCPropNodePtr addData, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestAddData(rootUUID, ownerUUID, addData, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestDeisolateData(WrapGUID rootUUID, string filterText, WrapGUID outSessionGuid, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestDeisolateData(rootUUID, filterText, outSessionGuid, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestExclusiveLoadData(string table, string column, object column_value, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestExclusiveLoadData(table, column, column_value, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestExclusiveLoadDataByGuid(string rootTableName, WrapGUID rootUUID, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestExclusiveLoadDataByGuid(rootTableName, rootUUID, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestExclusiveLoadDataByQuery(string rootTableName, string queryString, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestExclusiveLoadDataByQuery(rootTableName, queryString, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestExclusiveLoadNewData(string rootTableName, WrapCPropNodePtr addData, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestExclusiveLoadNewData(rootTableName, addData, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestExclusiveLoadNewData(string rootTableName, WrapCPropNodePtr addData, bool transaction, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestExclusiveLoadNewData(rootTableName, addData, transaction, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestIsolateData(WrapGUID rootUUID, string rootTableName, WrapGUID outSessionGuid, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestIsolateData(rootUUID, rootTableName, outSessionGuid, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestNonExclusiveAddData(string rootTableName, WrapGUID rootUUID, WrapGUID ownerUUID, WrapCPropNodePtr addData, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestNonExclusiveAddData(rootTableName, rootUUID, ownerUUID, addData, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestNonExclusiveModifyValue(string rootTableName, WrapGUID rootUUID, WrapGUID nodeUUID, string propertyName, WrapValueOperType operType, WrapCVariant value, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestNonExclusiveModifyValue(rootTableName, rootUUID, nodeUUID, propertyName, operType, value, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestNonExclusiveRemoveData(string rootTableName, WrapGUID rootUUID, WrapGUID removeUUID, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestNonExclusiveRemoveData(rootTableName, rootUUID, removeUUID, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestNonExclusiveSetValueIf(string rootTableName, WrapGUID rootUUID, WrapGUID nodeUUID, string propertyName, WrapCVariant newValue, WrapValueCompareType compareType, WrapCVariant compareValue, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestNonExclusiveSetValueIf(rootTableName, rootUUID, nodeUUID, propertyName, newValue, compareType, compareValue, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestNonExclusiveSnapshotData(string rootTableName, string fieldName, WrapCVariant cmpValue, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestNonExclusiveSnapshotData(rootTableName, fieldName, cmpValue, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestNonExclusiveSnapshotDataByGuid(string rootTableName, WrapGUID rootUUID, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestNonExclusiveSnapshotDataByGuid(rootTableName, rootUUID, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestNonExclusiveSnapshotDataByQuery(string rootTableName, string searchString, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestNonExclusiveSnapshotDataByQuery(rootTableName, searchString, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestRecursiveUpdateData(WrapCLoadedData2Ptr loadedData, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestRecursiveUpdateData(loadedData, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestRecursiveUpdateData(WrapCLoadedData2Ptr loadedData, bool transactional, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestRecursiveUpdateData(loadedData, transactional, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestRemoveData(WrapGUID rootUUID, WrapGUID removeUUID, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestRemoveData(rootUUID, removeUUID, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator RequestUpdateData(WrapCPropNodePtr updateData, QueryParameter b)
        {
            b.progressing = true;
            mc.RequestUpdateData(updateData, b);
            while (b.progressing) yield return null;
        }
        public IEnumerator UnilateralAddData(WrapGUID rootUUID, WrapGUID ownerUUID, WrapCPropNodePtr addData)
        {
            mc.UnilateralAddData(rootUUID, ownerUUID, addData);
            yield break;
        }
        public IEnumerator UnilateralMoveData(string rootTableName, WrapGUID rootUUID, WrapGUID nodeUUID, WrapGUID destRootUUID, WrapGUID destNodeUUID)
        {
            mc.UnilateralMoveData(rootTableName, rootUUID, nodeUUID, destRootUUID, destNodeUUID);
            yield break;
        }
        public IEnumerator UnilateralMoveData(string rootTableName, WrapGUID rootUUID, WrapGUID nodeUUID, WrapGUID destRootUUID, WrapGUID destNodeUUID, bool writeDbmsImmediately)
        {
            mc.UnilateralMoveData(rootTableName, rootUUID, nodeUUID, destRootUUID, destNodeUUID, writeDbmsImmediately);
            yield break;
        }
        public IEnumerator UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr loadedData)
        {
            mc.UnilateralRecursiveUpdateData(loadedData);
            yield break;
        }
        public IEnumerator UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr loadedData, bool transactional)
        {
            mc.UnilateralRecursiveUpdateData(loadedData, transactional);
            yield break;
        }
        public IEnumerator UnilateralRecursiveUpdateData(WrapCLoadedData2Ptr loadedData, bool transactional, bool writeDbmsImmediately)
        {
            mc.UnilateralRecursiveUpdateData(loadedData, transactional, writeDbmsImmediately);
            yield break;
        }
        public IEnumerator UnilateralRemoveData(WrapGUID rootUUID, WrapGUID removeUUID)
        {
            mc.UnilateralRemoveData(rootUUID, removeUUID);
            yield break;
        }
        public IEnumerator UnilateralRemoveData(WrapGUID rootUUID, WrapGUID removeUUID, bool writeDbmsImmediately)
        {
            mc.UnilateralRemoveData(rootUUID, removeUUID, writeDbmsImmediately);
            yield break;
        }
        public IEnumerator UnilateralUpdateData(WrapCPropNodePtr updateData)
        {
            mc.UnilateralUpdateData(updateData);
            yield break;
        }
        public IEnumerator UnilateralUpdateData(WrapCPropNodePtr updateData, bool writeDbmsImmediately)
        {
            mc.UnilateralUpdateData(updateData, writeDbmsImmediately);
            yield break;
        }
        public IEnumerator UnloadDataBySessionGuid(WrapGUID sessionGuid)
        {
            var b = new DBCache.QueryParameter();
            b.progressing = true;
            mc.UnloadDataBySessionGuid(sessionGuid, b);
            yield break;
        }

    }
}
