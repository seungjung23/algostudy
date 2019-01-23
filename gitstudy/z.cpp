#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int endr, endc = 0;
int ans;

void search(int startr, int startc, int size, int n)
{
	int next_size = size / 2;
	if (endr == startr && endc == startc) //base case
	{
		ans = n;
		return;
	}
	if (next_size >= 1)
	{
		if (startr <= endr && startr + next_size - 1 >= endr && startc <= endc && startc + next_size - 1 >= endc)
			search(startr, startc, next_size, n);
		else if (startr <= endr && startr + next_size - 1 >= endr && startc + next_size <= endc && startc + next_size * 2 - 1 > endc)
			search(startr, startc + next_size, next_size, n + (next_size) *(next_size) * 1);
		else if (startr + next_size <= endr && startr + next_size * 2 - 1 >= endr && startc <= endc && startc + next_size - 1 >= endc)
			search(startr + next_size, startc, next_size, n + (next_size) *(next_size) * 2);
		else if (startr + next_size <= endr && startr + next_size * 2 - 1 >= endr && startc + next_size <= endc && startc + next_size * 2 - 1 >= endc)
			search(startr + next_size, startc + next_size, next_size, n + (next_size) *(next_size) * 3);
	}

	return;
	}


 int main() {
	
	int n;
	scanf("%d %d %d", &n, &endr, &endc);
	
	search(0, 0, pow(2, n), 0);
	

	printf("%d\n", ans);

}