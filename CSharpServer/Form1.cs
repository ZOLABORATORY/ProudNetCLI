using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace CSharpServer
{


    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 테스트서버용 로드 txt 파일을 사용할지 (false라면 리얼서버용 txt파일을 사용)
        /// </summary>
        public static bool TestServer = true;

        private void Form1_Load(object sender, EventArgs e)
        {
            //DB초기화
            try
            {
                string defaultFileName = TestServer ? "c:\\CSharpServerLocationForTest.txt" : "c:\\CSharpServerLocation.txt";

                var fs = new FileStream(defaultFileName, FileMode.Open, FileAccess.Read);
                StreamReader sr = new StreamReader(fs);
                string str = sr.ReadToEnd();
                str = str.Replace("\r\n", "\n");
                var strs = str.Split('\n');
                sr.Close();
                fs.Close();
                if (strs.Length < 4)
                    throw new Exception();
                DB.DataSource = strs[0];
                DB.DataBase = strs[1];
                DB.UserID = strs[2];
                DB.Password = strs[3];
            }
            catch (System.Exception ex)
            {
                //nop : DB에 기본값이 설정되있음
                Util.Log("Using DB Default Setting");
            }

            //셋팅된 정보대로 DB접속을 초기화 (구 DB.Query, Transaction 을 사용가능하게 함)
            DBSystem.Instance.Initialize();

            //db cache system 에 접속가능하게 만든다. (DB캐시 사용가능하게 함)
            DBCacheSystem.Instance.Start();

            //테스트 코드를 날려본다. (DB캐시에 테스트 코드 발송)
            scCoroutine.Instance.Begin(DBCacheSystem.Instance.Example_Coroutine());

            ProudServer s = new ProudServer();
            s.Start();

        }
    }
}
