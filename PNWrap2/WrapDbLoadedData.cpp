#include "stdafx.h"
#include "WrapDbLoadedData.h"

namespace PNWrap2
{
	WrapCLoadedData2Ptr::WrapCLoadedData2Ptr(Proud::CLoadedData2Ptr& in)
	{
		op = new Proud::CLoadedData2Ptr(in);
	}

	WrapCLoadedData2Ptr::~WrapCLoadedData2Ptr()
	{
		delete op;
	}

	PNWrap2::WrapErrorType WrapCLoadedData2Ptr::MovePropNode(WrapCLoadedData2Ptr^ destForest, WrapCPropNodePtr^ nodeToMove, WrapCPropNodePtr^ destParentNode)
	{
		return (WrapErrorType)original->MovePropNode(*destForest->original, nodeToMove->original, destParentNode->original);
	}

	PNWrap2::WrapErrorType WrapCLoadedData2Ptr::InsertChild(WrapCPropNodePtr^ parent, WrapCPropNodePtr^ newNode)
	{
		return (WrapErrorType)original->InsertChild(parent->original, newNode->original);
	}

	PNWrap2::WrapErrorType WrapCLoadedData2Ptr::RemoveNode(WrapCPropNodePtr^ node, bool addremovelist)
	{
		return (WrapErrorType)original->RemoveNode(node->original, addremovelist);
	}

	PNWrap2::WrapErrorType WrapCLoadedData2Ptr::RemoveNode(WrapGUID^ removeUUID, bool addremovelist)
	{
		return (WrapErrorType)original->RemoveNode(removeUUID->original, addremovelist);
	}

	WrapCPropNodePtr^ WrapCLoadedData2Ptr::GetNode(WrapGUID^ guid)
	{
		return gcnew WrapCPropNodePtr(original->GetNode(guid->original));
	}

	WrapCPropNodePtr^ WrapCLoadedData2Ptr::GetRootNode()
	{
		return gcnew WrapCPropNodePtr(original->GetRootNode());
	}

	WrapGUID^ WrapCLoadedData2Ptr::GetRootUUID()
	{
		return gcnew WrapGUID(original->GetRootUUID());
	}

	WrapGUID^ WrapCLoadedData2Ptr::GetSessionGuid()
	{
		return gcnew WrapGUID(original->GetSessionGuid());
	}

	void WrapCLoadedData2Ptr::SetSessionGuid(WrapGUID^ val)
	{
		original->SetSessionGuid(val->original);
	}

	WrapCLoadedData2Ptr^ WrapCLoadedData2Ptr::Clone()
	{
		return gcnew WrapCLoadedData2Ptr(original->Clone());
	}

	Proud::CLoadedData2Ptr& WrapCLoadedData2Ptr::original::get()
	{
		return *op;
	}

}