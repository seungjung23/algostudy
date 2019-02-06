#include <iostream>
#include <vector>
#include <string>
#define max(a,b) (a>b)?a:b

using namespace std;

int N, W;

string name[100];
vector<int> w; //부피
vector<int> n; //절박도
vector<vector<int>> cache;



int packing(int num, int capacity) //몇번째 아이템, 남은 용량
{
	if (num == N) //모든 물건 순회 했을 때, return
		return 0;
	
	int &ret = cache[num][capacity];
	if (ret != -1) return ret;

	ret = packing(num + 1, capacity); //아이템을 넣지 않았을 때

	if (capacity >= w[num]) //남은 용량에 들어갈 수 있을 때, 아이템 넣기
	{
		ret = max(ret, packing(num + 1, capacity - w[num]) + n[num]);
	}

	return ret;
}

void reconstruct(int num, int capacity, vector<int>& pick)
{
	if (num == N)
		return;

	if (packing(num, capacity) == packing(num + 1, capacity)) 
	{
		reconstruct(num + 1, capacity, pick);
	}
	else
	{
		pick.push_back(num);
		reconstruct(num + 1, capacity - w[num], pick);
	}
	return;
}

int main()
{
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cin >> N >> W;

		for (int i = 0; i < N; i++)
		{
			w.push_back(0);
			n.push_back(0);
		}

		for (int i = 0; i < N; i++)
		{
			cin >> name[i];
			cin >> w[i];
			cin >> n[i];
		}

		for (int i = 0; i < N; i++)
		{
			vector<int> ele(W + 1, -1);
			cache.push_back(ele); 
		}
		int ans = 0;
		ans = packing(0, W);

		vector<int> pick;
		reconstruct(0, W, pick);

		cout << ans << ' ' << pick.size() << endl;

		for (int i = 0; i < pick.size(); i++)
		{
			cout << name[pick[i]] << endl;
		}
		
		w.clear(); 
		n.clear(); 		
		cache.clear();		
		pick.clear();
	}
}

