// ----------------------------------------------------------------------------
// win.cpp 
// ----------------------------------------------------------------------------
#include "win.h"
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

ATOM WindowsApp::AppRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_szWindowClass;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wcex);
}

BOOL WindowsApp::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	m_handleInstance = hInstance;

	RECT rc = { 0, 0, 1280, 720 };

	m_windowsHandle = CreateWindow(
		m_szWindowClass,
		m_szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!m_windowsHandle)
	{
		return FALSE;
	}

	ShowWindow(m_windowsHandle, nCmdShow);
	UpdateWindow(m_windowsHandle);

	return TRUE;
}

WindowsApp::WindowsApp(HINSTANCE hInstance, int nCmdShow)
	: m_initialized(false)
{
	_stprintf_s(m_szTitle, MAX_LOADSTRING, L"Title");
	_stprintf_s(m_szWindowClass, MAX_LOADSTRING, L"APP");
	AppRegisterClass(hInstance);

	if (InitInstance(hInstance, nCmdShow))
	{
		m_initialized = true;
	}
}

WindowsApp::~WindowsApp()
{
}

int WindowsApp::MainLoop()
{
	m_initialized = true;
	if (!m_initialized)
	{
		return 0;
	}
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Draw();
		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
	wmId = LOWORD(wParam);
	wmEvent = HIWORD(wParam);
	break;
	case WM_LBUTTONDOWN:
	break;
	case WM_LBUTTONUP:
	break;
	case WM_KEYDOWN:
	break;
	case WM_PAINT:
	hdc = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);
	break;
	case WM_DESTROY:
	PostQuitMessage(0);
	break;
	default:
	return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


