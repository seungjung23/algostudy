#include <iostream>
#include <vector>
#define max(a,b) (a>b)?a:b

using namespace std;
int N;
vector<int> cache;
vector<int> S;

int lis2(int start)
{
	int& ret = cache[start];
	if (ret != -1) return ret;

	ret = 1;

	for (int next = start + 1; next < N; next++)
	{
		if (S[start] < S[next])
			ret = max(ret, lis2(next) + 1);
	}
	return ret;
}


int main()
{
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cin >> N;
		int tmp;

		for (int i = 0; i < N; i++)
		{
			cache.push_back(-1);
			scanf("%d", &tmp);
			S.push_back(tmp);
		}
		
		int ans = 0;

		for (int i = 0; i < N; i++)
		{
			ans = max(ans, lis2(i));
		}

		cache.clear();
		S.clear();

		cout << ans << endl;
	}
}

