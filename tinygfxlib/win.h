// ----------------------------------------------------------------------------
// win.h 
// ----------------------------------------------------------------------------
// Description : ウィンドウを書くためのラッパ. 
#pragma once
#include <windows.h>

#define MAX_LOADSTRING 100

class WindowsApp
{
public:
	HWND                        m_windowsHandle;
	HINSTANCE                   m_handleInstance;
	TCHAR                       m_szTitle      [MAX_LOADSTRING];
	TCHAR                       m_szWindowClass[MAX_LOADSTRING];
	bool                        m_initialized;

	ATOM AppRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

public:

	WindowsApp(HINSTANCE hInstance, int nCmdShow);
	virtual ~WindowsApp();

	int                         MainLoop();

	virtual void                Update() = 0;
	virtual void                Draw() = 0;

}; // class WindowsApp 


