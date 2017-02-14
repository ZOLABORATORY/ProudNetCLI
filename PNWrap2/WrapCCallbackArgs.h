#pragma once
#include "stdafx.h"

namespace PNWrap2
{
	public ref class WrapCCallBackArgs
	{
	public:
		typedef System::Collections::Generic::List<WrapCItem^> Items;
	private:
		Items^ inner_m_items();
		int inner_m_tag();
	public:
		WrapCCallBackArgs(Proud::IDbCacheClientDelegate2::CCallbackArgs& in);
		~WrapCCallBackArgs();

		Proud::IDbCacheClientDelegate2::CCallbackArgs& original;
		System::Object^ comment;		

		property Items^ m_items
		{
			Items^ get();
		}

		property int m_tag
		{
			int get();
		}
		
	};

}

