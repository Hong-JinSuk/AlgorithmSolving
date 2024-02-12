#include<iostream>
#include<vector>
#define endl "\n"
using namespace std;

int N, M, sx, sy, K;

vector<int> Move;
int MAP[20][20];
vector<int>cube(7); // 1,2,3,4,5,6 위치

void check() {
	if (MAP[sy][sx] == 0) MAP[sy][sx] = cube[6];
	else {
		cube[6] = MAP[sy][sx];
		MAP[sy][sx] = 0;
	}
	cout << cube[1] << endl;
}
void moveE() {
	if (sx >= M - 1) return;
	sx++;
	cube = {0, cube[4],cube[2],cube[1],cube[6],cube[5],cube[3] };
	check();
}
void moveW() {
	if (sx <= 0) return;
	sx--;
	cube = {0, cube[3] ,cube[2] ,cube[6] ,cube[1] ,cube[5] ,cube[4] };
	check();
}
void moveN() {
	if (sy <= 0) return;
	sy--;
	cube = {0, cube[5] ,cube[1] ,cube[3] ,cube[4] ,cube[6] ,cube[2] };
	check();
}
void moveS() {
	if (sy >= N - 1) return;
	sy++;
	cube = {0, cube[2] ,cube[6] ,cube[3] ,cube[4] ,cube[1] ,cube[5] };
	check();
}
void input() {
	cin >> N >> M >> sy >> sx >> K; // 아니이거 x,y 받아온 다음에 하는거 아니였어..? ㅋㅋㅋㅋㅋ
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> MAP[y][x];
		}
	}
	for (int i = 0; i < K; i++) {
		int com; cin >> com;
		Move.push_back(com);
	}
}
void sol() {
	for (int dir : Move) {
		if (dir == 1) {
			moveE();
		}
		else if (dir == 2) {
			moveW();
		}
		else if (dir == 3) {
			moveN();
		}
		else if (dir == 4) {
			moveS();
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
	input();
	sol();
	return 0;
}