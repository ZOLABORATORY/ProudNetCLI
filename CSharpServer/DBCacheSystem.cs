using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using PNWrap2;

namespace CSharpServer
{
    public class DBCacheSystem
    {
        public IEnumerator Example_Coroutine()
        {
            if (RunnerDBCache == null)
            {
                //DBCache 가 초기화가 안됐으면 못 날림
                System.Console.Write("error!! DBCache Client Not Exist");
            }
            else
            {
                System.Console.Write("test dbcache query : ");
                


                Util.Log("----------------------------00-----------------------------");

                //0. 유저 정보를 읽어온다.
                {
                    //ExclusiveLoadData 는 use_users 에만 걸 수 있다.
                    DBCache.QueryParameter dq_original = new DBCache.QueryParameter();   //받아오는 패러매터

                    //개발자를 dq_original 에 받아온다.
                    //예를들어 이 세션을 Login_Server 로 가정한다.
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.RequestExclusiveLoadData("use_users", "name", "개발자", dq_original));

                    //이름 등의 데이터가 정상적으로 받아지는 것을 확인가능
                    var namen = dq_original.RootNode.GetFieldString("name");
                    Util.Log("dq_original Root User Name : " + namen);


                    //개발자를 dq에 받아온다.
                    //예를들어2, 이 세션을 Main_Server 로 가정한다.
                    DBCache.QueryParameter dq = new DBCache.QueryParameter();   //받아오는 패러매터
                    var ww = scCoroutine.Instance.Begin(RunnerDBCache.RequestExclusiveLoadData("use_users", "name", "개발자", dq));

                    //이 타이밍에 DBCacheServer로부터 Login_Server 세션에 OnDataUnloadRequest 요청을 보낸다.
                    //∵ 동시에 2개 이상의 세션이 한 RootNode를 접근할 수 없기 때문에
                    //※ 기존엔 이 요청이 오면 NullReferenceException이 발생했으나 이젠 아니도록 처리됨
                    //그러나, 현재 우리게임은 코루틴 구조이기 때문에 이 요청이 왔는지 알 수 없다 (콜백에 대한 응답을 적는 구조로 코딩되있지 않기 때문에)

                    //고로 가능한 로드한 데이터는 최대한 빨리 언로드하도록 한다...
                    //만약 어디선가 언로드가 일어나지 않는다면 최악의 경우 해당 노드는 서버 재접속 까지 영원히 ExclusiveLoad가 불가능하므로 철저한 처리가 필요함. (Exception 등으로)

                    //1틱에 0.01초니 대충 100틱정도(1초) 기다린다.
                    //1초나 걸리진 않겠지만, 이 시간이 대충 dq_original(Login Server 세션)이 할일을 하는 시간이라고 가정해본다.
                    int i = 0;
                    while (i++ < 100 && ww.br) yield return null;

                    //ww.br을 찍어봄으로써 아직 로드가 안됐음을 알 수 있다.
                    bool wait_Load_dq = ww.br;
                    Util.Log("dq not finished : " + wait_Load_dq);

                    //프로세스가 끝나고
                    //이제 dq_original(Login_Server 세션) 을 언로드한다.
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.UnloadDataBySessionGuid(dq_original.LoadedData.GetSessionGuid()));

                    //계속해서 dq(Main_Server 세션)로드를 기다려보면
                    yield return ww;

                    //로드가 끝나있다!! dq_original(Login_Server 세션)이 언로드 해줬기 때문에
                    //칼룸의 리스트 (대문자로 준다) 디버거로 열어보면 보인다
                    var ls = dq.RootNode.ColumnList;

                    //필드값을 딕셔너리로 모음 (칼룸명은 대문자로 준다) 역시 디버거로 열어보면 보인다
                    var dic = dq.RootNode.TotalFieldDictionary;
                    
                    //이것저것 로그를 찍어본다
                    Util.Log("test : select * from use_users where `name` = '개발자' -(result:)> ");
                    Util.Log("UUID : " + dq.RootNode.GetUUID());
                    Util.Log("id : " + dq.RootNode.GetFieldString("id"));
                    Util.Log("email : " + dq.RootNode.GetFieldString("email"));
                    Util.Log("passwd : " + dq.RootNode.GetFieldString("passwd"));
                    Util.Log("name : " + dq.RootNode.GetFieldString("name"));
                    Util.Log("register date: " + dq.RootNode.GetFieldString("date"));

                    //모든 카드 받아옴 (use_skills로부터) : 역시 칼룸명은 대문자로 줘야한다.
                    var ls_mycards = dq.RootNode.FindChildren("USE_SKILLS");
                    Util.Log("개발자 cards = ");
                    foreach (var v in ls_mycards) Util.Log(v.GetFieldString("card"));

                    //모든 자식 : 역시 디버거로 열어보면 안다
                    var dic_myChildren = dq.RootNode.GetChildDictionary;

                    //언로드 : 언로드는 완료인지 아닌지 알려주지 않는다. 다만 LoadDataExclusive시 time을 재서 기다릴 뿐.
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.UnloadDataBySessionGuid(dq.LoadedData.GetSessionGuid()));
                }

                Util.Log("----------------------------01-----------------------------");

                //신규 유저 생성 : 생성할때는 Add 가 아닌 ExclusiveLoadNew 를 한다 (use_users 나 use_duel 테이블에 넣을때만 ExclusiveLoadNew)
                PNWrap2.WrapGUID uuid_created;
                {
                    DBCache.QueryParameter dq = new DBCache.QueryParameter();

                    //노드 생성
                    WrapCPropNodePtr wc = new WrapCPropNodePtr("use_users");

                    //필수 정보는 전부 입력한다.
                    wc.SetField("name", "이것이 바로 테스트 계정!!!");
                    wc.SetField("email", "email_test@email_test.email_test");
                    wc.SetField("passwd", "password");
                    wc.SetField("role", "ROLE_USER");
                    wc.SetField("iconpath", "url(/2dimensia/images/user_image_box.png)");
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.RequestExclusiveLoadNewData("use_users", wc, dq));

                    //dq.RootNode는 얻어온 노드의 UUID
                    uuid_created = dq.RootNode.GetUUID();
                    Util.Log("insert finished : " + uuid_created);

                    //언로드
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.UnloadDataBySessionGuid(dq.LoadedData.GetSessionGuid()));
                }

                Util.Log("----------------------------02-----------------------------");

                //생성한 유저 데이터 변경 : 카드를 준다.
                //주의1 : Add 시에는 반드시 full data를 넣어야한다 (캐싱을 하기 때문에 DB기본값이 있다고 해도 안넣으면 에러난다.)
                //주의2 : 독점적 로드 상태여야만 하위 데이터를 변경이 가능하다. 만약 독점로딩상태가 아니라면 코루틴이 응답하지 않을 것이다.
                {
                    //다시 독점 로드 (원래대로라면 아까 '신규 유저 생성'후 언로드를 안하는게 더 좋지만, 예제 코드의 깔끔함을 위해서 언로드-로드를 하기로 함
                    DBCache.QueryParameter dq = new DBCache.QueryParameter();   //받아오는 패러매터
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.RequestExclusiveLoadDataByGuid("use_users", uuid_created, dq));

                    Util.Log("create card begin");

                    List <CoroutineClass> coroutines = new List<CoroutineClass>();

                    PNWrap2.WrapCPropNodePtr wp = new PNWrap2.WrapCPropNodePtr("use_skills");
                    wp.SetField("card", 101001);
                    wp.SetField("deck", 1);
                    wp.SetField("isBasic", 0);
                    wp.SetField("tag", 1);
                    wp.SetField("skin", 1);
                    wp.SetField("firstpick", 0);
                    wp.SetField("owner", 0);
                    wp.SetField("date", DateTime.Now);
                    wp.SetField("id", 0);

                    PNWrap2.WrapCPropNodePtr wp2 = new PNWrap2.WrapCPropNodePtr("use_skills");
                    wp.SetField("card", 101002);
                    wp.SetField("deck", 2);
                    wp.SetField("isBasic", 3);
                    wp.SetField("tag", 4);
                    wp.SetField("skin", 1);
                    wp.SetField("firstpick", 0);
                    wp.SetField("owner", 1);
                    wp.SetField("date", DateTime.Now);
                    wp.SetField("id", 0);

                    PNWrap2.WrapCPropNodePtr wp3 = new PNWrap2.WrapCPropNodePtr("use_skills");
                    wp.SetField("card", 101002);
                    wp.SetField("deck", 2);
                    wp.SetField("isBasic", 3);
                    wp.SetField("tag", 4);
                    wp.SetField("skin", 1);
                    wp.SetField("firstpick", 0);
                    wp.SetField("owner", 1);
                    wp.SetField("date", DateTime.Now);
                    wp.SetField("id", 0);

                    coroutines.Add(scCoroutine.Instance.Begin(RunnerDBCache.UnilateralAddData(uuid_created, uuid_created, wp)));
                    coroutines.Add(scCoroutine.Instance.Begin(RunnerDBCache.UnilateralAddData(uuid_created, uuid_created, wp2)));
                    foreach (var v in coroutines) yield return v;

                    //Unilateral 이 끝나면 Request를 이용, db에 한번에 넣는다. (Request가 전송되면 Unilateral이 업데이트된다)
                    var dqq = new DBCache.QueryParameter();
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.RequestAddData(uuid_created, uuid_created, wp3, dqq));

                    
                    Util.Log("create card finished : "+dq.RootNode.GetUUID().ToString());

                    //언로드
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.UnloadDataBySessionGuid(dq.LoadedData.GetSessionGuid()));

                }
                
                //생성한 유저에게 덱 부여

                //생성한 유저 제거
                {
                    DBCache.QueryParameter dq = new DBCache.QueryParameter();   //받아오는 패러매터
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.RequestExclusiveLoadDataByGuid("use_users", uuid_created, dq));

                    dq = new DBCache.QueryParameter();
                    yield return scCoroutine.Instance.Begin(RunnerDBCache.RequestRemoveData(uuid_created, uuid_created, dq));
                    Util.Log("delete test account. result : "+dq.result);
                }

                {
                //작업순서
                //1. comm.dll 을 쓰나? 이게 최선인가? ㅇㅇ 이 정의는 있어야지...
                //2. 즉, comm.dll 은 있어야한다.
                }

                Util.Log("unload queried");


                Util.Log("----------------------------All Finished-----------------------------");
            }
        }


        public DBCacheSystem()
        {

        }

        public static DBCacheSystem Instance
        {
            get
            {
                if (_instance == null)
                    _instance = new DBCacheSystem();
                return _instance;
            }
        }
        static DBCacheSystem _instance = null;

        //DB Cache 에서 콜백되는 함수 델리게이터 타입
        delegate void OnDBLoadFinished(PNWrap2.WrapCCallBackArgs arg);

        //DLL에서 임포트한 함수들을 맵핑한다
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnExclusiveLoadDataComplete(OnDBLoadFinished callback);        
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnDataUnloadRequested(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnDataForceUnloaded(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnAddDataFailed(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnAddDataSuccess(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnUpdateDataFailed(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnUpdateDataSuccess(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnRemoveDataFailed(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnRemoveDataSuccess(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnNonExclusiveSnapshotDataComplete(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnNonExclusiveAddDataAck(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnNonExclusiveRemoveDataAck(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnNonExclusiveModifyValueSuccess(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnNonExclusiveModifyValueFailed(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnNonExclusiveSetValueIfSuccess(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnNonExclusiveSetValueIfFailed(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnSomeoneAddData(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnSomeoneRemoveData(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnSomeoneModifyValue(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnSomeoneSetValue(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void Register_OnAccessError(OnDBLoadFinished callback);
        [DllImport("PNWrap2.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PrintHello();
        
        public PNWrap2.MainClass mc;
        public DBCache RunnerDBCache;

        OnDBLoadFinished OnExclusiveLoadDataComplete;
        OnDBLoadFinished OnDataUnloadRequested;
        OnDBLoadFinished OnDataForceUnloaded;
        OnDBLoadFinished OnAddDataFailed;
        OnDBLoadFinished OnAddDataSuccess;
        OnDBLoadFinished OnUpdateDataFailed;
        OnDBLoadFinished OnUpdateDataSuccess;
        OnDBLoadFinished OnRemoveDataFailed;
        OnDBLoadFinished OnRemoveDataSuccess;
        OnDBLoadFinished OnNonExclusiveSnapshotDataComplete;
        OnDBLoadFinished OnNonExclusiveAddDataAck;
        OnDBLoadFinished OnNonExclusiveRemoveDataAck;
        OnDBLoadFinished OnNonExclusiveModifyValueSuccess;
        OnDBLoadFinished OnNonExclusiveModifyValueFailed;
        OnDBLoadFinished OnNonExclusiveSetValueIfSuccess;
        OnDBLoadFinished OnNonExclusiveSetValueIfFailed;
        OnDBLoadFinished OnSomeoneAddData;
        OnDBLoadFinished OnSomeoneRemoveData;
        OnDBLoadFinished OnSomeoneModifyValue;
        OnDBLoadFinished OnSomeoneSetValue;
        OnDBLoadFinished OnAccessError;

        /// <summary>
        /// 여기서 시작한다
        /// </summary>
        public void Start()
        {
            //최초의 테스트 : dll 함수가 제대로 임포트 됐는지 화면에 헬로월드 2개를 찍는다
            PrintHello();

            //메인클래스 생성 (dll 안에 있음)
            mc = new MainClass();

            //Test 함수를 OnExclusiveLoadDataComplete 콜백에 등록한다 (나중에 코루틴으로 바꾸던 해야한다)
            Register_OnExclusiveLoadDataComplete(OnExclusiveLoadDataComplete = new OnDBLoadFinished(CB_OnExclusiveLoadDataComplete));
            Register_OnDataUnloadRequested(OnDataUnloadRequested = new OnDBLoadFinished(CB_OnDataUnloadRequested));
            Register_OnDataForceUnloaded(OnDataForceUnloaded = new OnDBLoadFinished(CB_OnDataForceUnloaded));
            Register_OnAddDataFailed(OnAddDataFailed = new OnDBLoadFinished(CB_OnAddDataFailed));
            Register_OnAddDataSuccess(OnAddDataSuccess = new OnDBLoadFinished(CB_OnAddDataSuccess));
            Register_OnUpdateDataFailed(OnUpdateDataFailed = new OnDBLoadFinished(CB_OnUpdateDataFailed));
            Register_OnUpdateDataSuccess(OnUpdateDataSuccess = new OnDBLoadFinished(CB_OnUpdateDataSuccess));
            Register_OnRemoveDataFailed(OnRemoveDataFailed = new OnDBLoadFinished(CB_OnRemoveDataFailed));
            Register_OnRemoveDataSuccess(OnRemoveDataSuccess = new OnDBLoadFinished(CB_OnRemoveDataSuccess));
            Register_OnNonExclusiveSnapshotDataComplete(OnNonExclusiveSnapshotDataComplete = new OnDBLoadFinished(CB_OnNonExclusiveSnapshotDataComplete));
            Register_OnNonExclusiveAddDataAck(OnNonExclusiveAddDataAck = new OnDBLoadFinished(CB_OnNonExclusiveAddDataAck));
            Register_OnNonExclusiveRemoveDataAck(OnNonExclusiveRemoveDataAck = new OnDBLoadFinished(CB_OnNonExclusiveRemoveDataAck));
            Register_OnNonExclusiveModifyValueSuccess(OnNonExclusiveModifyValueSuccess = new OnDBLoadFinished(CB_OnNonExclusiveModifyValueSuccess));
            Register_OnNonExclusiveModifyValueFailed(OnNonExclusiveModifyValueFailed = new OnDBLoadFinished(CB_OnNonExclusiveModifyValueFailed));
            Register_OnNonExclusiveSetValueIfSuccess(OnNonExclusiveSetValueIfSuccess = new OnDBLoadFinished(CB_OnNonExclusiveSetValueIfSuccess));
            Register_OnNonExclusiveSetValueIfFailed(OnNonExclusiveSetValueIfFailed = new OnDBLoadFinished(CB_OnNonExclusiveSetValueIfFailed));
            Register_OnSomeoneAddData(OnSomeoneAddData = new OnDBLoadFinished(CB_OnSomeoneAddData));
            Register_OnSomeoneRemoveData(OnSomeoneRemoveData = new OnDBLoadFinished(CB_OnSomeoneRemoveData));
            Register_OnSomeoneModifyValue(OnSomeoneModifyValue = new OnDBLoadFinished(CB_OnSomeoneModifyValue));
            Register_OnSomeoneSetValue(OnSomeoneSetValue = new OnDBLoadFinished(CB_OnSomeoneSetValue));
            Register_OnAccessError(OnAccessError = new OnDBLoadFinished(CB_OnAccessError));

            //디비 캐시 서버에 접속!
            mc.Start("localhost", 33940);

            //접속이 성공할때까지 기다림
            while (!mc.ConnectSucceeded()) ;

            //접속이 성공됐다면 
            if (mc.ConnectSucceeded())
            {
                Util.Log("connect succeeded");

                //dbcache 객체 생성
                RunnerDBCache = new DBCache(mc);
            }
        }

        
        /// <summary>
        /// 쿼리패러매터에 받은 item을 적는다.
        /// </summary>
        /// <param name="qp"></param>
        /// <param name="items"></param>
        void write_Queryparam(DBCache.QueryParameter qp, List<WrapCItem> items)
        {
            foreach (var v in items)
            {
                var data = v.m_loadedData;
                var root = v.m_loadedData.GetRootNode();

                if (qp.m_firstLoadData == null)
                    qp.m_firstLoadData = data;
                else
                {
                    if (qp.m_LoadedDatas == null) qp.m_LoadedDatasCreateIfNull.Add(qp.m_firstLoadData);
                    qp.m_LoadedDatas.Add(data);
                }

                if (qp.m_firstRootNode == null)
                    qp.m_firstRootNode = root;
                else
                {
                    if (qp.m_RootNodes == null) qp.m_rootNodesCreateIfNull.Add(qp.m_firstRootNode);
                    qp.m_RootNodes.Add(root);
                }
            }
        }

        void CB_OnExclusiveLoadDataComplete(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnExclusiveLoadDataComplete;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }
        void CB_OnDataUnloadRequested(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = new DBCache.QueryParameter();
            qp.result = DBCache.Result.OnDataUnloadRequested;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }

		void CB_OnDataForceUnloaded(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = new DBCache.QueryParameter();
            qp.result = DBCache.Result.OnDataForceUnloaded;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }

		void CB_OnAddDataFailed(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnAddDataFailed;
            qp.progressing = false;
        }

		void CB_OnAddDataSuccess(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnAddDataSuccess;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }


		void CB_OnUpdateDataFailed(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnUpdateDataFailed;
            qp.progressing = false;
        }

		void CB_OnUpdateDataSuccess(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnUpdateDataSuccess;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }

		void CB_OnRemoveDataFailed(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnRemoveDataFailed;
            qp.progressing = false;
        }

		void CB_OnRemoveDataSuccess(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnRemoveDataSuccess;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }

		// 	void CB_OnNonExclusiveSnapshotDataFailed(PNWrap2.WrapCCallBackArgs args)
		// 	void CB_OnNonExclusiveSnapshotDataSuccess(PNWrap2.WrapCCallBackArgs args)
		void CB_OnNonExclusiveSnapshotDataComplete(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnNonExclusiveSnapshotDataComplete;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }

		void CB_OnNonExclusiveAddDataAck(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnNonExclusiveAddDataAck;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }
		void CB_OnNonExclusiveRemoveDataAck(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnNonExclusiveRemoveDataAck;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }

		void CB_OnNonExclusiveModifyValueSuccess(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnNonExclusiveModifyValueSuccess;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }
		void CB_OnNonExclusiveModifyValueFailed(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnNonExclusiveModifyValueFailed;
            qp.progressing = false;
        }

		void CB_OnNonExclusiveSetValueIfSuccess(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnNonExclusiveSetValueIfSuccess;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }
		void CB_OnNonExclusiveSetValueIfFailed(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnNonExclusiveSetValueIfFailed;
            qp.progressing = false;
        }

		void CB_OnSomeoneAddData(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnSomeoneAddData;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }
		void CB_OnSomeoneRemoveData(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnSomeoneRemoveData;
            qp.progressing = false;
        }

		void CB_OnSomeoneModifyValue(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnSomeoneModifyValue;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }
		void CB_OnSomeoneSetValue(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnSomeoneSetValue;
            write_Queryparam(qp, args.m_items);
            qp.progressing = false;
        }
        
		void CB_OnAccessError(PNWrap2.WrapCCallBackArgs args)
        {
            var qp = (DBCache.QueryParameter)args.comment;
            qp.result = DBCache.Result.OnAccessError;
            qp.progressing = false;
        }

        

        /// <summary>
        /// RequestExclusiveLoadData 성공시 콜백된다
        /// </summary>
        /// <param name="args"></param>
        void Test(PNWrap2.WrapCCallBackArgs args)
        {
            Util.Log(args.comment);

            //읽어온 것들을 리스트로 뽑아서
            var ls = args.m_items;
            foreach (var v in ls)
            {
                //찍는다 : 이건 C++ 의 SimpleTest 예제랑 동일함
                var nd = v.m_loadedData.GetRootNode();
                Util.Log(nd.GetFieldString("name"));
                Util.Log(nd.GetFieldString("email"));
                Util.Log(nd.GetFieldString("passwd"));

                //언로드한다
                mc.UnloadDataBySessionGuid(v.m_sessionGuid, new DBCache.QueryParameter());
            }
        }

    }
}
