#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int height[20000];

int func(int left, int right) {
	int ret;

	if (left == right) return height[left];				// base case ��ĭ�� ��� ���� ����
	int mid = (left + right) / 2;
	ret = max(func(left, mid), func(mid + 1, right));	// ���� ������ ���

	int center_l = mid;
	int center_r = mid + 1;
	int center_h = min(height[center_l], height[center_r]);	// �߰��� ��ġ�� ��� ���
	ret = max(ret, center_h * 2);							// ��ġ�� �κ� ��ĭ ����

	while (left < center_l || center_r < right) {			// �߰����� �翷 ������ ������ ���� ����
		if (center_r < right && (center_l == left || height[center_l - 1] < height[center_r + 1])) {	// �������� ���̰� �� Ŭ��� Ȥ�� ������ �̹� ���� ������ ���
			center_r++;										// ��� ��ĭ ����
			center_h = min(center_h, height[center_r]);		// ���̴� �׻� ����������(���̰��)
		}
		else {												// ������ ���̰� �� Ŭ��� Ȥ�� �������� �̹� ���� ������ ���
			center_l--;										// �·� ��ĭ ����
			center_h = min(center_h, height[center_l]);
		}
		ret = max(ret, center_h*(center_r - center_l + 1));	// ��ĭ �����Ҷ����� ���� �ִ밪����
	}
	return ret;												// ����, ����, �߰���ġ�� �κ� ���� ���� ���� ��ȯ
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