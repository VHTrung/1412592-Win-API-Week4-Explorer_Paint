// Simple Paint.cpp : Defines the entry CPoint for the application.
//
#include "stdafx.h"
#include <windowsx.h>
#include "Simple Paint.h"
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include <vector>
using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szBuffer[MAX_LOADSTRING + 20];
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
bool g_isDrawing = false;
HWND g_hWnd;
vector<CShape*> g_shapes;
CPoint g_leftTop, g_rightBottom/*, g_currentMouse*/;
CShape* g_currentShape;
HBITMAP backbuffer;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEPAINT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLEPAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SIMPLEPAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:


		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_TOOLS_BUFFERING:
		{
			if (GetMenuState(GetMenu(g_hWnd), ID_TOOLS_BUFFERING, 0) == MFS_UNCHECKED)
				CheckMenuItem(GetMenu(g_hWnd), ID_TOOLS_BUFFERING, MFS_CHECKED);
			else
				CheckMenuItem(GetMenu(g_hWnd), ID_TOOLS_BUFFERING, MFS_UNCHECKED);
			//InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case ID_DRAW_LINE:
		{
			if (GetMenuState(GetMenu(g_hWnd), ID_DRAW_LINE, 0) == MFS_UNCHECKED)
			{
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_LINE, MFS_CHECKED);
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_ELLIPSE, MFS_UNCHECKED);
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_RECTANGLE, MFS_UNCHECKED);
			}

			break;
		}
		case ID_DRAW_RECTANGLE:
		{
			if (GetMenuState(GetMenu(g_hWnd), ID_DRAW_RECTANGLE, 0) == MFS_UNCHECKED)
			{
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_RECTANGLE, MFS_CHECKED);
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_LINE, MFS_UNCHECKED);
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_ELLIPSE, MFS_UNCHECKED);
			}

			break;
		}
		case ID_DRAW_ELLIPSE:
		{
			if (GetMenuState(GetMenu(g_hWnd), ID_DRAW_ELLIPSE, 0) == MFS_UNCHECKED)
			{
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_ELLIPSE, MFS_CHECKED);
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_LINE, MFS_UNCHECKED);
				CheckMenuItem(GetMenu(g_hWnd), ID_DRAW_RECTANGLE, MFS_UNCHECKED);
			}

			break;
		}

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{

		if (!g_isDrawing)
		{


			g_isDrawing = true;
			g_leftTop.m_X = GET_X_LPARAM(lParam);
			g_leftTop.m_Y = GET_Y_LPARAM(lParam);

			if (GetMenuState(GetMenu(g_hWnd), ID_DRAW_LINE, 0) == MFS_CHECKED)
			{
				g_currentShape = new CLine;
				g_currentShape->SetData(g_leftTop, g_leftTop);
			}
			else if (GetMenuState(GetMenu(g_hWnd), ID_DRAW_RECTANGLE, 0) == MFS_CHECKED)
			{
				g_currentShape = new CRectangle;
				g_currentShape->SetData(g_leftTop, g_leftTop);
			}
			else if (GetMenuState(GetMenu(g_hWnd), ID_DRAW_ELLIPSE, 0) == MFS_CHECKED)
			{
				g_currentShape = new CEllipse;
				g_currentShape->SetData(g_leftTop, g_leftTop);
			}
			else
				break;
			//InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (g_isDrawing)
		{
			g_rightBottom.m_X = GET_X_LPARAM(lParam);
			g_rightBottom.m_Y = GET_Y_LPARAM(lParam);
			g_currentShape->SetData(g_leftTop, g_rightBottom);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else
		{
			g_leftTop.m_X = GET_X_LPARAM(lParam);
			g_leftTop.m_Y = GET_Y_LPARAM(lParam);
		}
		wsprintf(szBuffer, L"%ls (%d, %d)", szTitle, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		SetWindowText(hWnd, szBuffer);

		break;
	}
	case WM_LBUTTONUP:
	{
		g_rightBottom.m_X = GET_X_LPARAM(lParam);
		g_rightBottom.m_Y = GET_Y_LPARAM(lParam);


		g_shapes.push_back(g_currentShape);

		g_isDrawing = FALSE;

		//InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_SIZE:
	{

		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...

			CPaint::SetHDC(&hdc);
			for (unsigned int i = 0; i < g_shapes.size(); ++i)
			{
				g_shapes[i]->Paint();
			}
			if (g_isDrawing)
			{
				g_currentShape->Paint();
			}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		for (unsigned int i = 0; i < g_shapes.size(); ++i)
		{
			if (g_shapes[i])
				delete g_shapes[i];
		}
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
