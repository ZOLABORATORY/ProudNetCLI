// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// PNWrap2.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

namespace PNWrap2
{
	OnDBLoadFinished* callbacks::When_OnExclusiveLoadDataComplete = NULL;
	OnDBLoadFinished* callbacks::When_OnDataUnloadRequested = NULL;
	OnDBLoadFinished* callbacks::When_OnDataForceUnloaded = NULL;
	OnDBLoadFinished* callbacks::When_OnAddDataFailed = NULL;
	OnDBLoadFinished* callbacks::When_OnAddDataSuccess = NULL;
	OnDBLoadFinished* callbacks::When_OnUpdateDataFailed = NULL;
	OnDBLoadFinished* callbacks::When_OnUpdateDataSuccess = NULL;
	OnDBLoadFinished* callbacks::When_OnRemoveDataFailed = NULL;
	OnDBLoadFinished* callbacks::When_OnRemoveDataSuccess = NULL;
	OnDBLoadFinished* callbacks::When_OnNonExclusiveSnapshotDataComplete = NULL;
	OnDBLoadFinished* callbacks::When_OnNonExclusiveAddDataAck = NULL;
	OnDBLoadFinished* callbacks::When_OnNonExclusiveRemoveDataAck = NULL;
	OnDBLoadFinished* callbacks::When_OnNonExclusiveModifyValueSuccess = NULL;
	OnDBLoadFinished* callbacks::When_OnNonExclusiveModifyValueFailed = NULL;
	OnDBLoadFinished* callbacks::When_OnNonExclusiveSetValueIfSuccess = NULL;
	OnDBLoadFinished* callbacks::When_OnNonExclusiveSetValueIfFailed = NULL;
	OnDBLoadFinished* callbacks::When_OnSomeoneAddData = NULL;
	OnDBLoadFinished* callbacks::When_OnSomeoneRemoveData = NULL;
	OnDBLoadFinished* callbacks::When_OnSomeoneModifyValue = NULL;
	OnDBLoadFinished* callbacks::When_OnSomeoneSetValue = NULL;
	OnDBLoadFinished* callbacks::When_OnAccessError = NULL;
}
