#include <stdio.h>
#include <math.h>
#include <string.h>

#define INF 987654321
using namespace std;


int ans;
int n, s;
int A[101];
int Asum[101];
int Adoublesum[101];
int cache[101][11];

int min(int a, int b)
{
	return (a >= b) ? b : a;
}

void sort()
{
	int tmp = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			if (A[i] > A[j])
			{
				tmp = A[i];
				A[i] = A[j];
				A[j] = tmp;
			}
		}
}

void precal()
{
	Asum[0] = A[0];
	Adoublesum[0] = A[0] * A[0];

	for (int i = 1; i < n; i++)
	{
		Asum[i] = Asum[i - 1] + A[i];
		Adoublesum[i] = Adoublesum[i - 1] + A[i] * A[i];
	}
}

int minError(int a, int b)
{
	int sum = Asum[b] - ((a == 0) ? 0 : Asum[a - 1]);
	int doublesum = Adoublesum[b] - ((a == 0) ? 0 : Adoublesum[a - 1]);
	int m = int(0.5 + (double)sum / (b - a + 1));

	int ret = doublesum - 2 * m * sum + m * m * (b - a + 1);
	
	return ret;
}

int quantize(int from, int parts)
{
	if (from == n) //모든 숫자를 양자화 끝냈을 때 return
		return 0;
	if (parts == 0) //숫자는 남았지만 남은 양자가 없을 때 아주 큰 값 반환
		return INF;

	int &ret = cache[from][parts]; //ret의 값이 cache에 들어가도록

	if (ret != -1) return ret;

	ret = INF;

	for (int size = 1; size <= n - from; size++)
		ret = min(ret, minError(from, from + size - 1) + quantize(from + size, parts - 1));
	
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		ans = 0;
		scanf("%d %d", &n, &s);
		memset(cache, -1, sizeof(cache));
		
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);

		sort();
		precal();
		

		
		printf("%d\n", quantize(0, s));
	}
}