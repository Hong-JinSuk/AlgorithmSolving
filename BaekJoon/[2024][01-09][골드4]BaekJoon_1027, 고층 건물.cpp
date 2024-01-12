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
	for (int M = 0; M < N; M++) { // 살펴볼 건물
		float Left = 100000000000.0;
		float Right = -10000000000.0;
		for (float L = M - 1; L >= 0; L--) { // 이 건물이 왼쪽으로 볼 수 있는 빌딩
			float L_in = (building[M] - building[L]) / (M - L);
			if (L_in < Left) { // 기울기가 더 낮아야 볼 수 있음
				Left = L_in;
				cnt[M]++;
			}
		}
		for (float R = M + 1; R < N; R++) { // 이 건물이 왼쪽으로 볼 수 있는 빌딩
			float R_in = (building[R] - building[M]) / (R - M);
			if (R_in > Right) { // 기울기가 더 높아야 볼 수 있음
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