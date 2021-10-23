#pragma once

#include <stdio.h>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include "main.h"

#define MAX_DEVICES				256
#define DEVICE_STRING_LENGTH	4096

typedef struct _USBTOOLS_DEVICE {
	wchar_t szInstanceId[DEVICE_STRING_LENGTH];
} USBTOOLS_DEVICE, *PUSBTOOLS_DEVICE;


extern size_t g_numDevices;
extern PUSBTOOLS_DEVICE g_aDevices[MAX_DEVICES];


void UsbToolsLoadDevices(HWND hWnd, LRESULT (CALLBACK *fnCallback)(HWND, PUSBTOOLS_DEVICE));
void UsbToolsFreeDevices();