#include "WrapCVariant.h"
#include "WrapCPropNodePtr.h"
#include "stdafx.h"

namespace PNWrap2
{
	WrapCPropNodePtr::WrapCPropNodePtr(Proud::CPropNodePtr& in)
	{
		op = new Proud::CPropNodePtr(in);
	}

	WrapCPropNodePtr::WrapCPropNodePtr(SString^ type_name)
	{
		op = new Proud::CPropNodePtr(new Proud::CPropNode(SStringToProud(type_name)));
	}
	
	WrapCPropNodePtr^ WrapCPropNodePtr::CreateByPointer(Proud::CPropNode* in)
	{
		if (in == NULL)
			return nullptr;
		else
			return gcnew WrapCPropNodePtr(in);
	}

	//이걸 직접 사용하면 NULL 이 들어왔을 때 nullptr을 리턴할 수 없기 때문에, 위의 CreateByPointer를 사용한다.
	WrapCPropNodePtr::WrapCPropNodePtr(Proud::CPropNode* in)
	{
		op = new Proud::CPropNodePtr(in);
	}

	WrapCPropNodePtr::~WrapCPropNodePtr()
	{
		delete op;
	}
	
	System::String^ WrapCPropNodePtr::GetTypeName()
	{
		return gcnew SString(original->GetTypeName());
	}

	void WrapCPropNodePtr::SetStringTypeName(SString^ str)
	{
		original->SetStringTypeName(SStringToProud(str));
	}

	PNWrap2::WrapCVariant^ WrapCPropNodePtr::GetFieldWrapCVariant(SString^ name)
	{
		const Proud::String ps = SStringToProud(name);
		CVariant& cv = original->GetField(ps);
		return WrapCVariant::CreateFromCVariant(cv);
	}

	System::String^ WrapCPropNodePtr::GetFieldString(SString^ name)
	{
		const Proud::String ps = SStringToProud(name);
		CVariant& cv = original->GetField(ps);
		return ProudToSString(Proud::String(cv));
	}

	int WrapCPropNodePtr::GetFieldInt(SString^ name)
	{
		CVariant& cv = original->GetField(SStringToProud(name));
		return cv.m_val.intVal;
	}

	float WrapCPropNodePtr::GetFieldFloat(SString^ name)
	{
		CVariant& cv = original->GetField(SStringToProud(name));
		return cv.m_val.fltVal;
	}

	void WrapCPropNodePtr::SetField(SString^ name, SString^ value)
	{
		original->SetField(SStringToProud(name), CVariant(SStringToProud(value)));
	}

	void WrapCPropNodePtr::SetField(SString^ name, const int value)
	{
		original->SetField(SStringToProud(name), CVariant(value));
	}

	void WrapCPropNodePtr::SetField(SString^ name, const float f)
	{
		original->SetField(SStringToProud(name), CVariant(f));
	}

	void WrapCPropNodePtr::SetField(SString^ name, const System::DateTime time)
	{	
		original->SetField(SStringToProud(name), CVariant(SDateToProud(time)));
	}

	void WrapCPropNodePtr::SetField(SString^ name, WrapGUID^ guid)
	{
		original->SetField(SStringToProud(name), CVariant(SStringToProud(guid->ToBracketString())));
	}

	void WrapCPropNodePtr::RemoveField(SString^ name)
	{
		original->RemoveField(SStringToProud(name));
	}

	bool WrapCPropNodePtr::Add(SString^ key, SString^ val)
	{
		return original->Add(SStringToProud(key), CVariant(SStringToProud(val)));
	}

	bool WrapCPropNodePtr::Add(SString^ key, const int val)
	{
		return original->Add(SStringToProud(key), CVariant(val));
	}

	bool WrapCPropNodePtr::Add(SString^ key, const float val)
	{
		return original->Add(SStringToProud(key), CVariant(val));
	}

	WrapCPropNodePtr^ WrapCPropNodePtr::GetChild()
	{
		CPropNode* p = original->GetChild();
		if (p == NULL)
			return nullptr;
		else
			return gcnew WrapCPropNodePtr(p);
	}

	WrapCPropNodePtr^ WrapCPropNodePtr::GetSibling()
	{
		CPropNode* p = NULL;
		p = original->GetSibling();
		if (p == NULL)
			return nullptr;
		else
		{
			return gcnew WrapCPropNodePtr(p);
		}
	}

	WrapCPropNodePtr^ WrapCPropNodePtr::GetEndSibling()
	{
		CPropNode* p = original->GetEndSibling();
		if (p == NULL)
			return nullptr;
		else
			return gcnew WrapCPropNodePtr(p);
	}

	WrapGUID^ WrapCPropNodePtr::GetUUID()
	{
		return gcnew WrapGUID(original->GetUUID());
	}

	WrapGUID^ WrapCPropNodePtr::GetOwnerUUID()
	{
		return gcnew WrapGUID(original->GetOwnerUUID());
	}

	WrapGUID^ WrapCPropNodePtr::GetRootUUID()
	{
		return gcnew WrapGUID(original->GetRootUUID());
	}

	System::Collections::Generic::List<WrapCPropNodePtr^>^ WrapCPropNodePtr::FindChildren(SString^ type_name)
	{
		System::Collections::Generic::List<WrapCPropNodePtr^>^ rtv = gcnew System::Collections::Generic::List<WrapCPropNodePtr^>();
		CPropNode* c1 = original->GetChild();
		Proud::String tname = SStringToProud(type_name);
		if (c1 != NULL)
		{
			CPropNode* ed = c1->GetEndSibling();
			while (c1 != ed)
			{
				if (0 == tname.CompareNoCase(Proud::String(c1->GetTypeName()))) rtv->Add(CreateByPointer(c1));
				c1 = c1->GetSibling();
			}
		}
		return rtv;
	}

	PNWrap2::SString^ WrapCPropNodePtr::ToString()
	{
		Proud::String ps;
		System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
		sb->Append("(");
		SString^ ss = GetTypeName();
		sb->Append(ss);
		sb->Append(") UUID(");
		sb->Append(GetUUID()->ToString());
		sb->Append(")");
		return sb->ToString();
	}

	System::Collections::Generic::List<SString^>^ WrapCPropNodePtr::makeColumnList()
	{
		System::Collections::Generic::List<SString^>^ rtv = gcnew System::Collections::Generic::List<SString^>();

		Proud::CFastArray<Proud::String> keys;
		original->CopyKeysTo(keys);

		for (int i = 0; i < keys.Count; ++i)
		{
			rtv->Add(ProudToSString(keys[i]));
		}

		return rtv;
	}

	System::Collections::Generic::Dictionary<SString^, WrapCVariant^>^ WrapCPropNodePtr::makeFieldDiectionary()
	{
		System::Collections::Generic::Dictionary<SString^, WrapCVariant^>^ rtv = gcnew System::Collections::Generic::Dictionary<SString^, WrapCVariant^>();

		Proud::CFastArray<Proud::String> keys;
		original->CopyKeysTo(keys);
		for (int i = 0; i < keys.Count; ++i)
		{
			CVariant& cv = original->GetField(keys[i]);
			if (!cv.IsNull())
			{
				//3 = int / bool / short = I4
				//4 = float	= R4
				//7 = date = DATE
				//8 = GUID / wchar_t* = BSTR
				//19 = unsigned long = UI4

				SString^ kstr = ProudToSString(keys[i]);
				rtv->Add(kstr, WrapCVariant::CreateFromCVariant(cv));
			}
		}

		return rtv;
	}

	System::Collections::Generic::Dictionary<SString^, System::Collections::Generic::List<WrapCPropNodePtr^>^>^ WrapCPropNodePtr::makeChildDictionary()
	{
		System::Collections::Generic::Dictionary<SString^, System::Collections::Generic::List<WrapCPropNodePtr^>^>^  rtv = gcnew System::Collections::Generic::Dictionary<SString^, System::Collections::Generic::List<WrapCPropNodePtr^>^>();

		CPropNode* c1 = original->GetChild();
		if (c1 != NULL)
		{
			CPropNode* ed = c1->GetEndSibling();
			while (c1 != ed)
			{
				SString^ ss = ProudToSString(c1->GetTypeName());
				System::Collections::Generic::List<WrapCPropNodePtr^>^ ls = nullptr;
				if (!rtv->TryGetValue(ss, ls))
				{
					ls = gcnew System::Collections::Generic::List<WrapCPropNodePtr^>();
					ls->Add(CreateByPointer(c1));
					rtv->Add(ss, ls);
				}
				else
				{
					ls->Add(CreateByPointer(c1));
				}
				//next
				c1 = c1->GetSibling();
			}
		}
		return rtv;
	}

}
