#include <stdio.h>

int map[20][20];
int n, m, ans, cnt;

void fill(int t)
{
	if (cnt == t)//블럭의 갯수 채움
	{
		ans++; return;
	}

	int x, y;
	//가운데 점을 지정하여 1,2,3,4번 모양으로 채운다.
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
	   // 상    하    좌     우
	// 1번 모양 ┘ 2번모양 └  3번모양 ┐ 4번모양 ┌
	
	//1모양	
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

	//2모양	
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

	//3모양	
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

	//4모양	
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
		cnt /= 3; //들어갈 수 있는 블럭의 갯수
		fill(0);
		printf("#%d %d\n", tc, ans);
	}
}

