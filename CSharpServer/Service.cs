using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Nettention.Proud;
using PNWrap2;

namespace CSharpServer
{
    public partial class ProudServer
    {
        //public IEnumerator Request_ServiceAchivementChange(Nettention.Proud.HostID remote, Nettention.Proud.RmiContext rmiContext, int userID, System.Collections.Generic.Dictionary<int, int> questRefIDs_amount)
        //{
        //    Util.Log("Service Achivement Change Requested");
        //    Util.Log("HostID : " + remote);
        //    Util.Log("RmiID : " + Server_C2S_Test_ForCS.Common.Request_ServiceAchivementChange);

        //    string resultStr = string.Empty;
        //    string tag = Comm.Def.AchivementProgressKey;

        //    DBCache.QueryParameter dq = new DBCache.QueryParameter();
        //    yield return scCoroutine.Instance.Begin(db.RunnerDBCache.RequestExclusiveLoadData("use_users", "id", userID, dq));

        //    var childs = dq.RootNode.GetChildDictionary;
        //    List<WrapCPropNodePtr> ls;
        //    if (childs.TryGetValue("USE_PROGRESS", out ls))
        //    {
        //        foreach (var kv in questRefIDs_amount)
        //        {
        //            var targetNode = ls.Find((WrapCPropNodePtr wrapC) =>
        //            {
        //                string name = wrapC.TotalFieldDictionary["NAME"].strval;
        //                if (name == tag + kv.Key)
        //                {
        //                    return true;
        //                }
        //                return false;
        //            });

        //            if (targetNode != null)
        //            {
        //                int before_value = targetNode.GetFieldInt("value");
        //                int addr = kv.Value;
        //                targetNode.SetField("value", before_value + addr);
        //                scCoroutine.Instance.Begin(db.RunnerDBCache.RequestUpdateData(targetNode, new DBCache.QueryParameter()));
        //            }
        //            else
        //            {
        //                //TODO : 새로 노드 생성하는 로직이 필요함
        //                var uuid = dq.RootNode.GetUUID();
        //                var wc = ServerUtil.CreateNewerProgressNode(tag + kv.Key, kv.Value);
        //            }
        //        }
        //    }
        //    else
        //    {
        //        //프로그래스가 아예 없는 상황
        //        //TODO : 유즈 프로그래스 테이블 자체를 새로 생성 후 딕셔너리 안의 각 노드들 생성해야 함
        //    }
        //    yield return scCoroutine.Instance.Begin(db.RunnerDBCache.UnloadDataBySessionGuid(dq.LoadedData.GetSessionGuid()));

        //}
    }
}
