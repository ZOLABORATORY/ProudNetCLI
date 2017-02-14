﻿
// stdafx.h : It includes a file that contain standard include file and project realated file which does not change often.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // It excludes information that do not often use at Windows header.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // Some CString creator declare with state clearly.

// Cancel hiding about MFC common part and ignorable warning message.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard compose factor
#include <afxext.h>         // MFC extention


#include <afxdisp.h>        // MFC automate class



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support about Internet Explorer 4 public control
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support about Windows public control
#endif // _AFX_NO_AFXCMN_SUPPORT

//#include <afxcontrolbars.h>     // Support ribbon and control of MFC









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



//기존의 Sample에서 Common을 쓰는 부분
//#include "..\SimpleDB2Common\Vars.h"

//이 부분을 변경함
#include "../ProudNet/include/ProudDB.h"
using namespace Proud;
#define MESSAGE_LOG WM_USER+10 
extern String g_DbAuthKey;
extern int g_DbServerPort;

//추가된 부분
#include <fstream>
#include <iostream>