#include <stdio.h>
int map[20][20];
int n, m, ans, cnt;


//const int coverType[4][3][2] =
//{
//	{{0, -1}, {0, 0}, {-1, 0}},  	//  �� 1
//	{{0, -1}, {0, 0}, {1,  0}}, 	// ��  2
//	{{0, 1},  {0, 0}, {-1, 0}}, 	//  �� 3
//	{{0, 1},  {0, 0}, {1,  0}}		// ��  4
//};

void fill(int a, int b, int t)
{
	/*for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
	*/
	if (cnt == t)//���� ���� ä��
	{
		++ans; return;
	}

	int x, y;
	
	//��� ���� �����Ͽ� 1,2,3,4�� ������� ä���.
	for (int i = a; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if ((i == a) && j <= b) continue;
			
			if (map[i][j] == 0)
			{
				x = j, y = i;
				//1
				if (!map[y - 1][x] && !map[y][x - 1] && (y - 1) >= 0 && (x - 1) >= 0)
				{
					map[y - 1][x] = t + 1;
					map[y][x] = t + 1;
					map[y][x - 1] = t + 1;
					fill(y, x, t + 1);
					map[y - 1][x] = 0;
					map[y][x] = 0;
					map[y][x - 1] = 0;
				}

				//2
				if (!map[y - 1][x] && !map[y][x + 1] && (y - 1) >= 0 && (x + 1) < m)
				{
					map[y - 1][x] = t + 1;
					map[y][x] = t + 1;
					map[y][x + 1] = t + 1;
					fill(y, x, t + 1);
					map[y - 1][x] = 0;
					map[y][x] = 0;
					map[y][x + 1] = 0;
				}

				//3
				if (!map[y + 1][x] && !map[y][x - 1] && (y + 1) < n && (x - 1) >= 0)
				{
					map[y + 1][x] = t + 1;
					map[y][x] = t + 1;
					map[y][x - 1] = t + 1;
					fill(y, x, t + 1);
					map[y + 1][x] = 0;
					map[y][x] = 0;
					map[y][x - 1] = 0;
				}

				//4
				if (!map[y + 1][x] && !map[y][x + 1] && (y + 1) < n && (x + 1) < m)
				{
					map[y + 1][x] = t + 1;
					map[y][x] = t + 1;
					map[y][x + 1] = t + 1;
					fill(y, x, t + 1);
					map[y + 1][x] = 0;
					map[y][x] = 0;
					map[y][x + 1] = 0;
				}
			}
		}
}
	
void setting()
{
	char tmp;
	for (int i = 0; i < n; i++)
	{
		while (getchar() != '\n');
		for (int j = 0; j < m; j++)
		{
			scanf("%c", &tmp);
			if (tmp == '#')
				map[i][j] = 8;
			else if (tmp == '.')
			{
				map[i][j] = 0;
				cnt++;
			}
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d %d", &n, &m);
		cnt = 0;
		
		setting();
		
	
		//for (int i = 0; i < n; i++)
		//{
		//	for (int j = 0; j < m; j++)
		//	{
		//		printf("%d ", map[i][j]);
		//	}
		//	printf("\n");
		//}
		if (cnt % 3 != 0)
		{
			printf("#%d %d\n", tc, 0);
			continue;
		}
		cnt /= 3; //�� �� �ִ� ���� ����
		fill(0, 0, 0);
		printf("#%d %d\n", tc, ans);
	}
}

