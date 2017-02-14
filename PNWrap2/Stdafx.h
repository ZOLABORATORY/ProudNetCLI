// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.

#pragma once




// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//#include "windows.h"

namespace PNWrap2
{
	ref struct WrapGUID;
	ref struct WrapCItem;
	ref class WrapCLoadedData2Ptr;
	ref class WrapCPropNodePtr;
	ref class WrapCCallBackArgs;
	typedef System::String SString;
}

#include "EnumErrorType.h"
#include <iostream>
#include <string>
#include <atlbase.h>
#include "../ProudNet/include/ProudDB.h"
#include "resources.h"
#include "DbClient.h"
#include "Manager.h"
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <vcclr.h>
#include "WrapCItem.h"
#include "WrapGUID.h"
#include "WrapCPropNodePtr.h"
#include "WrapDbLoadedData.h"
#include "WrapCCallbackArgs.h"

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
namespace PNWrap2
{

	typedef void __stdcall OnDBLoadFinished(PNWrap2::WrapCCallBackArgs^ a);

	class callbacks
	{
	public:
		//콜백 델리게이터
		static OnDBLoadFinished* When_OnExclusiveLoadDataComplete;
		static OnDBLoadFinished* When_OnDataUnloadRequested;
		static OnDBLoadFinished* When_OnDataForceUnloaded;
		static OnDBLoadFinished* When_OnAddDataFailed;
		static OnDBLoadFinished* When_OnAddDataSuccess;
		static OnDBLoadFinished* When_OnUpdateDataFailed;
		static OnDBLoadFinished* When_OnUpdateDataSuccess;
		static OnDBLoadFinished* When_OnRemoveDataFailed;
		static OnDBLoadFinished* When_OnRemoveDataSuccess;
		static OnDBLoadFinished* When_OnNonExclusiveSnapshotDataComplete;
		static OnDBLoadFinished* When_OnNonExclusiveAddDataAck;
		static OnDBLoadFinished* When_OnNonExclusiveRemoveDataAck;
		static OnDBLoadFinished* When_OnNonExclusiveModifyValueSuccess;
		static OnDBLoadFinished* When_OnNonExclusiveModifyValueFailed;
		static OnDBLoadFinished* When_OnNonExclusiveSetValueIfSuccess;
		static OnDBLoadFinished* When_OnNonExclusiveSetValueIfFailed;
		static OnDBLoadFinished* When_OnSomeoneAddData;
		static OnDBLoadFinished* When_OnSomeoneRemoveData;
		static OnDBLoadFinished* When_OnSomeoneModifyValue;
		static OnDBLoadFinished* When_OnSomeoneSetValue;
		static OnDBLoadFinished* When_OnAccessError;
	};

	//////////////////////////////////////////////////////////////////////////
	//미구현 부분
// 	extern OnDBLoadFinished* When_OnIsolateDataFailed(CCallbackArgs& args) {}
// 	extern OnDBLoadFinished* When_OnIsolateDataSuccess(CCallbackArgs& args) {}
// 	extern OnDBLoadFinished* When_OnDeisolateDataFailed(CCallbackArgs& args) {}
// 	extern OnDBLoadFinished* When_OnDeisolateDataSuccess(CCallbackArgs& args) {}

	//ErrorInfo 가 마샬링된 객체가 없음
	//typedef void __stdcall When_OnJoinDbCacheServerComplete(ErrorInfo *info)

	//이것도 아직DbmsWritePropNodePendType type, Proud::Guid loadedDataGuid 타입을 안 만듦
	//typedef void __stdcall When_OnDbmsWriteDone(DbmsWritePropNodePendType type, Proud::Guid loadedDataGuid);
	
	//얘내도 errorinfo 가 문제
	// 		void EventException(Exception &e) ;
	// 		void EventWarning(ErrorInfo *errorInfo);
	// 		void EventError(ErrorInfo *errorInfo);
	//////////////////////////////////////////////////////////////////////////

	
	//////////////////////////////////////////////////////////////////////////
	//유틸리티
	//System::String 을 Proud::String으로 전환한다
	static Proud::String SStringToProud(SString^ from)
	{
		return (const wchar_t*)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(from).ToPointer();
		//return msclr::interop::marshal_as<std::wstring>(from).c_str();
		//PtrToStringChars()
	}

	//Proud::String 을 System::String으로 전환한다
	static SString^ ProudToSString(const Proud::String& ps)
	{
		return gcnew System::String(ps.GetString());
	}

	static System::DateTime^ ProudToSDate(const Proud::CPnTime& dt)
	{
		return gcnew System::DateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), dt.GetMinute(), dt.GetSecond(), dt.GetMillisecond());
	}

	static Proud::CPnTime SDateToProud(System::DateTime^ dt)
	{	
		return Proud::CPnTime(dt->Year, dt->Month, dt->Day, dt->Hour, dt->Minute, dt->Second, dt->Millisecond);
	}

	//////////////////////////////////////////////////////////////////////////
}

extern "C"
{

	//실제 라이브러리에서 호출할 함수들 : 델리게이터를 등록함
	void __declspec(dllexport) Register_OnExclusiveLoadDataComplete(PNWrap2::OnDBLoadFinished* pcb)
	{ PNWrap2::callbacks::When_OnExclusiveLoadDataComplete = pcb; }
	void __declspec(dllexport) Register_OnDataUnloadRequested(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnDataUnloadRequested = pcb; }
	void __declspec(dllexport) Register_OnDataForceUnloaded(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnDataForceUnloaded = pcb; }
	void __declspec(dllexport) Register_OnAddDataFailed(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnAddDataFailed = pcb; }
	void __declspec(dllexport) Register_OnAddDataSuccess(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnAddDataSuccess = pcb; }
	void __declspec(dllexport) Register_OnUpdateDataFailed(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnUpdateDataFailed = pcb; }
	void __declspec(dllexport) Register_OnUpdateDataSuccess(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnUpdateDataSuccess = pcb; }
	void __declspec(dllexport) Register_OnRemoveDataFailed(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnRemoveDataFailed = pcb; }
	void __declspec(dllexport) Register_OnRemoveDataSuccess(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnRemoveDataSuccess = pcb; }
	void __declspec(dllexport) Register_OnNonExclusiveSnapshotDataComplete(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnNonExclusiveSnapshotDataComplete = pcb; }
	void __declspec(dllexport) Register_OnNonExclusiveAddDataAck(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnNonExclusiveAddDataAck = pcb; }
	void __declspec(dllexport) Register_OnNonExclusiveRemoveDataAck(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnNonExclusiveRemoveDataAck = pcb; }
	void __declspec(dllexport) Register_OnNonExclusiveModifyValueSuccess(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnNonExclusiveModifyValueSuccess = pcb; }
	void __declspec(dllexport) Register_OnNonExclusiveModifyValueFailed(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnNonExclusiveModifyValueFailed = pcb; }
	void __declspec(dllexport) Register_OnNonExclusiveSetValueIfSuccess(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnNonExclusiveSetValueIfSuccess = pcb; }
	void __declspec(dllexport) Register_OnNonExclusiveSetValueIfFailed(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnNonExclusiveSetValueIfFailed = pcb; }
	void __declspec(dllexport) Register_OnSomeoneAddData(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnSomeoneAddData = pcb; }
	void __declspec(dllexport) Register_OnSomeoneRemoveData(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnSomeoneRemoveData = pcb; }
	void __declspec(dllexport) Register_OnSomeoneModifyValue(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnSomeoneModifyValue = pcb; }
	void __declspec(dllexport) Register_OnSomeoneSetValue(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnSomeoneSetValue = pcb; }
	void __declspec(dllexport) Register_OnAccessError(PNWrap2::OnDBLoadFinished* pcb) 
	{ PNWrap2::callbacks::When_OnAccessError = pcb; }

	//라이브러리 임포트 테스트용으로 호출해봤던 함수로 별로 의미는 없음
	void __declspec(dllexport) PrintHello()
	{
		std::cout << "HELLO WORLD!" << std::endl;
		std::wcout << L"HELLO WORLD!" << std::endl;
	}

}

#define RunDelegate(name, paramet)  if (NULL != (name)) (name)(paramet)