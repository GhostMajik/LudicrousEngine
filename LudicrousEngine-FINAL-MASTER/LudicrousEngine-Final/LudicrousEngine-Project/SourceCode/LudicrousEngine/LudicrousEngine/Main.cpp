#include <windows.h>  
#include <winnt.h>
#include <WinUser.h>
#include <iostream>
#include <powrprof.h>
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  
#include <strsafe.h>
#include "InputInterfaceClass.h"

// Global variables  

// set up window class name and window title name
static TCHAR szWindowClass[] = _T("LudicrousEngineWindow"); 
static TCHAR szTitle[] = _T("LudicrousEngine");

HINSTANCE hInst;
InputInterfaceClass* Input;



// Forward declarations of functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK InputHandler(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;
	LPCWSTR WindowName;
	Input = new InputInterfaceClass();
	if (!Input) {
		return false;
	}
	Input->Initialize();
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

	// The parameters to CreateWindow explained:  
	// szWindowClass: the name of the application  
	// szTitle: the text that appears in the title bar  
	// WS_OVERLAPPEDWINDOW: the type of window to create  
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
	// 500, 100: initial size (width, length)  
	// NULL: the parent of this window  
	// NULL: this application does not have a menu bar  
	// hInstance: the first parameter from WinMain  
	// NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}
	//Change background color

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
	SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)brush);

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//not sure if needed to set focus
	SetFocus(hWnd);

	return (int)msg.wParam;
}

//create input event handler to handle messages from main that 
LRESULT CALLBACK InputHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			Input->GetKeyDown((UINT)wParam);
			return 0;
		}
		case WM_KEYUP:
		{
			Input->GetKeyUp((UINT)wParam);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			Input->LeftMouseDown((UINT)wParam);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			Input->LeftMouseUp((UINT)wParam);
			return 0;
		}
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("12345");
	LPSTR keyMessage = "KeyDown: ";
	TCHAR outputMessage[16] = {};
	LPSTR mouseMessage = "mouseDown: ";
	TCHAR mouseInputMessage[20] = {};

	ZeroMemory(outputMessage, sizeof(outputMessage[0] * 16));
	ZeroMemory(mouseInputMessage, sizeof(mouseInputMessage[0] * 18));

	switch (message)
	{
	case WM_INPUT: {
		InputHandler(hWnd, message, wParam, lParam);
	
	}

	case WM_CHAR: {
		InputHandler(hWnd, message, wParam, lParam);
		for (int i = 0; i < 256; i++) {
			if (Input->IsKeyPressed(i))
			{
				LPSTR keyNamedValue = new char(i);
				keyMessage = " Key Pressed";
				StringCchCopy(outputMessage, 2, keyNamedValue);
				StringCchCat(outputMessage, 16, keyMessage);
				OutputDebugString("COLIN\n");
				OutputDebugString(outputMessage);
			}	
		}
		
	}
	//paint message here, need to output button/key pressed in WM_PAINT
	case WM_PAINT:
		InvalidateRect(hWnd, NULL, false);
		hdc = BeginPaint(hWnd, &ps);

		SetWindowText(hWnd,"LudicrousEngine");
		TextOut(hdc, 350, 300, outputMessage, (sizeof(outputMessage) / sizeof(*outputMessage)));
		//TextOut(hdc, 200, 200, mouseInputMessage, (sizeof(mouseInputMessage) / sizeof(*mouseInputMessage)));
		

		

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return InputHandler(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}