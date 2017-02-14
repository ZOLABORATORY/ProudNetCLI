#pragma once
#include "stdafx.h"


namespace PNWrap2
{
	public ref struct WrapGUID
	{
	private:
		SString^ guid_value;
		WrapGUID(SString^ from);
		Proud::Guid* o_val;
		Proud::Guid& origin();
	public:
		WrapGUID(Proud::Guid& in);
		WrapGUID(WrapGUID^ from);
		~WrapGUID();
 		static WrapGUID^ Random();
		static WrapGUID^ GetFromString(System::String^ uuidstr);
 		virtual System::String^ ToString() override;
		System::String^ ToBracketString();

		property Proud::Guid& original
		{
			Proud::Guid& get()
			{
				return origin();
			}
		}
	
	};
}