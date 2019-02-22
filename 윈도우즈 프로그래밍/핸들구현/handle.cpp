#include <iostream>
#include <string.h>

using namespace std;
typedef unsigned int HANDLE;

struct HandleData 
{ //핸들값과, 문자열의 포인터를 묶어서 관리
	HANDLE h;
	char *p_string;
};

class HandleManager
{

private:
	unsigned int m_max_count; //갯수를 멤버로 보관하기.
	unsigned int m_gen_value; 
	HandleData *mp_data;

public:
	HandleManager(unsigned int a_max_count=50) //디폴트 매개변수
	{//사용자가 값을 넘기지 않으면 50으로 
	 //핸들의 갯수를 정한다.
	 //생성자
		m_gen_value = 1;
		m_max_count = a_max_count;
		mp_data = new HandleData[m_max_count];
		memset(mp_data, 0, sizeof(HandleData)*m_max_count);			
		//왜 0으로 채우나, 아직 0이면 이 핸들이 비어있다고 구분
		cout << "핸들 관리자가 생성되었습니다." << endl;		
	}
	
	~HandleManager()
	{
		HandleData *p = mp_data;
		for (unsigned int i = 0; i < m_max_count; i++)
		{
			if (p->h)
				delete[] p->p_string;
			p++;
		}
		delete[] mp_data;
		cout << "핸들관리자가 관리하던 문자열 모두 제거!!" << endl;
	}

	HANDLE InsertString(const char *ap_string)
	{
		HandleData *p = mp_data;
		unsigned int i;
		for (i = 0; i < m_max_count; i++)
		{ //비어있는 핸들 찾기
			if (p->h == 0)
				break;
			p++;
		}
		if (i < m_max_count)
		{
			p->h = m_gen_value++;
			int len = strlen(ap_string) + 1;//널문자 복사 +1
			p->p_string = new char[len];
			memcpy(p->p_string, ap_string, len);
			cout << p->p_string << ": 문자열 추가!!" << endl;
			return p->h;		
		}
		else //핸들이 꽉 찼다.
		{
			cout << "더 이상 문자열을 추가할 수 없습니다!" << endl;
			return 0xFFFFFFFF;
		}		
	}

	void PrintString(HANDLE a_h)
	{
		HandleData *p = mp_data;
		for (unsigned int i = 0; i < m_max_count; i++)
		{ 
			if (p->h == a_h)
			{
				cout << p->p_string << endl;
				return;
			}
			p++;
		}
		cout << "유효하지 않은 핸들값을 사용했습니다." << endl;
	}


	void DeleteString(HANDLE a_h)
	{
		HandleData *p = mp_data;
		for (unsigned int i = 0; i < m_max_count; i++)
		{
			if (p->h == a_h)
			{
				cout << p->p_string << ": 해당하는 핸들을 삭제!!" << endl;
				delete[] p->p_string;
				p->h = 0;
				return;
			}
			p++;
		}
		cout << "유효하지 않은 핸들값을 사용했습니다." << endl;
	}
};



int main()
{
	HandleManager str_list(30); //30개의 핸들 갯수를 넘겨줌.
	
	HANDLE h_str = str_list.InsertString("Hello~ Seungjung");
	str_list.PrintString(h_str);
	str_list.DeleteString(h_str);
	str_list.PrintString(h_str);

	return 0;
}

	/*관리하는 사람이 자기가 내부적으로 할당한 메모리를 쓰는 사람이 모르게
	핸들과 같은 기법을 CLASS로 만들어보기
	관리하는 사람과 쓰는 사람을 명확하게 구분하기 위해 CLASS사용
	저장된 위치를 알려주지 않고 사용할 수 있도록
	*/