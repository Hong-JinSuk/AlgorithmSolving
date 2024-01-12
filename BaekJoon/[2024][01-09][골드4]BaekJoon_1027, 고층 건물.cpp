#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int N;
int cnt[50];
int answer = 0;
vector<int> building;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int Height; cin >> Height;
		building.push_back(Height);
	}
}

void cul_incline() {
	for (int M = 0; M < N; M++) { // ���캼 �ǹ�
		float Left = 100000000000.0;
		float Right = -10000000000.0;
		for (float L = M - 1; L >= 0; L--) { // �� �ǹ��� �������� �� �� �ִ� ����
			float L_in = (building[M] - building[L]) / (M - L);
			if (L_in < Left) { // ���Ⱑ �� ���ƾ� �� �� ����
				Left = L_in;
				cnt[M]++;
			}
		}
		for (float R = M + 1; R < N; R++) { // �� �ǹ��� �������� �� �� �ִ� ����
			float R_in = (building[R] - building[M]) / (R - M);
			if (R_in > Right) { // ���Ⱑ �� ���ƾ� �� �� ����
				Right = R_in;
				cnt[M]++;
			}
		}
	}
}

int main() {

	input();
	cul_incline();
	int answer = 0;
	for (int i = 0; i < N; i++) {
		answer = max(answer, cnt[i]);
	}
	cout << answer;
	return 0;
}