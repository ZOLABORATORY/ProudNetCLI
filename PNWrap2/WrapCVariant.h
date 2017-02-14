#pragma once
#pragma once
#include "stdafx.h"

namespace PNWrap2
{
	typedef System::String SString;
	public ref class WrapCVariant
	{
	public:
		char cval;
		INT64 i64val;
		int ival;
		short sval;
		SString^ strval;
		float fval;
		double dval;
		System::DateTime^ datetimeval;
		WrapGUID^ guidval;
		WrapCVariant_Type current_type;

	public:
		Proud::CVariant& original;
		WrapCVariant(float f);
		WrapCVariant(double f);
		WrapCVariant(char c);
		WrapCVariant(INT64 i);
		WrapCVariant(int i);
		WrapCVariant(short s);
		WrapCVariant(SString^ s);
		WrapCVariant(Proud::String& s);
		WrapCVariant(System::DateTime^ dt);
		WrapCVariant(Proud::CPnTime& dt);
		WrapCVariant(WrapGUID^ guid);
		static WrapCVariant^ CreateFromCVariant(CVariant& from);
		~WrapCVariant();
		virtual System::String^ ToString() override;
		property System::String^ ConvertString
		{
			System::String^ get();
		}
	};
}