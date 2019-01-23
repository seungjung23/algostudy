#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

string::iterator iter;
char cur;

string Decompress()
{
	cur = *iter;		// ó�� �Է¹��� string���� �Ź� ��� �������� ��ĭ�� ������ �̵�������. ��, �̵����ڿ� �Ұ���. 
	iter++;                         //  ��� �Է��� �� Ȯ���ϸ鼭 �Լ��� ��ȯ���� string���� ��ƹ����Ƿ� ��� ������Ű�� Ȯ���ص���.
	if (cur == 'w' || cur == 'b') return string(1, cur);

	string lu = Decompress();				// 1,2,3,4 ��и� ������� �ԷµǹǷ� ������� ���������ؾ��� 
	string ru = Decompress();
	string ld = Decompress();
	string rd = Decompress();

	return "x" + ld + rd + lu + ru;			// ��ȯ�Ҷ� 3,4,1,2 ������ ����� ��ȯ , ���ڿ��� ��ȯ�ع����Ƿ� �ش� ���ڿ��� �ٽ� ���� ������ �� ����
}


int main() {
	int tc;
	scanf("%d", &tc);

	for (int i = 0; i < tc; i++) {
		string s;
		cin >> s;
		iter = s.begin();

		cout << Decompress() << endl;
	}

}