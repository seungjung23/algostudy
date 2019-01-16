#include <iostream>
#include <string>
#include <vector>

#include <time.h>
using namespace std;

vector<string> result;
string str;

string rvrs_quadTree(int *idx);

int main() {

	int T;
	scanf("%d", &T);
	clock_t start, end;
	start = clock();
	for (int t = 0; t < T; t++) {
		cin >> str;

		int idx = 0;
		result.push_back(rvrs_quadTree(&idx));
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
	
	end = clock();
	printf("time : %f\n", (double)(end - start));
}

string rvrs_quadTree(int *idx) {

	string rst, str1_2, str3_4;
	// base condition, idx �ڸ��� x�� �ƴϸ�
	if (str[*idx] != 'x') return rst += str[*idx];

	for (int i = 0; i < 4; i++) {		// x���� 3 4 1 2 ������ ���̱�
		char temp = str[++(*idx)];
		if (temp == 'x') {
			if (i < 2) str1_2 += rvrs_quadTree(idx);
			else str3_4 += rvrs_quadTree(idx);
		}
		else {
			if (i < 2) str1_2 += temp;
			else str3_4 += temp;
		}
	}
	return rst = 'x' + str3_4 + str1_2;


	
}