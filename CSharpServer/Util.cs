using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meta
{
    public class AutoValue : IComparable
    {
        public override string ToString()
        {
            return strvalue;
        }

        public float floatvalue;
        public int intvalue;
        public string strvalue;

        public int basic_int_value = -1;
        public string basic_string_value = string.Empty;
        public float basic_float_value = -1;

        public int i
        {
            get
            {
                return intvalue;
            }
            set
            {
                _intable = true;
                _floatable = true;
                intvalue = value;
                strvalue = value.ToString();
                floatvalue = value;
            }
        }

        public float f
        {
            get
            {
                return floatvalue;
            }
            set
            {
                _intable = true;
                _floatable = true;
                intvalue = (int)value;
                strvalue = value.ToString();
                floatvalue = value;
            }
        }

        public bool IntAble
        {
            get
            {
                return _intable;
            }
        }
        private bool _intable = false;

        public bool Floatable
        {
            get
            {
                return _floatable;
            }
        }
        private bool _floatable = false;

        public string s
        {
            get
            {
                return strvalue;
            }
            set
            {
                strvalue = value;
                if (!int.TryParse(value, out intvalue))
                {
                    _intable = false;
                    intvalue = basic_int_value;
                }
                else { _intable = true; }
                if (!float.TryParse(value, out floatvalue))
                {
                    _floatable = false;
                    floatvalue = basic_float_value;
                }
                else _floatable = true;
            }
        }

        public AutoValue(object o, string defaultvalue = "")
        {
            if (o == null) s = "null";
            else s = o.ToString();
        }

        public AutoValue(int iv)
        {
            i = iv;
        }

        public AutoValue(float fv)
        {
            f = fv;
        }

        public int CompareTo(object obj)
        {
            return s.CompareTo(obj);
        }

        public int CompareTo<T>(T other)
        {
            return s.CompareTo(other.ToString());
        }

        public AutoValue Clone()
        {
            if (IntAble) return new AutoValue(i);
            return new AutoValue(s);
        }
    }
}

namespace CSharpServer
{
    public class Boxer<T>
    {
        public static implicit operator T(Boxer<T> b)
        {
            return b.value;
        }

        public override string ToString()
        {
            return value.ToString();
        }
        public T value;
        public Boxer(T t)
        {
            Set(t);
        }
        public void Set(T t)
        {
            value = t;
        }
        public Boxer<T> Clone()
        {
            return new Boxer<T>(value);
        }
    }

    public class intbox : Boxer<int>
    {
        public intbox(int i) : base(i)
        {

        }

        public intbox()
            : base(0)
        {

        }
    }

    public class box : Boxer<object>
    {
        public box(object o) : base(o)
        {

        }

        public box()
            : base(null)
        {

        }
    }


    public class Util
    {
        public delegate void DelegateVoidNoParam();
        
        
        public static void Log(object o)
        {
            //일단콘솔에 ㅡ,.ㅡ
            System.Console.WriteLine(o);
        }

        private static System.Timers.Timer _updateTimer = null;

        public static System.Timers.Timer UpdateTimer
        {
            get
            {
                if (_updateTimer == null)
                {
                    _updateTimer = new System.Timers.Timer();
                    _updateTimer.Interval = 5000;
                    _updateTimer.Start();                    
                }
                return _updateTimer;
            }
        }


    }
}
