// TestWin32.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "TestWin32.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_LBUTTONDOWN)
	{
		HWND h_find_wnd = NULL;
		//찾을 단톡방의 핸들에 NULL값을 넣어준다.
		while (h_find_wnd = FindWindowEx(NULL, h_find_wnd, L"#32770", NULL))
		{ //단톡방은 대화상자 윈도우이기에 대화상자를 가진 윈도우를 while문으로 반복하여 찾음.
			HWND h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"RichEdit20W", NULL);
			//단톡방의 윈도우에 edit윈도우를 찾는다.
			if (h_edit_wnd != NULL)
			{
					SendMessage(h_edit_wnd, WM_SETTEXT, 0, (LPARAM)L"클릭으로 글 보내기");

					Sleep(200);
					//위의 메세지를 처리한 후 다음 메세지를 처리할 수 있도록 텀을 준다.
					PostMessage(h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C001);
					//엔터키 DOWN 상태
					PostMessage(h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C001);
					//엔터키가 UP 상태
					break;
					//break를 없애면 여러 단톡방을 찾아서 다 보낸다.
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