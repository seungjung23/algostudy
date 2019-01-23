#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

string::iterator iter;
char cur;

string Decompress()
{
	cur = *iter;		// 처음 입력받은 string에서 매번 재귀 들어갈때마다 한칸씩 앞으로 이동시켜줌. 즉, 이동인자에 불과함. 
	iter++;                         //  모든 입력을 다 확인하면서 함수의 반환형인 string으로 담아버리므로 계속 증가시키며 확인해도됨.
	if (cur == 'w' || cur == 'b') return string(1, cur);

	string lu = Decompress();				// 1,2,3,4 사분면 순서대로 입력되므로 순서대로 압축해제해야함 
	string ru = Decompress();
	string ld = Decompress();
	string rd = Decompress();

	return "x" + ld + rd + lu + ru;			// 반환할때 3,4,1,2 순서로 뒤집어서 반환 , 문자열을 반환해버리므로 해당 문자열을 다시 순서 변경할 수 있음
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