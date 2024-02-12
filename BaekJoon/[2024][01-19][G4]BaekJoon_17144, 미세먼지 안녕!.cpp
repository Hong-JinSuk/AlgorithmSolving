#include<iostream>
#include<vector>
#define endl "\n"
using namespace std;

int R, C, T;

int next_x[] = { -1,1,0,0 };
int next_y[] = { 0,0,1,-1 };

int MAP[51][51];
int S_MAP[51][51];
int d_start;

void input() {
	cin >> R >> C >> T;
	for (int y = 1; y <= R; y++) {
		for (int x = 1; x <= C; x++) {
			cin >> MAP[y][x];
			if (MAP[y][x] == -1) d_start = y;
		}
	}
}

void Spread(int y, int x) {
	int cnt = 0;
	int sp = MAP[y][x] / 5; // 퍼질 양
	for (int i = 0; i < 4; i++) {
		int nx = x + next_x[i];
		int ny = y + next_y[i];
		if (ny > 0 && ny <= R && nx > 0 && nx <= C) { // 범위 안에 있고
			if (MAP[ny][nx] != -1) { // 공기 청정기가 아니면
				S_MAP[ny][nx] += sp;
				cnt++; // 퍼진 수
			}
		}
	}
	MAP[y][x] -= (sp * cnt); // 퍼진 양 * 퍼진 칸
}

void u_Wind(int x, int y) {

	for (int Y = d_start - 2; Y > 1; Y--)
		MAP[Y][1] = MAP[Y - 1][1];
	for (int X = 1; X < C; X++)
		MAP[1][X] = MAP[1][X + 1];
	for (int Y = 1; Y < d_start - 1; Y++)
		MAP[Y][C] = MAP[Y + 1][C];
	for (int X = C; X > 2; X--)
		MAP[d_start - 1][X] = MAP[d_start - 1][X - 1];

	MAP[d_start - 1][2] = 0;
}

void d_Wind(int x, int y) {
	
	for (int Y = d_start + 1; Y < R; Y++)
		MAP[Y][1] = MAP[Y + 1][1];
	for (int X = 1; X < C; X++)
		MAP[R][X] = MAP[R][X + 1];
	for (int Y = R; Y > d_start; Y--)
		MAP[Y][C] = MAP[Y - 1][C];
	for (int X = C; X > 2; X--)
		MAP[d_start][X] = MAP[d_start][X - 1];

	MAP[d_start][2] = 0;
}

void sol() {
	while (T--) { // T초 반복

		// 모든 칸에서 확산
		for (int y = 1; y <= R; y++) {
			for (int x = 1; x <= C; x++) {
				if (MAP[y][x] == 0 || MAP[y][x] == -1) continue;
				Spread(y, x);
			}
		}

		for (int y = 1; y <= R; y++) {
			for (int x = 1; x <= C; x++) {
				MAP[y][x] += S_MAP[y][x];
				S_MAP[y][x] = 0;
			}
		}

		// 공기 청정기 위,아래
		u_Wind(0, d_start - 1);
		d_Wind(0, d_start);
	}

	int answer = 0;
	for (int y = 1; y <= R; y++) {
		for (int x = 1; x <= C; x++) {
			answer += MAP[y][x];
		}
	}
	cout << answer + 2;
}
int main() {
	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
	input();
	sol();
	return 0;
}