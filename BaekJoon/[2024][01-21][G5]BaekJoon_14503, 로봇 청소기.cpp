#include<iostream>

using namespace std;

int N, M, r, c, d;
int dir[] = { 0,3,2,1 };
int next_x[] = { 0,1,0,-1 };
int next_y[] = { -1,0,1,0 };

struct Map
{
	bool isClean = false;
	int Wall;
};

Map MAP[50][50];

void input() {
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> MAP[y][x].Wall;
			if (MAP[y][x].Wall == 1) MAP[y][x].isClean = true;
		}
	}
}

void sol() {

	int sy = r, sx = c;
	int answer = 0;

	while (1) {

		if (!MAP[sy][sx].isClean) {
			MAP[sy][sx].isClean = true;
			answer++;
		}

		bool go = false;

		for (int i = 0; i < 4; i++) { // �� �ð����
			d = (d + 3) % 4; // �ݽð� �������� 90�� ȸ��
			int nx = sx + next_x[d], ny = sy + next_y[d];
			if (nx > -1 && ny > -1 && ny < N && nx < M) {
				if (!MAP[ny][nx].isClean) { // ���� �ƴϰ� û�ҵ� �ȵ������� �̵�
					sy += next_y[d], sx += next_x[d];
					go = true;
					break;
				}
			}
		}

		if (!go) { // �̵����� ���ߴٸ�
			// 2-Case
			int nx = sx + next_x[(d+2)%4], ny = sy + next_y[(d+2)%4];

			if (nx < 0 || nx >= M || ny < 0 || ny >= N || MAP[ny][nx].Wall == 1) {
				cout << answer;
				break;
			}
			else {
				sy = ny;
				sx = nx;
			}
		}
	}
}

int main() {

	input();
	sol();
	
	return 0;
}