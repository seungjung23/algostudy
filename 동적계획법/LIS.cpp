#include <iostream>
#include <vector>
#define max(a,b) (a>b)?a:b

using namespace std;

int N;

int lis(const vector<int>& A)
{
	if (A.empty()) 
		return 0;
	
	int ret = 0;

	for (int i = 0; i < A.size(); i++)
	{
		vector<int> B;
		for (int j = i + 1; j < A.size(); j++)
			if (A[i] < A[j])
				B.push_back(A[j]);

		ret = max(ret, 1 + lis(B));
	}
	
	return ret;
}


int main()
{
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cin >> N;
		vector<int> sub(N, 0);

		for (int i = 0; i < N; i++)
		{
			scanf("%d", &sub[i]);
		}

		cout << lis(sub) << endl;
		sub.clear();
	}
}

