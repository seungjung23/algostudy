#include <iostream>
#include <vector>
int map[100][100];
int cache[100][100];
int N;

using namespace std;

int jump(int y, int x)
{

	if (x < 0 || x >= N || y < 0 || y >= N)
		return 0;
	if (x == N - 1 && y == N - 1)
		return 1;

	int& ret = cache[y][x];
	if (ret != -1)return ret;

	int n = map[y][x];
	return ret = jump(y, x + n) || jump(y + n, x);
}


int main()
{
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cin >> N;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin>>map[i][j];
				cache[i][j] = -1;
			}
		}

		int ans = jump(0, 0);

		if(ans)
			cout << "YES" << endl;
		else if (ans == 0)
			cout << "NO" << endl;
	}
}