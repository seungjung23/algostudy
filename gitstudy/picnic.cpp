#include <stdio.h>
#include <time.h>

int checknum[10]; //�̹� ¦�� ���������� Ȯ���ϴ� �迭
int map[10][10]; //ģ���� Ȯ���ϴ� map
int ans;
int n, m;
int tn; //¦�� �� n/2


void match(int cnt) //cnt ���°, up -�̻��� ���� ����
{
	
	if (cnt == tn) // ��� ¦�� �������� ��
	{
		ans++; return;
	}

	int tmp = 0;
	while (!checknum[tmp])
		tmp++;
	int flag = 0;
	for (int j = tmp + 1; j < n; j++)
	{
		if (map[tmp][j] == 1 && checknum[j])
		{
			checknum[tmp] = 0;
			checknum[j] = 0;
			match(cnt + 1);
			checknum[tmp] = 1;
			checknum[j] = 1;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		ans = -1; return;
	}

	
	return;
}


int main()
{
	int t;
	scanf("%d", &t);
	//clock_t start, end;
	//start = clock();

	for (int tc = 1; tc <= t; tc++)
	{
		ans = 0;
		int num;
		scanf("%d %d", &n, &num);
		
		tn = n / 2;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				checknum[j] = 1;
				map[i][j] = map[j][i] = 0;
			}

		int tmpa, tmpb;

		while (getchar() != '\n');

		for (int i = 0; i < num; i++)
		{
			scanf("%d %d", &tmpa, &tmpb);
			map[tmpa][tmpb] = map[tmpb][tmpa] = 1;
		}
	
		match(0);
		printf("%d\n", ans);	
	}
	//end = clock();
	//printf("time : %f\n", (double)(end - start));
}

