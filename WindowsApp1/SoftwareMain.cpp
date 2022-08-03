#include <Windows.h>
#include "SoftwareDefinitions.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_WINLOGO), L"MainWndClass", SoftwareMainProcedure);

	long desktopHorizontal, desktopVertical;
	GetDesktopResolution(desktopHorizontal, desktopVertical);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"First window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, desktopHorizontal / 4, desktopVertical / 4, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

void GetDesktopResolution(long& horizontal, long& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };

	NWC.hCursor = Cursor;
	NWC.hIcon = Icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnMenuAction1:
			MessageBoxA(hWnd, "Действие 1 текст!", "Действие 1", MB_OK); break;
		case OnMenuAction2:
			MessageBoxA(hWnd, "Действие 2 текст!", "Действие 2", MB_OK); break;
		case OnMenuAction3:
			MessageBoxA(hWnd, "Действие 3 текст!", "Действие 3", MB_OK); break;
		case OnExitSoftware:
			PostQuitMessage(0); break;
		default:
			break;
		}
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU SubFileMenu = CreateMenu();
	HMENU SubFileActionMenu = CreateMenu();
	HMENU SubHelpMenu = CreateMenu();

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubFileMenu, L"Файл");
	{
		AppendMenu(SubFileMenu, MF_POPUP, (UINT_PTR)SubFileActionMenu, L"Действия");
		{
			AppendMenu(SubFileActionMenu, MF_STRING, OnMenuAction1, L"Действие 1");
			AppendMenu(SubFileActionMenu, MF_STRING, OnMenuAction2, L"Действие 2");
			AppendMenu(SubFileActionMenu, MF_STRING, OnMenuAction3, L"Действие 3");
		}
		AppendMenu(SubFileMenu, MF_SEPARATOR, NULL, NULL);
		AppendMenu(SubFileMenu, MF_STRING, OnExitSoftware, L"Выход");
	}
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubHelpMenu, L"Справка");

	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 10, 10, 140, 60, hWnd, NULL, NULL, NULL);

	CreateWindowA("static", "Status: Error", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | WS_BORDER, 160, 10, 830, 60, hWnd, NULL, NULL, NULL);

	CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 80, 980, 340, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Save", WS_VISIBLE | WS_CHILD | ES_CENTER, 10, 430, 140, 60, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Load", WS_VISIBLE | WS_CHILD | ES_CENTER, 160, 430, 140, 60, hWnd, NULL, NULL, NULL);

	CreateWindowA("static", "Copyright © 2022", WS_VISIBLE | ES_RIGHT | WS_CHILD | SS_CENTERIMAGE, 310, 430, 680, 60, hWnd, NULL, NULL, NULL);
}