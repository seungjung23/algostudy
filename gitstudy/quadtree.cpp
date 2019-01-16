#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>

#define MAX 1001

using namespace std;
char quad[MAX];

void print(int s, int e)
{
	int point = s;
		while ((quad[point] == 'b' || quad[point] == 'w'))
		{
			if (point == e)
			{
				printf("%c", quad[point]);
				return;
			}
			printf("%c", quad[point]);
			point++;
		}

	if (quad[point] == 'x')
	{ //x이면나뉘어지는부분을찾고나누어서반전시킴
		int wbcnt = 1;
		int p1 = 0, p2 = 0, p3 = 0, p4 = 0;

		for (p1 = s + 1; p1 <= e; p1++)
		{
			if (quad[p1] == 'x')
				wbcnt += 3;
			else if (quad[p1] == 'b' || quad[p1] == 'w')
				wbcnt--;
			if (wbcnt == 0)
				break;
		}

		wbcnt = 1;
		for (p2 = p1 + 1; p2 <= e; p2++)
		{
			if (quad[p2] == 'x')
				wbcnt += 3;
			else if (quad[p2] == 'b' || quad[p2] == 'w')
				wbcnt--;
			if (wbcnt == 0)
				break;
		}

		wbcnt = 1;
		for (p3 = p2 + 1; p3 <= e; p3++)
		{
			if (quad[p3] == 'x')
				wbcnt += 3;
			else if (quad[p3] == 'b' || quad[p3] == 'w')
				wbcnt--;
			if (wbcnt == 0)
				break;
		}

		wbcnt = 1;
		for (p4 = p3 + 1; p4 <= e; p4++)
		{
			if (quad[p4] == 'x')
				wbcnt += 3;
			else if (quad[p4] == 'b' || quad[p4] == 'w')
				wbcnt--;
			if (wbcnt == 0)
				break;
		}

		printf("x");
		print(p2 + 1, p3);
		print(p3 + 1, p4);
		print(s + 1, p1);
		print(p1 + 1, p2);
	}
	return;
}

int main()
{
	int t;
	scanf("%d", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		memset(quad, 0, sizeof(quad));
		cin >> quad;
		print(0, strlen(quad) - 1);
	}
}

