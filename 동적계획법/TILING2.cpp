#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
int cache[101];

int tiling(int width)
{
	if (width <= 1) return 1; 
	//기저사례: 넓이가 1이 남았을 때, 한가지 방법만 가능함.
	int &ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;
}
int main()
{
	memset(cache, -1, sizeof(cache));
	

	cout << tiling(5) << endl;

	return 0;
}