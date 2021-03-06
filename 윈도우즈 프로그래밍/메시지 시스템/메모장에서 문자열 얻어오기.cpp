// TestWin32.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "TestWin32.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_LBUTTONDOWN)
	{
		HWND h_find_wnd = FindWindow(L"Notepad", NULL);
		//메모장의 핸들값을 얻는다.
		if (h_find_wnd != NULL)
		{
			HWND h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"Edit", NULL);
			//메모장의 메인윈도에 포함된 에디트 윈도우의 핸들값을 얻는다.
			if (h_edit_wnd != NULL)
			{
				wchar_t str[256];
				SendMessage(h_edit_wnd, WM_GETTEXT, 256, (LPARAM)str);
				                    //최대로 받아올 메모리의 크기 256, 메모리의 주소 str
				MessageBox(hWnd, str, L"에디트에 적힌 내용 확인", MB_OK);
			}
		}
		
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	wchar_t my_class_name[] = L"sjprogram";

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"Seungjung_Program", 
		WS_OVERLAPPEDWINDOW, 50, 50, 840, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
}