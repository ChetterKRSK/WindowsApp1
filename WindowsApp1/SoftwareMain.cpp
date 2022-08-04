#include <Windows.h>
#include "SoftwareDefinitions.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	GetDesktopResolution();

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_WINLOGO), L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"First window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, desktopX / 3, desktopY / 3, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

void GetDesktopResolution()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	::desktopX = desktop.right;
	::desktopY = desktop.bottom;
}

BOOL CALLBACK DestoryChildCallback(HWND hwnd, LPARAM lp)
{
	if (hwnd != NULL)
		DestroyWindow(hwnd);

	return TRUE;
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
	case WM_SIZE:
		windowX = LOWORD(lp);
		windowY = HIWORD(lp);
		EnumChildWindows(hWnd, DestoryChildCallback, NULL);
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		break;
	case WM_COMMAND:
		switch (wp)
		{
		case OnFileMenuAction1:
			MessageBoxA(hWnd, "Действие!", "Действие", MB_OK); break;
		case OnExitSoftware:
			PostQuitMessage(0); break;
		case OnHelpMenuAction1:
			MessageBoxA(hWnd, "Данное приложение было разработано бригадой, состоящей из одного человека, в рамках домашнего обучения средствам WinApi и не имеет никакой полезной нагрузки!\nУдачи!", "О приложении", MB_OK); break;
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
			AppendMenu(SubFileActionMenu, MF_STRING, OnFileMenuAction1, L"Действие");
		}
		AppendMenu(SubFileMenu, MF_SEPARATOR, NULL, NULL);
		AppendMenu(SubFileMenu, MF_STRING, OnExitSoftware, L"Выход");
	}
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubHelpMenu, L"Справка");
	{
		AppendMenu(SubHelpMenu, MF_STRING, OnHelpMenuAction1, L"О приложении");
	}

	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 10, 10, windowX / 10, windowY / 10, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Draw", WS_VISIBLE | WS_CHILD | ES_CENTER, 20 + windowX / 10, 10, windowX / 10, windowY / 10, hWnd, NULL, NULL, NULL);

	CreateWindowA("static", "Status: Error", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | WS_BORDER, 30 + ((windowX / 10) * 2), 10, windowX - 40 - ((windowX / 10) * 2), windowY / 10, hWnd, NULL, NULL, NULL);

	CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 20 + (windowY / 10), windowX - 20, windowY - 40 - (windowY / 10) * 2, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Save", WS_VISIBLE | WS_CHILD | ES_CENTER, 10, windowY - 10 - (windowY / 10), windowX / 10, windowY / 10, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Load", WS_VISIBLE | WS_CHILD | ES_CENTER, 20 + (windowX / 10), windowY - 10 - (windowY / 10), windowX / 10, windowY / 10, hWnd, NULL, NULL, NULL);

	CreateWindowA("static", "Copyright © 2022", WS_VISIBLE | ES_RIGHT | WS_CHILD | SS_CENTERIMAGE, 30 + ((windowX / 10) * 2), windowY - 10 - (windowY / 10), windowX - ((windowX / 10) * 2) - 40, windowY / 10, hWnd, NULL, NULL, NULL);
}