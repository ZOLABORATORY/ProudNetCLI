using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpServer
{

    public class CoroutineClass : ObjectYield
    {

        static int id_generator = 0;
        public int ID;

        /// <summary>
        /// waiter_list 에 자기자신을 포함한, 자기가 기다리는 대기열의 모든 리스트를 내보내준다.
        /// </summary>
        /// <param name="waiter_list"></param>
        /// <returns></returns>
        public void MakeWaiterList(List<CoroutineClass> waiter_list)
        {
            waiter_list.Clear();
            object waiter = coroutine.Current;
            waiter_list.Add(this);

            while (waiter != null && waiter.GetType() == typeof(CoroutineClass))
            {
                CoroutineClass c_waiter = (CoroutineClass)waiter;
                waiter_list.Add(c_waiter);
                waiter = c_waiter.coroutine.Current;
            }
        }

        //use it like const
        public static object null_key = new object();

        //position
        public object key_of_mylist = null;
        public List<CoroutineClass> mylist = null;
        public scCoroutine myCoroutine = null;

        //tag : when clear, only tagged is cleared
        public int tag = 0;

        public override string ToString()
        {
            string str = "CoroutineClass{(ID:" + ID + " / track:" + tag + ")" + coroutine + "}, delayed by{" + (coroutine.Current == null ? "null" : coroutine.Current) + "} : finished(" + !br + ")";
            return str;
        }

        public int last_runned_tick = 0;
        public IEnumerator coroutine;

        //bool _br = false;

        public bool br = true;
        //     {
        //         get
        //         {
        //             return _br;
        //         }
        //         set
        //         {
        //             Debug.Log("br from(" + _br + ") to(" + value + ") : " + ToString());
        //             _br = value;
        //         }
        //     }

        public CoroutineClass(scCoroutine mycoroutine, IEnumerator ii)
        {
            ID = id_generator++;
            coroutine = ii;
            myCoroutine = mycoroutine;
        }

        public void Stop()
        {
            if (br)
            {
                br = false;
                RunFinishFunction();
            }
        }

        public bool MoveNext(bool Surpress)
        {
            if (Surpress)
                return MoveNextSurpress();
            else
                return MoveNext();
        }

        bool MoveNext()
        {
            if (!br) return false;
            //실행은 한 틱에 한 번만!
            //Util.Log("br is" + br+"/last_runn:"+last_runned_tick+"/curr:"+current_tick);
            if (last_runned_tick < myCoroutine.CurrentTick)
            {
                last_runned_tick = myCoroutine.CurrentTick;

                //MoveNext할 수 있는지 체크
                if (coroutine.Current == null)
                {
                    bool t_br = coroutine.MoveNext();
                    if (br) br = t_br;
                    if (!br) RunFinishFunction();
                }
                else if (coroutine.Current is CoroutineClass)
                {
                    //쉰다.
                    CoroutineClass waitCoroutine = (CoroutineClass)coroutine.Current;

                    //만약 waitCoroutine이 끝나있는 상황이라면..
                    if (!waitCoroutine.br)
                    {
                        bool t_br = coroutine.MoveNext();
                        if (br) br = t_br;
                        if (!br) RunFinishFunction();
                    }
                }
                return br;
            }
            return br;
        }
        //한 틱에 한번 실행 제한 없이 강제실행한다.
        bool MoveNextSurpress()
        {
            if (!br) return false;
            last_runned_tick = myCoroutine.CurrentTick;
            bool t_br = coroutine.MoveNext();
            if (br) br = t_br;
            if (!br) RunFinishFunction();
            return br;
        }

        public void RunFinishFunction()
        {
            if (OnFinishFunction != null)
            {
                OnFinishFunction();
                OnFinishFunction = null;
            }
        }

        public void SetFinishFunction(DelegateVoidNoParam func)
        {
            OnFinishFunction = func;
            if (!br)
                RunFinishFunction();
        }

        DelegateVoidNoParam OnFinishFunction;

        public delegate void DelegateVoidNoParam();
    }

    public class ObjectYield
    {

    }

    
}
