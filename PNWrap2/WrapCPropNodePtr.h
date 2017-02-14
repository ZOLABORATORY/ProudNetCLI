#pragma once
#include "WrapCVariant.h"
#include "stdafx.h"

namespace PNWrap2
{
	typedef System::String SString;
	public ref class WrapCPropNodePtr
	{
		//포인터로는 바로 생성 못하게
		WrapCPropNodePtr(Proud::CPropNode* in);
	public:
		WrapCPropNodePtr(Proud::CPropNodePtr& in);		
		WrapCPropNodePtr(SString^ tablename);
		~WrapCPropNodePtr();

		static WrapCPropNodePtr^ CreateByPointer(Proud::CPropNode* in);

		SString^ GetTypeName();

		void SetStringTypeName(SString^ str);

		WrapCVariant^ GetFieldWrapCVariant(SString^ name);

		SString^ GetFieldString(SString^ name);

		int GetFieldInt(SString^ name);

		float GetFieldFloat(SString^ name);

		void SetField(SString^ name, SString^ value);

		void SetField(SString^ name, const int value);

		void SetField(SString^ name, const float f);

		void SetField(SString^ name, const System::DateTime time);
		
		void SetField(SString^ name, WrapGUID^ guid);

		void RemoveField(SString^ name);

		bool Add(SString^ key, SString^ val);

		bool Add(SString^ key, const int val);

		bool Add(SString^ key, const float val);		

		property Proud::CPropNodePtr& original
		{
			Proud::CPropNodePtr& get()
			{
				return *op;
			}
		}

		property System::Collections::Generic::List<SString^>^ ColumnList
		{
			System::Collections::Generic::List<SString^>^ get()
			{
				return makeColumnList();
			}
		}

		property System::Collections::Generic::Dictionary<SString^, WrapCVariant^>^ TotalFieldDictionary
		{
			System::Collections::Generic::Dictionary<SString^, WrapCVariant^>^ get()
			{
				return makeFieldDiectionary();
			}
		}

		WrapCPropNodePtr^ GetChild();

		WrapCPropNodePtr^ GetSibling();

		WrapCPropNodePtr^ GetEndSibling();

		WrapGUID^ GetUUID();

		WrapGUID^ GetOwnerUUID();

		WrapGUID^ GetRootUUID();

		property System::Collections::Generic::Dictionary<SString^, System::Collections::Generic::List<WrapCPropNodePtr^>^>^  GetChildDictionary
		{
			System::Collections::Generic::Dictionary<SString^, System::Collections::Generic::List<WrapCPropNodePtr^>^>^  get()
			{
				return makeChildDictionary();
			}
		}

		System::Collections::Generic::List<WrapCPropNodePtr^>^ FindChildren(SString^ type_name);

		virtual SString^ ToString() override;

		
		
	private:
		System::Collections::Generic::List<SString^>^ makeColumnList();
		System::Collections::Generic::Dictionary<SString^, WrapCVariant^>^ makeFieldDiectionary();
		System::Collections::Generic::Dictionary<SString^, System::Collections::Generic::List<WrapCPropNodePtr^>^>^  makeChildDictionary();
		Proud::CPropNodePtr* op;
	};

	
}