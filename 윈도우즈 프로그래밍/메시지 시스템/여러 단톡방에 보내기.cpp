// TestWin32.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "TestWin32.h"

#define MAX_COUNT 30

HWND gh_chat_edit, gh_send_btn, gh_list_box;
HFONT gh_font;

struct TalkStruct
{
	HWND h_talk_wnd;
	HWND h_edit_wnd;
	wchar_t title[256];
};

TalkStruct g_talk_list[MAX_COUNT];
int count = 0;

void FindTalkWindow()
{	
	HWND tmp_wnd = NULL; //찾았던 카톡방 또 찾지 않도록 p++때문에 따로 저장해 줘야 한다.
	TalkStruct *p = g_talk_list;
	
	//p->h_talk_wnd = NULL; 이미 널이 들어있기때문에 필요없는 코드
	

	while (tmp_wnd = FindWindowEx(NULL, tmp_wnd, L"#32770", NULL))
	{
		p->h_edit_wnd = FindWindowEx(tmp_wnd, NULL, L"RichEdit20W", NULL);
		if (p->h_edit_wnd != NULL)
		{ //카톡방을 찾은 경우 반복 중단
			p->h_talk_wnd = tmp_wnd;
			wchar_t str[256];
			GetWindowText(p->h_talk_wnd, p->title, 256);
			swprintf_s(str, 256, L"카톡방%d : %s", count + 1, p->title);
			SendMessage(gh_list_box, LB_INSERTSTRING, count, (LPARAM)str);
			count++; p++;
		}
	}
}

void SendChatData()
{	
	
	if (count == 0)return;

	wchar_t str[128];
	GetWindowText(gh_chat_edit, str, 128);
	
	int index=SendMessage(gh_list_box, LB_INSERTSTRING, -1, (LPARAM)str);
	SendMessage(gh_list_box, LB_SETCURSEL, index, 0);

	TalkStruct *p = g_talk_list;
	for (int i = 0; i < count; i++)
	{
		SendMessage(p->h_edit_wnd, WM_SETTEXT, 0, (LPARAM)str);
		p++;
	}

	Sleep(200);

	p = g_talk_list;
	for (int i = 0; i < count; i++)
	{
		PostMessage(p->h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C001);
		PostMessage(p->h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C001);
		p++;
	}
	SetWindowText(gh_chat_edit, L"");
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		gh_font = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, 
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"굴림체");

		//에디트컨트롤 만들기
		gh_chat_edit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 
			5, 303, 532, 28, hWnd, (HMENU)25002, NULL, NULL);
		SendMessage(gh_chat_edit, WM_SETFONT, (WPARAM)gh_font, 1);
		//Ex쓰는게 좋은것이 확장속성 가능 (첫번째 인자)
		//3d효과등등
		//EDIT컨트롤로 만들기 위해서 인자 넣음
		//수평 스크롤
		//부모가 hWnd
		//HMENU 메뉴하고 상관없고, 에디트 컨트롤로 만들었는데 여러개 에디트컨트롤과 구분하기 위한 번호
		//나머지 지금 알필요 없이 NULL
		
		gh_send_btn = CreateWindow(L"BUTTON", L"전송",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			540, 301, 80, 31, hWnd, (HMENU)25003, NULL, NULL);
		SendMessage(gh_send_btn, WM_SETFONT, (WPARAM)gh_font, 1);

		gh_list_box = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,
			5, 5, 615, 300, hWnd, (HMENU)25001, NULL, NULL);
		SendMessage(gh_list_box, WM_SETFONT, (WPARAM)gh_font, 1);
		FindTalkWindow();
	}
	else if (uMsg == WM_COMMAND)
	{
		if (LOWORD(wParam) == 25003)
			SendChatData();
	}
	else if (uMsg == WM_DESTROY) 
	{
		DestroyWindow(gh_chat_edit); //에디트 컨트롤 삭제
		DestroyWindow(gh_send_btn); //버튼 컨트롤 삭제
		DestroyWindow(gh_list_box); //리스트 박스 삭제
		DeleteObject(gh_font);
		PostQuitMessage(0);
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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 50, 50, 640, 374, NULL, NULL, hInstance, NULL);
	//WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU   크기 못변하게 조정하기
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
