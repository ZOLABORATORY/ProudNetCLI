#pragma once
#include "stdafx.h"


namespace PNWrap2
{	
	typedef System::String SString;
	public ref struct WrapCItem
	{
		WrapCItem(Proud::IDbCacheClientDelegate2::CCallbackArgs::CItem& in);
		~WrapCItem();
		Proud::IDbCacheClientDelegate2::CCallbackArgs::CItem& original;
	public:
		property WrapGUID^ m_sessionGuid { WrapGUID^ get() { return inner_sessionGuid(); } }
		property WrapGUID^ m_rootUUID { WrapGUID^ get() { return inner_rootUUID(); } }
		property WrapCLoadedData2Ptr^ m_loadedData { WrapCLoadedData2Ptr^ get() { return inner_loadedData(); } }
		property WrapGUID^ m_UUID { WrapGUID^ get() { return inner_UUID(); } }
		property WrapCPropNodePtr^ m_data { WrapCPropNodePtr^ get() { return inner_data(); } }
		property WrapErrorType m_reason { WrapErrorType get() { return inner_reason(); } }
		property SString^ m_comment { SString^ get() { return inner_comment(); } }
		property int m_hResult { int get() { return inner_hResult(); } }
		property SString^ m_source { SString^ get() { return inner_source(); } }

	private:
		WrapGUID^ inner_sessionGuid();
		WrapGUID^ inner_rootUUID();
		WrapCLoadedData2Ptr^ inner_loadedData();
		WrapGUID^ inner_UUID();
		WrapCPropNodePtr^ inner_data();
		WrapErrorType inner_reason();
		SString^ inner_comment();
		int inner_hResult();
		SString^ inner_source();
	};
	
}