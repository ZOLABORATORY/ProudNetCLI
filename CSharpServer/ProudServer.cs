using System;
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
        public bool m_runLoop;

        NetServer m_netServer = new NetServer();

        ThreadPool netWorkerThreadPool = new ThreadPool(8);
        ThreadPool userWorkerThreadPool = new ThreadPool(8);

        
        public static List<HostID> TotalClientIDs = new List<HostID>();

        DBCacheSystem db;

        public ProudServer()
        {
            m_runLoop = true;
            
            db = DBCacheSystem.Instance;

            m_netServer.ConnectionRequestHandler = (AddrPort clientAddr, ByteArray userDataFromClient, ByteArray reply) =>
            {
                reply = new ByteArray();
                reply.Clear();
                return true;
            };

            m_netServer.ClientHackSuspectedHandler = (HostID clientID, HackType hackType) =>
            {

            };

            m_netServer.ClientJoinHandler = (NetClientInfo info) =>
            {
                Console.WriteLine("onClientJoin: {0}", info.hostID);
                TotalClientIDs.Add(info.hostID);
            };

            m_netServer.ClientLeaveHandler = (NetClientInfo info, ErrorInfo eInfo, ByteArray comment) =>
            {
                Console.WriteLine("onClientLeave: {0}", info.hostID);
                TotalClientIDs.Remove(info.hostID);
            };

            m_netServer.ErrorHandler = (ErrorInfo einfo) =>
            {
                Console.WriteLine("onError! {0}", einfo.ToString());
            };

            m_netServer.WarningHandler = (ErrorInfo einfo) =>
            {
                Console.WriteLine("onWarning! {0}", einfo.ToString());
            };

            m_netServer.ExceptionHandler = (Exception e) =>
            {
                Console.WriteLine("onException! {0}", e.Message.ToString());
            };

            m_netServer.InformationHandler = (ErrorInfo einfo) =>
            {
                Console.WriteLine("onInformaiton! {0}", einfo.ToString());
            };

            m_netServer.NoRmiProcessedHandler = (RmiID rmiID) =>
            {
                Console.WriteLine("onNoRmiProcessed! {0}", rmiID);
            };

            m_netServer.P2PGroupJoinMemberAckCompleteHandler = (HostID groupHostID, HostID memberHostID, ErrorType result) =>
            {

            };

            m_netServer.TickHandler = (object context) =>
            {

            };

            m_netServer.UserWorkerThreadBeginHandler = () =>
            {

            };

            m_netServer.UserWorkerThreadEndHandler = () =>
            {

            };

            m_netServer.ReceiveUserMessageHandler = (HostID sender, RmiContext rmiContext, ByteArray payload) =>
            {
                Util.Log("Message Received");
                Util.Log("sender = " + sender);
            };

        }

        public void Start()
        {
            StartServerParameter sp = new StartServerParameter();
            //sp.protocolVersion = new Nettention.Proud.Guid(SngCommon.Vars.g_sngProtocolVersion); guid설정
            sp.tcpPorts = new IntArray();
            sp.tcpPorts.Add(4001);
            sp.SetExternalNetWorkerThreadPool(netWorkerThreadPool);
            sp.SetExternalUserWorkerThreadPool(userWorkerThreadPool);
            db = DBCacheSystem.Instance;
            m_netServer.SetMessageMaxLength(262144, 131072);
            //시작 호출
            m_netServer.Start(sp);
            Core.Instance.Initialize();
        }

        public void Dispose()
        {
            m_netServer.Dispose();
        }
    }
}
