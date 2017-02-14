#pragma once
#include "stdafx.h"
#include "EnumErrorType.h"
#include "WrapGUID.h"
#include "WrapCPropNodePtr.h"

namespace PNWrap2
{
	public ref class WrapCLoadedData2Ptr
	{	
	public:
		WrapCLoadedData2Ptr(Proud::CLoadedData2Ptr& in);
		~WrapCLoadedData2Ptr();

		WrapErrorType MovePropNode(WrapCLoadedData2Ptr^ destForest, WrapCPropNodePtr^ nodeToMove, WrapCPropNodePtr^ destParentNode);

		WrapErrorType InsertChild(WrapCPropNodePtr^ parent, WrapCPropNodePtr^ newNode);

		WrapErrorType RemoveNode(WrapCPropNodePtr^ node, bool addremovelist);

		WrapErrorType RemoveNode(WrapGUID^ removeUUID, bool addremovelist);

		WrapCPropNodePtr^ GetNode(WrapGUID^ guid);

		WrapCPropNodePtr^ GetRootNode();

		WrapGUID^ GetRootUUID();

		WrapGUID^ GetSessionGuid();

		void SetSessionGuid(WrapGUID^ val);

		WrapCLoadedData2Ptr^ Clone();
		
		property Proud::CLoadedData2Ptr& original
		{
			Proud::CLoadedData2Ptr& get();
		}

	private:
		Proud::CLoadedData2Ptr* op;
	};


}