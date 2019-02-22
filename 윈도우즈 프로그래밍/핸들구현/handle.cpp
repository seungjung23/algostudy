#include <iostream>
#include <string.h>

using namespace std;
typedef unsigned int HANDLE;

struct HandleData 
{ //�ڵ鰪��, ���ڿ��� �����͸� ��� ����
	HANDLE h;
	char *p_string;
};

class HandleManager
{

private:
	unsigned int m_max_count; //������ ����� �����ϱ�.
	unsigned int m_gen_value; 
	HandleData *mp_data;

public:
	HandleManager(unsigned int a_max_count=50) //����Ʈ �Ű�����
	{//����ڰ� ���� �ѱ��� ������ 50���� 
	 //�ڵ��� ������ ���Ѵ�.
	 //������
		m_gen_value = 1;
		m_max_count = a_max_count;
		mp_data = new HandleData[m_max_count];
		memset(mp_data, 0, sizeof(HandleData)*m_max_count);			
		//�� 0���� ä�쳪, ���� 0�̸� �� �ڵ��� ����ִٰ� ����
		cout << "�ڵ� �����ڰ� �����Ǿ����ϴ�." << endl;		
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
		cout << "�ڵ�����ڰ� �����ϴ� ���ڿ� ��� ����!!" << endl;
	}

	HANDLE InsertString(const char *ap_string)
	{
		HandleData *p = mp_data;
		unsigned int i;
		for (i = 0; i < m_max_count; i++)
		{ //����ִ� �ڵ� ã��
			if (p->h == 0)
				break;
			p++;
		}
		if (i < m_max_count)
		{
			p->h = m_gen_value++;
			int len = strlen(ap_string) + 1;//�ι��� ���� +1
			p->p_string = new char[len];
			memcpy(p->p_string, ap_string, len);
			cout << p->p_string << ": ���ڿ� �߰�!!" << endl;
			return p->h;		
		}
		else //�ڵ��� �� á��.
		{
			cout << "�� �̻� ���ڿ��� �߰��� �� �����ϴ�!" << endl;
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
		cout << "��ȿ���� ���� �ڵ鰪�� ����߽��ϴ�." << endl;
	}


	void DeleteString(HANDLE a_h)
	{
		HandleData *p = mp_data;
		for (unsigned int i = 0; i < m_max_count; i++)
		{
			if (p->h == a_h)
			{
				cout << p->p_string << ": �ش��ϴ� �ڵ��� ����!!" << endl;
				delete[] p->p_string;
				p->h = 0;
				return;
			}
			p++;
		}
		cout << "��ȿ���� ���� �ڵ鰪�� ����߽��ϴ�." << endl;
	}
};



int main()
{
	HandleManager str_list(30); //30���� �ڵ� ������ �Ѱ���.
	
	HANDLE h_str = str_list.InsertString("Hello~ Seungjung");
	str_list.PrintString(h_str);
	str_list.DeleteString(h_str);
	str_list.PrintString(h_str);

	return 0;
}

	/*�����ϴ� ����� �ڱⰡ ���������� �Ҵ��� �޸𸮸� ���� ����� �𸣰�
	�ڵ�� ���� ����� CLASS�� ������
	�����ϴ� ����� ���� ����� ��Ȯ�ϰ� �����ϱ� ���� CLASS���
	����� ��ġ�� �˷����� �ʰ� ����� �� �ֵ���
	*/