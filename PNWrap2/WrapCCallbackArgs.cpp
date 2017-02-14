#include "WrapCCallbackArgs.h"
#include "WrapCItem.h"
#include "stdafx.h"




PNWrap2::WrapCCallBackArgs::WrapCCallBackArgs(Proud::IDbCacheClientDelegate2::CCallbackArgs& in) : original(in)
{	
	if (in.m_tag != 0)
	{
		System::IntPtr ip(in.m_tag);
		comment = System::Runtime::InteropServices::Marshal::GetObjectForIUnknown(ip);
		System::Runtime::InteropServices::Marshal::Release(ip);
	}
}

PNWrap2::WrapCCallBackArgs::~WrapCCallBackArgs()
{

}

PNWrap2::WrapCCallBackArgs::Items^ PNWrap2::WrapCCallBackArgs::inner_m_items()
{
	Items^ itms = gcnew Items();
	for (int i = 0; i < original.m_items.Count; ++i)
	{
		Proud::IDbCacheClientDelegate2::CCallbackArgs::CItem& myitm = original.m_items[i];
		if (myitm.m_reason == ErrorType_Ok)
		{
			WrapCItem^ citm = gcnew WrapCItem(original.m_items[i]);
			itms->Add(citm);
		}
	}
	return itms;
}

int PNWrap2::WrapCCallBackArgs::inner_m_tag()
{
	return original.m_tag;
}

int PNWrap2::WrapCCallBackArgs::m_tag::get()
{
	return inner_m_tag();
}

PNWrap2::WrapCCallBackArgs::Items^ PNWrap2::WrapCCallBackArgs::m_items::get()
{
	Items^ itms = inner_m_items();
	return itms;
}
