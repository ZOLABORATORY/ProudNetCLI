using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace CSharpServer
{
    public class Core
    {
        public const bool LogDetail = false;
        public static void Log(object o)
        {
            if (LogDetail) Util.Log(o);
        }

        public static void SleepSometime()
        {
            Util.Log("begin wait");
            int i = int.MaxValue;
            while (i > 0) --i;
            Util.Log("end wait");
        }

        public static Core Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new Core();
                }
                return _instance;
            }
        }
        static Core _instance = null;
        Core()
        {

        }

        public static int port;

        public Util.DelegateVoidNoParam UpdateEvent = null;

        /// <summary>
        /// 메인 업데이트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void Update(object sender, System.Timers.ElapsedEventArgs e)
        {
            if (UpdateEvent != null)
            {
                UpdateEvent();
            }
        }

        int accumtime_for_log_batched = 0;

        /// <summary>
        /// 초기화
        /// </summary>
        public void Initialize()
        {
            time = new System.Timers.Timer(10);      //10ms = 0.01s = 1tick
            time.Elapsed += Update;
            time.AutoReset = true;
            time.Enabled = true;
        }

        /// <summary>
        /// 업데이트 타이머
        /// </summary>
        System.Timers.Timer time;
    }
}
