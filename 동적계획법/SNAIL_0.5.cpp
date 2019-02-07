#include <iostream>
#include <cstring>
#include <math.h>
#define MAXD 1000
using namespace std;

int cache[MAXD][2 * MAXD + 1];
int N, M;

int climb(int day, int sum)
{
	if (day == M) 
		return (sum >= N) ? 1 : 0;

	if (cache[day][sum] != -1) 
		return cache[day][sum];

	return cache[day][sum] = climb(day + 1, sum + 1) + climb(day + 1, sum + 2);
}


int main()
{
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cin >> N >> M;
		memset(cache, -1, sizeof(cache));
		
		cout << climb(0, 0) / pow(2, M) << endl;
	}
}

