#include <iostream>
#include <cstring>
using namespace std;
int cache[30][30];

int binodp(int n, int r)
{
	if (r == 0 || n == r) return 1;

	if (cache[n][r] != -1) return cache[n][r];

	return cache[n][r] = binodp(n - 1, r - 1) + binodp(n - 1, r);
}


int main()
{
	int n, r;
	cin >> n >> r;
	memset(cache, -1, sizeof(cache));

	int ret = binodp(n, r);
	cout << ret << endl;
}

