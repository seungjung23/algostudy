#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int height[20000];

int func(int left, int right) {
	int ret;

	if (left == right) return height[left];				// base case 한칸일 경우 넓이 리턴
	int mid = (left + right) / 2;
	ret = max(func(left, mid), func(mid + 1, right));	// 절반 나눠서 재귀

	int center_l = mid;
	int center_r = mid + 1;
	int center_h = min(height[center_l], height[center_r]);	// 중간이 겹치는 경우 계산
	ret = max(ret, center_h * 2);							// 겹치는 부분 두칸 넓이

	while (left < center_l || center_r < right) {			// 중간부터 양옆 끝까지 닿을때 까지 진행
		if (center_r < right && (center_l == left || height[center_l - 1] < height[center_r + 1])) {	// 오른쪽이 높이가 더 클경우 혹은 왼쪽이 이미 끝에 도달한 경우
			center_r++;										// 우로 한칸 진행
			center_h = min(center_h, height[center_r]);		// 높이는 항상 작은값유지(넓이계산)
		}
		else {												// 왼쪽이 높이가 더 클경우 혹은 오른쪽이 이미 끝에 도달한 경우
			center_l--;										// 좌로 한칸 진행
			center_h = min(center_h, height[center_l]);
		}
		ret = max(ret, center_h*(center_r - center_l + 1));	// 한칸 진행할때마다 넓이 최대값저장
	}
	return ret;												// 좌측, 우측, 중간겹치는 부분 가장 넓은 넓이 반환
}

int main() {
	int tc;
	scanf("%d", &tc);

	for (int i = 0; i < tc; i++) {
		int n;
		scanf("%d", &n);

		for (int i = 0; i < n; i++) scanf("%d", &height[i]);

		printf("%d\n", func(0, n - 1));
	}

}