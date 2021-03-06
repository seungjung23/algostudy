// TestWin32.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "TestWin32.h"
#define MAXDATA 100
struct  drawdata
{
	int x, y; 
	char type;
};
drawdata drawd[MAXDATA];

HPEN gh_green_pen;
int cnt = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		HGDIOBJ h_old_pen = SelectObject(h_dc, gh_green_pen);
		drawdata *p = drawd;

		for (int i = 0; i < cnt; i++)
		{
			if (p->type)
				Ellipse(h_dc, p->x - 15, p->y - 15, p->x + 15, p->y + 15);
			else 
				Rectangle(h_dc, p->x - 15, p->y - 15, p->x + 15, p->y + 15);			
			p++;
		}

		SelectObject(h_dc, h_old_pen);
		EndPaint(hWnd, &ps);
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);
		int x =LOWORD(lParam);
		int y = HIWORD(lParam);

		if (cnt < MAXDATA) 
		{
			drawd[cnt].x = x;
			drawd[cnt].y = y;
			drawd[cnt].type = wParam & MK_CONTROL;
			cnt++;
		}
		
		HGDIOBJ h_old_pen = SelectObject(h_dc, gh_green_pen);

		if(wParam&MK_CONTROL)
			Ellipse(h_dc, x - 15, y - 15, x + 15, y + 15);
		else
			Rectangle(h_dc, x - 15, y - 15, x + 15, y + 15);

		SelectObject(h_dc, h_old_pen);
		ReleaseDC(hWnd, h_dc);
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

	gh_green_pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));


	HWND hWnd = CreateWindow(my_class_name, L"Seungjung_Program", 
		WS_OVERLAPPEDWINDOW, 50, 50, 400, 400, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteObject(gh_green_pen);
	
}