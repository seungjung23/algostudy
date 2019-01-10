#include <stdio.h>
int map[16];
int ans;
int swit[10][5] = 
{ 
	{0,1,2},
	{3,7,9,11},
	{4,10,14,15},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15},
	{3,14,15},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13} 
};

int main()
{
	int t;
	scanf("%d", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		for (int i = 0; i < 16; i++)
		{
			scanf("%d", &map[i]);
			if (map[i] == 12)
				map[i] = 0;
		}



		printf("#%d %d\n", tc, ans);
	}
}
