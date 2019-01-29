#include <stdio.h>
#include <time.h>
int max;
int sche[15][2];
int n;
int check[15];

void dfs(int cnt, int sum)
{
	if (cnt >= n - 1)
	{
		if (sche[n - 1][0] == 1 && check[n - 1])
			sum += sche[n - 1][1];
		max = (max < sum) ? sum : max;
		return;
	}

	int tmp = 0;
	if (check[cnt] && (sche[cnt][0] + cnt <= n))//상담을 잡을 수 있는 경우
	{
		for (tmp = 0; tmp < sche[cnt][0]; tmp++)
			check[cnt + tmp] = 0;
		dfs(cnt + tmp, sum + sche[cnt][1]); //잡거나
		for (tmp = 0; tmp < sche[cnt][0]; tmp++)
			check[cnt + tmp] = 1;
		dfs(cnt + 1, sum); //잡지않는다.
	}
	else
	{
		dfs(cnt + 1, sum); //잡지않는다.
	}
	return;
}

int main()
{
	scanf("%d", &n);
	max = 0;
	for (int i = 0; i < n; i++)
	{
		check[i] = 1;
	}

	int a, b;
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &a, &b);
		sche[i][0] = a;
		sche[i][1] = b;
	}
	dfs(0, 0);
	printf("%d\n", max);
}

