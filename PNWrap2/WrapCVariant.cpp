
#include "stdafx.h"
#include "WrapCVariant.h"

namespace PNWrap2
{

	WrapCVariant::WrapCVariant(float f) : original(*(new Proud::CVariant(f)))
	{
		fval = f;
		current_type = t_float;
	}

	WrapCVariant::WrapCVariant(char c) : original(*(new Proud::CVariant(c)))
	{
		cval = c;
		current_type = t_char;
	}

	WrapCVariant::WrapCVariant(INT64 i) : original(*(new Proud::CVariant(i)))
	{
		i64val = i;
		current_type = t_int;
	}

	WrapCVariant::WrapCVariant(int i) : original(*(new Proud::CVariant(i)))
	{
		ival = i;
		current_type = t_int;
	}

	WrapCVariant::WrapCVariant(short s) : original(*(new Proud::CVariant(s)))
	{
		sval = s;
		current_type = t_short;
	}

	WrapCVariant::WrapCVariant(SString^ s) : original(*(new Proud::CVariant(SStringToProud(s))))
	{
		strval = s;
		current_type = t_string;
	}

	WrapCVariant::WrapCVariant(Proud::String& s) : original(*(new Proud::CVariant(s)))
	{
		strval = ProudToSString(s);
		current_type = t_string;
	}

	WrapCVariant::WrapCVariant(System::DateTime^ dt) : original(*(new Proud::CVariant(SDateToProud (dt))))
	{
		datetimeval = dt;
		current_type = t_datetime;
	}

	WrapCVariant::WrapCVariant(Proud::CPnTime& dt) : original(*(new Proud::CVariant(dt)))
	{
		datetimeval = ProudToSDate(dt);
		current_type = t_datetime;
	}

	WrapCVariant::WrapCVariant(WrapGUID^ guid) : original(*(new Proud::CVariant(guid->original)))
	{
		guidval = guid;
		current_type = t_guid;
	}
		
	WrapCVariant::WrapCVariant(double f) : original(*(new Proud::CVariant(f)))
	{
		dval = f;
		current_type = t_double;
	}

	WrapCVariant^ WrapCVariant::CreateFromCVariant(CVariant& cv)
	{
		WrapCVariant^ rtv = nullptr;
		switch ((VARENUM)cv.m_val.GetVARIANT().vt)
		{
		case VT_EMPTY:
		case VT_NULL:
			break;
		case VT_I2:
			rtv = gcnew WrapCVariant((short)cv);
			break;
		case VT_I4:
			rtv = gcnew WrapCVariant((int)cv);
			break;
		case VT_I8:
			rtv = gcnew WrapCVariant((INT64)cv);
			break;
		case VT_INT:
			rtv = gcnew WrapCVariant((int)cv);
			break;
		case VT_R4:
			rtv = gcnew WrapCVariant((float)cv);
			break;
		case VT_R8:
			rtv = gcnew WrapCVariant((double)cv);
			break;
		case VT_DATE:
			rtv = gcnew WrapCVariant((Proud::CPnTime)cv);
			break;
		case VT_BSTR:
			rtv = gcnew WrapCVariant((Proud::String)cv);
			break;
		}
		//³ª¸ÓÁø null
		return rtv;
	}

	WrapCVariant::~WrapCVariant()
	{
		delete &original;
	}

	System::String^ WrapCVariant::ToString()
	{
		switch (current_type)
		{
		case PNWrap2::t_char:
			return cval.ToString();
		case PNWrap2::t_i64:
			return i64val.ToString();
		case PNWrap2::t_int:
			return ival.ToString();
		case PNWrap2::t_short:
			return sval.ToString();
		case PNWrap2::t_string:
			return strval->ToString();
		case PNWrap2::t_float:
			return fval.ToString();
		case PNWrap2::t_double:
			return dval.ToString();
		case PNWrap2::t_datetime:
			return datetimeval->ToString();
		case PNWrap2::t_guid:
			return guidval->ToString();
		default:
			break;
		}
		return L"[EMPTY]";
	}

	System::String^ WrapCVariant::ConvertString::get()
	{
		return ToString();
	}

}