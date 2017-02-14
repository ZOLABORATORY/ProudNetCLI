#include "WrapGUID.h"
#include "WrapDbLoadedData.h"
#include "WrapCItem.h"
#include "stdafx.h"

namespace PNWrap2
{

	PNWrap2::WrapCItem::WrapCItem(Proud::IDbCacheClientDelegate2::CCallbackArgs::CItem& in) : original(in)
	{

	}

	WrapCItem::~WrapCItem()
	{
	}

	WrapGUID^ PNWrap2::WrapCItem::inner_sessionGuid()
	{
		return gcnew WrapGUID(original.m_sessionGuid);
	}

	WrapGUID^ PNWrap2::WrapCItem::inner_rootUUID()
	{
		return gcnew WrapGUID(original.m_rootUUID);
	}

	WrapCLoadedData2Ptr^ PNWrap2::WrapCItem::inner_loadedData()
	{
		return gcnew WrapCLoadedData2Ptr(original.m_loadedData);
	}

	WrapGUID^ PNWrap2::WrapCItem::inner_UUID()
	{
		return gcnew WrapGUID(original.m_UUID);
	}

	WrapCPropNodePtr^ PNWrap2::WrapCItem::inner_data()
	{
		return gcnew WrapCPropNodePtr(original.m_data);
	}

	PNWrap2::WrapErrorType PNWrap2::WrapCItem::inner_reason()
	{
		return (WrapErrorType)original.m_reason;
	}

	SString^ PNWrap2::WrapCItem::inner_comment()
	{
		return ProudToSString(original.m_comment);
	}

	int PNWrap2::WrapCItem::inner_hResult()
	{
		return original.m_hResult;
	}

	SString^ PNWrap2::WrapCItem::inner_source()
	{
		return ProudToSString(original.m_source);
	}

}