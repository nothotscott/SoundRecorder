#pragma once

#ifdef _DEBUG
#define	AGGRESSIVE	1
#endif
#ifdef REACTOS
#define	AGGRESSIVE	0
#endif

#ifdef AGGRESSIVE
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <windows.h>
#include <stdio.h>
#include "resource.h"

#define MAX_LOADSTRING 128
#define IDC_COMBOBOX	1001

#define DEBUGPRINT(...)	(OutputDebugString(__VA_ARGS__))
#define DEBUGINT(n)		{ wchar_t _buf[20] = { 0 }; swprintf(_buf, _countof(_buf), L"%d\r\n", n); DEBUGPRINT(_buf); }

extern const wchar_t g_szClassName[];
extern TCHAR g_szTitle[MAX_LOADSTRING];