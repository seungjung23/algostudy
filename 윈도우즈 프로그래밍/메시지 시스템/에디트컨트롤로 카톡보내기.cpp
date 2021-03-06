// TestWin32.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "TestWin32.h"

HWND gh_talk_wnd, gh_edit_wnd; //전역변수로 선언
HWND gh_chat_edit, gh_send_btn; 
//채팅을 입력할 에디트 컨트롤의 핸들 저장 변수
//채팅 전송용 버튼컨트롤의 핸들 저장 변수

//카톡방 찾는 함수 만들기
void FindTalkWindow()
{
	gh_talk_wnd = NULL;
	//찾을 단톡방의 핸들에 NULL값을 넣어준다.
	while (gh_talk_wnd = FindWindowEx(NULL, gh_talk_wnd, L"#32770", NULL))
	{ 
		gh_edit_wnd = FindWindowEx(gh_talk_wnd, NULL, L"RichEdit20W", NULL);
		if (gh_edit_wnd != NULL)
		{ //카톡방을 찾은 경우 반복 중단
			break;
		}
	}
}

void SendChatData()
{	
	if (gh_edit_wnd == NULL)return;

	wchar_t str[128];
	GetWindowText(gh_chat_edit, str, 128);
	//카톡방에 글쓰기!
	SendMessage(gh_edit_wnd, WM_SETTEXT, 0, (LPARAM)str);
	Sleep(200);
	//위의 메세지를 처리한 후 다음 메세지를 처리할 수 있도록 텀을 준다.
	PostMessage(gh_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C001);
	//엔터키 DOWN 상태
	PostMessage(gh_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C001);
	//엔터키가 UP 상태
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		//에디트컨트롤 만들기
		gh_chat_edit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 
			5, 303, 532, 28, hWnd, (HMENU)25002, NULL, NULL);
		//Ex쓰는게 좋은것이 확장속성 가능 (첫번째 인자)
		//3d효과등등
		//EDIT컨트롤로 만들기 위해서 인자 넣음
		//수평 스크롤
		//부모가 hWnd
		//HMENU 메뉴하고 상관없고, 에디트 컨트롤로 만들었는데 여러개 에디트컨트롤과 구분하기 위한 번호
		//나머지 지금 알필요 없이 NULL
		
		gh_send_btn = CreateWindow(L"Button", L"전송",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			540, 301, 80, 31, hWnd, (HMENU)25003, NULL, NULL);
		
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
