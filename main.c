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
#include "main.h"

const TCHAR g_szClassName[] = L"USBTools";
TCHAR g_szTitle[MAX_LOADSTRING];

void fnLayoutWindow(HWND);

static HWND hWndComboBox;


int CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hwnd, IDOK);
					break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hwnd, TRUE);
			break;
		default:
			return FALSE;
	}
	return TRUE;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
			fnLayoutWindow(hWnd);
			break;
		case WM_COMMAND:
			DEBUGINT(LOWORD(wParam));
			switch (LOWORD(wParam))
			{
				case ID_FILE_EXIT:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					break;
				case ID_ABOUT:
					if (!DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT_DIALOG), hWnd, AboutDlgProc)) {
						DEBUGPRINT(L"About dialog box failed\r\n");
					}
					break;
			}
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void fnLoadResources(HINSTANCE hInstance) {
	LoadString(hInstance, IDS_APP_TITLE, g_szTitle, MAX_LOADSTRING);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nShowCmd)
{
	// Load and register class
	WNDCLASSEX wce = { 0 };
	wce.lpszClassName = g_szClassName;
	wce.cbSize = sizeof(WNDCLASSEX);
	wce.style = 0;
	wce.lpfnWndProc = WindowProc;
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hInstance = hInstance;
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wce.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINICON));
	wce.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SMALLICON));
	if (!RegisterClassEx(&wce))
	{
		DEBUGPRINT(L"Window class registration failed\r\n");
		return 0;
	}
	// Load resources
	fnLoadResources(hInstance);

	// Create and display window
	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, g_szClassName, g_szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 320, 240, NULL, NULL, hInstance, NULL);
	if (hWnd == NULL)
	{
		DEBUGPRINT(L"Window creation failed\r\n");
		return 0;
	}
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	// Event loop
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void fnLayoutWindow(HWND hWnd) {
	hWndComboBox = CreateWindowEx(WS_EX_WINDOWEDGE, L"ComboBox", L"ComboBox1",  CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, 7, 7, 200, 200, hWnd, NULL, GetModuleHandle(NULL), NULL);
	if (hWndComboBox == NULL)
	{
		DEBUGPRINT(L"Could not create ComboBox\r\n");
		return;
	}
	SendMessage(hWndComboBox, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(0, 0));
}