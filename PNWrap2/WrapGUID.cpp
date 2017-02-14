#include "WrapGUID.h"
#include "stdafx.h"


namespace PNWrap2
{
	WrapGUID::WrapGUID(Proud::Guid& in)
	{	
		//guid_value = ProudToSString(in.GetString());
		o_val = new Proud::Guid(in);
	}

	WrapGUID::WrapGUID(WrapGUID^ from)
	{
		//guid_value = from->guid_value;
		o_val = new Proud::Guid(from->original);
	}

	WrapGUID::WrapGUID(SString^ from)
	{
		//guid_value = from;
		o_val = new Proud::Guid(Proud::Guid::GetFromString(SStringToProud(from)));
	}

	Proud::Guid& WrapGUID::origin()
	{
// 		if (o_val == NULL)
// 		{
// 			Proud::Guid pg = Proud::Guid::GetFromString(SStringToProud(guid_value));
// 			o_val = new Proud::Guid(pg);
// 		}
		return *o_val;
	}

	WrapGUID::~WrapGUID()
	{
		if (o_val != NULL) delete o_val;
		o_val = NULL;
	}

	PNWrap2::WrapGUID^ WrapGUID::Random()
	{
		return gcnew WrapGUID(Proud::Guid::RandomGuid());
	}

	System::String^ WrapGUID::ToString()
	{
		//if (o_val != NULL)
			return ProudToSString(o_val->ToString());
		//return guid_value;
	}

	System::String^ WrapGUID::ToBracketString()
	{
		//if (o_val != NULL) 
			return ProudToSString(o_val->ToBracketString());
		//return SString::Format("{{{0}}}", guid_value);
	}

	WrapGUID^ WrapGUID::GetFromString(System::String^ uuidstr)
	{
		return gcnew WrapGUID(uuidstr);
	}

}