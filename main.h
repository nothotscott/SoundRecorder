#pragma once

#include <windows.h>
#include "resource.h"

#define MAX_LOADSTRING 128

#define DEBUGPRINT(...)	(OutputDebugStringW(__VA_ARGS__))

extern const wchar_t usbtools_classname[];
extern TCHAR usbtools_title[MAX_LOADSTRING];