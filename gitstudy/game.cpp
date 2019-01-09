#include <stdio.h>

int map[20][20];
int n, m, ans, cnt;

void fill(int t)
{
	if (cnt == t)//���� ���� ä��
	{
		ans++; return;
	}

	int x, y;
	//��� ���� �����Ͽ� 1,2,3,4�� ������� ä���.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0)
			{
				x = j, y = i;
				break;
			}
		}

	// {-1,0},{1,0},{0,-1},{0,1}
	   // ��    ��    ��     ��
	// 1�� ��� �� 2����� ��  3����� �� 4����� ��
	
	//1���	
	if (!map[y - 1][x] && !map[y][x - 1])
	{
		map[y - 1][x] = 1;
		map[y][x] = 1;
		map[y][x - 1] = 1;
		fill(t++);
		map[y - 1][x] = 0;
		map[y][x] = 0;
		map[y][x - 1] = 0;
	}

	//2���	
	if (!map[y - 1][x] && !map[y][x + 1])
	{
		map[y - 1][x] = 1; 
		map[y][x] = 1;
		map[y][x + 1] = 1;
		fill(t++);
		map[y - 1][x] = 0;
		map[y][x] = 0;
		map[y][x + 1] = 0;
	}

	//3���	
	if (!map[y + 1][x] && !map[y][x - 1])
	{
		map[y + 1][x] = 1;
		map[y][x] = 1;
		map[y][x - 1] = 1;
		fill(t++);
		map[y + 1][x] = 0;
		map[y][x] = 0;
		map[y][x - 1] = 0;
	}

	//4���	
	if (!map[y + 1][x] && !map[y][x + 1])
	{
		map[y + 1][x] = 1;
		map[y][x] = 1;
		map[y][x + 1] = 1;
		fill(t++);
		map[y + 1][x] = 0;
		map[y][x] = 0;
		map[y][x + 1] = 0;
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
		char tmp;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				scanf("%c", &tmp);
				if (tmp == '#')
					map[i][j] = 1;
				else if (tmp == '.')
				{
					map[i][j] = 0;
					cnt++;
				}
			}
		cnt /= 3; //�� �� �ִ� ���� ����
		fill(0);
		printf("#%d %d\n", tc, ans);
	}
}

