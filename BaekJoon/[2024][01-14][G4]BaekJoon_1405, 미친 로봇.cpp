#include<iostream>

using namespace std;

int n;
double E, W, S, N;
double answer = 0;
bool isvisit[30][30];
void input() {

	cin >> n >> E >> W >> S >> N;
	E /= 100.0; W /= 100.0; S /= 100.0; N /= 100.0;
	
}

// 현재 위치에서 다음 위치로 이동할 수 있으면 그 확률을 곱해서 이동
// 이동할 수 없다면 그 상태의 확률에 다음으로 이동하는 확률을 곱해서 answer에 더해줌
// 이동할 수 없는 확률 = 1 - 단순 경로로 이동하는 확률
void gogo(double per, int x, int y, int cnt) {
	if (cnt == n) return; // 이동 횟수가 다되면 끝
	if (!isvisit[y - 1][x]) { 
		isvisit[y - 1][x] = true;
		gogo(per * N, x, y - 1, cnt + 1);
		isvisit[y - 1][x] = false;
	}
	else answer += (per * N);

	if (!isvisit[y + 1][x]) {
		isvisit[y + 1][x] = true;
		gogo(per * S, x, y + 1, cnt + 1);
		isvisit[y + 1][x] = false;
	}
	else answer += (per * S);

	if (!isvisit[y][x + 1]) {
		isvisit[y][x + 1] = true;
		gogo(per * E, x + 1, y, cnt + 1);
		isvisit[y][x + 1] = false;
	}
	else answer += (per * E);

	if (!isvisit[y][x - 1]) {
		isvisit[y][x - 1] = true;
		gogo(per * W, x - 1, y, cnt + 1);
		isvisit[y][x - 1] = false;
	}
	else answer += (per * W);
}

int main() {

	input();

	isvisit[15][15] = true; // 시작점은 항상 방문상태
	gogo(1.0, 15, 15, 0);

	cout.precision(16); // 이거 안한다고 틀리는건 좀..
	cout << 1 - answer;
	return 0;
}