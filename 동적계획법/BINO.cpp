#include <iostream>
using namespace std;

int bino(int n, int r)
{
	if (r == 0 || n == r) return 1;
	return bino(n - 1, r - 1) + bino(n - 1, r);
}

int main()
{
	int n, r;
	cin >> n >> r;

	int ret = bino(n, r);
	cout << ret << endl;
}

