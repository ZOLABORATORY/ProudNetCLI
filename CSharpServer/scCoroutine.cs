using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Collections;

namespace CSharpServer
{

    public class scCoroutine
    {
        public int CurrentTick = 1;

#if LOG_ALL
    List<CoroutineClassNew> RunThisTick = new List<CoroutineClassNew>();
#endif

        public CoroutineClass NULL
        {
            get
            {
                return new CoroutineClass(this, nopCoroutine());
            }
        }

        IEnumerator nopCoroutine()
        {
            yield break;
        }

        static scCoroutine _instance = null;
        public static scCoroutine Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new scCoroutine();
                }
                return _instance;
            }
        }

        object mutexlocker = new object();

        private scCoroutine()
        {
            //System.Timers.Timer t = new System.Timers.Timer();
            MyTimer = new System.Timers.Timer();
            MyTimer.Elapsed += TimerUpdate;
            MyTimer.Interval = 16.67;  //16.67ms = 1초에 60번 루프
            MyTimer.Start();
        }

        public double UpdateInterval
        {
            get
            {
                return MyTimer.Interval;
            }
            set
            {
                MyTimer.Interval = value;
            }
        }
        
        System.Timers.Timer MyTimer;

        void TimerUpdate(object sender, System.Timers.ElapsedEventArgs e)
        {
            RunCoroutinesInList_A_Tick(null);
            ++CurrentTick;
        }

        public static void StopAll()
        {
            if (_instance == null)
                return;

            foreach (List<CoroutineClass> lscc in _instance.dicTotalCoroutines.Values)
            {
                foreach (CoroutineClass cc in lscc)
                    cc.br = false;
            }
        }

        public static void StopAll(int tag)
        {
            if (_instance == null)
                return;

            foreach (List<CoroutineClass> lscc in _instance.dicTotalCoroutines.Values)
            {
                foreach (CoroutineClass cc in lscc)
                {
                    if (cc.tag == tag)
                        cc.br = false;
                }
            }
        }

        public override string ToString()
        {
            string ostr = "scCoroutineNew[\n";
            foreach (List<CoroutineClass> lscc in _instance.dicTotalCoroutines.Values)
            {
                foreach (CoroutineClass cc in lscc)
                {
                    ostr += cc.ToString() + "\n-----------------------------------------\n";
                }
            }
            ostr += "\n]--------------------------------------";
            return ostr;
        }

        public string ToString(int tag)
        {
            string ostr = "scCoroutineNew[\n";
            foreach (List<CoroutineClass> lscc in _instance.dicTotalCoroutines.Values)
            {
                foreach (CoroutineClass cc in lscc)
                {
                    if (tag == cc.tag)
                        ostr += cc.ToString() + "\n-----------------------------------------\n";
                }
            }
            ostr += "\n]--------------------------------------";
            return ostr;
        }


        void Update()
        {
            RunCoroutinesInList_A_Tick(null);
            ++CurrentTick;
        }


        public CoroutineClass Begin(IEnumerator wanna_run, int tag = 0)
        {
            CoroutineClass cc = new CoroutineClass(this, wanna_run);
            cc.myCoroutine = this;
            cc.tag = tag;

            do
            {
                cc.MoveNext(true);
            }
            while (
            //아직 안 끝났으며, 코루틴에 의해 막혔는데, 그놈이 노딜레이로 끝났다면 계속함
            cc.br
            && cc.coroutine.Current is CoroutineClass
            && !((CoroutineClass)cc.coroutine.Current).br
                );

            //내가 끝났다면 노딜레이 피니시
            if (!cc.br)
            {
                cc.RunFinishFunction();
                return cc;
            }
            else
            {
                //노 딜레이로 끝나지 않음 = 바로 안 끝났다는 이야기
                //다음의 케이스가 있음
                // 0. 내가 끝났는데 나를 기다리게 하는놈이 있을 수 없음.
                // 1. 난 아직 안 끝났고, 나를 기다리게 한 게 함수이고, 그놈이 nodelayfinish라면 -> 앞에서 이미 체크됨
                // 2. 난 아직 안 끝났고, 나를 기다리게 한 게 함수이고, 그놈이 delayed-finish라면 -> ... 여기서 그럴수가 있나? 걍 리턴
                // 3. 난 아직 안 끝났고, 나를 기다리게 한 게 함수이고, 그놈이 not yet finished 라면 -> 내가 이미 실행됐으므로 return
                // 4. 난 아직 안 끝났고, 나를 기다리게 한 게 null이면 -> return

                //2 : 불가

                /*
                //3
                if(cc.coroutine.Current is CoroutineClass)
                {
                    Add(cc.coroutine.Current, cc);
                    return cc;
                }
                else
                //4 아직 안 끝남
                if (cc.coroutine.Current == null)
                {
                    Add(cc.coroutine.Current, cc);
                    return cc;
                }
                */

                //3과 4는 처리방식이 동일하므로 그냥 이렇게 처리. 그러나 위쪽에 로직을 남겨놓는 이유는 code-reading을 위해
                Add(cc.coroutine.Current, cc);
                return cc;
            }
        }




        /// <summary>
        /// 동시에 실행되도 되는 코루틴을 다 실행해버린다.
        /// </summary>
        /// <param name="cList">이 입력값만 누군가의 복사값이면 </param>
        public void RunCoroutinesInList_A_Tick(object seed_reason)
        {
            if (seed_reason == null)
                seed_reason = CoroutineClass.null_key;

            List<object> will_run_reasons = new List<object>();

            //일단 cList 에 들어오는 놈들은 누군가에 의해 막혀본 경험 있는 놈들이다
            //기본적으로 할일 : cList를 돌면서 전부 MoveNext(Surpress)
            //결과에 따른 케바케 처리
            //!br -> 끝났으므로 나를 finished list 에 추가해준다. 
            //       
            //br, by coroutine
            // -> StuckedByCoroutine 으로 보낸다.
            //br, by null
            // -> StuckedByNull 로 보낸다.

            will_run_reasons.Add(seed_reason);

#if LOG_ALL
        RunThisTick.Clear();
#endif


            do
            {
                //이 reason은 제거되었다.
                object current_reason = will_run_reasons[will_run_reasons.Count - 1];
                if (current_reason == null)
                    current_reason = CoroutineClass.null_key;

                will_run_reasons.RemoveAt(will_run_reasons.Count - 1);

                List<CoroutineClass> lscc = Get(current_reason);
                if (lscc != null)
                {
                    CoroutineClass[] ccs = lscc.ToArray();
                    //전부 돌린다.
                    foreach (CoroutineClass cc in ccs)
                    {
#if LOG_ALL
                    RunThisTick.Add(cc);
#endif
                        if (current_reason == CoroutineClass.null_key)
                            cc.MoveNext(false);
                        else
                            cc.MoveNext(true);

                        //즉시 끝나는 코루틴에 의해 막혀있는 경우 연속적으로 실행을 시킨다.
                        while (
                                //아직 안 끝났으며, 코루틴에 의해 막혔는데, 그놈이 노딜레이로 끝났다면 계속함
                                cc.br
                                && cc.coroutine.Current is CoroutineClass
                                && !((CoroutineClass)cc.coroutine.Current).br
                                    )
                        {
                            cc.MoveNext(true);
                        }

                        if (cc.br)
                        {
                            //만약 안 끝났다면 재등록
                            if (cc.coroutine.Current == null)
                                Add(CoroutineClass.null_key, cc);
                            else
                                Add(cc.coroutine.Current, cc);
                        }
                        else
                        {
                            //끝났다면 나에 의해 멈춰있는 애들을 실행리스트에 등록
                            if (has(cc))
                            {
                                will_run_reasons.Add(cc);
                            }
                            RemoveThis(cc);
                        }
                    }
                }
            } while (will_run_reasons.Count != 0);


#if LOG_ALL
        string log = "Tick = " + CurrentTick +"\n";
        foreach (var v in RunThisTick)
        {
            log += v.ToString() + "\n";
        }
        Debug.Log(log);
#endif
        }

        Dictionary<object, List<CoroutineClass>> dicTotalCoroutines = new Dictionary<object, List<CoroutineClass>>();

        bool has(object reason)
        {
            lock (mutexlocker)
            {
                if (reason == null)
                    reason = CoroutineClass.null_key;
                return dicTotalCoroutines.ContainsKey(reason);
            }
        }

        /// <summary>
        /// dictionary 로부터 reason을 멈춤원인으로 하는 코루틴을 전부 가져온다.
        /// </summary>
        /// <param name="reason"></param>
        /// <returns></returns>
        List<CoroutineClass> Get(object reason)
        {
            lock(mutexlocker)
            {
                List<CoroutineClass> outv = null;
                if (reason == null)
                    reason = CoroutineClass.null_key;

                if (dicTotalCoroutines.TryGetValue(reason, out outv))
                    return outv;

                return null;
            }
        }

        /// <summary>
        /// dictionary에 reason을 멈춤원인으로 하는 코루틴을 등록
        /// </summary>
        /// <param name="reason"></param>
        /// <param name="cc"></param>
        void Add(object reason, CoroutineClass cc)
        {
            lock(mutexlocker)
            {
                if (reason == null)
                    reason = CoroutineClass.null_key;

                if (cc.key_of_mylist == reason)
                    return;
                else
                {
                    RemoveThis(cc);
                }

                List<CoroutineClass> lsCC = Get(reason);
                if (lsCC == null)
                {
                    lsCC = new List<CoroutineClass>();
                    dicTotalCoroutines.Add(reason, lsCC);
                }

                lsCC.Add(cc);
                cc.key_of_mylist = reason;
                cc.mylist = lsCC;
            }
        }

        /// <summary>
        /// dictionary에 등록되있던 코루틴 제거 : 이 코루틴에 의해 stuck 되어있던 애들의 실행은 보장하지 않는다.
        /// </summary>
        /// <param name="cc"></param>
        void RemoveThis(CoroutineClass cc)
        {
            lock (mutexlocker)
            {
                if (cc.key_of_mylist == null)
                    return;

                cc.mylist.Remove(cc);
                if (cc.mylist.Count == 0)
                {
                    dicTotalCoroutines.Remove(cc.key_of_mylist);
                }

                cc.mylist = null;
                cc.key_of_mylist = null;
            }
        }




    }

}
