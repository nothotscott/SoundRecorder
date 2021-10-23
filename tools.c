/*
 * USB Tools
 * Copyright (C) 2021 Scott Maday
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tools.h"


size_t g_numDevices = 0;
PUSBTOOLS_DEVICE g_aDevices[MAX_DEVICES];

void UsbToolsLoadDevices(HWND hWnd, LRESULT(CALLBACK* fnCallback)(HWND, PUSBTOOLS_DEVICE))
{
	GUID* pUsbDeviceGuid = (GUID*)&GUID_DEVCLASS_USB;
	HDEVINFO hDeviceInfoSet = SetupDiGetClassDevs(pUsbDeviceGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_PROFILE);
	DWORD i = 0;
	while (TRUE)
	{
		SP_DEVINFO_DATA deviceInfoData = {
			.cbSize = sizeof(SP_DEVINFO_DATA)
		};
		USBTOOLS_DEVICE* device = malloc(sizeof(USBTOOLS_DEVICE));
		if (device == NULL) {
			DEBUGPRINT(L"Not enough memory");
			break;
		}
		g_aDevices[i] = device;
		if (SetupDiEnumDeviceInfo(hDeviceInfoSet, i, &deviceInfoData) == FALSE)
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			else
			{
				DEBUGPRINT(L"Device enumeration failed with code: ");
				DEBUGINT(i);
				i++;
				continue;
			}
		}
		DWORD nSize = 0;
		SetupDiGetDeviceInstanceId(hDeviceInfoSet, &deviceInfoData, &device->szInstanceId, sizeof(device->szInstanceId), &nSize);
		i++;
	}
	g_numDevices = i;
	if (hDeviceInfoSet)
	{
		SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
	}
	for (i = 0; i < g_numDevices; i++)
	{
		fnCallback(hWnd, g_aDevices[i]);
	}
}

void UsbToolsFreeDevices()
{
	for (size_t i = 0; i < g_numDevices; i++)
	{
		free(g_aDevices[i]);
	}
}