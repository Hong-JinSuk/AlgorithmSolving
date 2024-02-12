#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#define endl "\n"
using namespace std;

int N, M;
int MAP[8][8];
int answer = 0;
int next_x[] = { -1,1,0,0 };
int next_y[] = { 0,0,1,-1 };
vector<vector<int>> Batch;
queue<pair<int,int>> q;
void input() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> MAP[y][x];
			if (MAP[y][x] == 2) {
				q.push({ x,y });
			}
		}
	}
}
void reMap(int (&Map)[8][8]) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			Map[y][x] = MAP[y][x];
		}
	}
}
void Test() {
	int Map[8][8] = { 0 };
	queue<pair<int, int>> virus;
	// 모든 배치 탐색
	for (int i = 0; i < Batch.size(); i++) {
		reMap(Map); // 배치마다 리셋
		for (int j = 0; j < Batch[i].size(); j++) {
			// 어디에 있는 기둥인지 확인
			int Y = Batch[i][j] / M;
			Batch[i][j] %= M;
			int X = Batch[i][j];

			if (Map[Y][X] != 0) break; // 기둥을 세울 수 없는 배치면 PASS
			else Map[Y][X] = 1; // 기둥을 세움
			
			if (j == 2) {
				virus = q; // 매번 리셋
				while (!virus.empty()) {
					int x = virus.front().first, y = virus.front().second; virus.pop();
					for (int k = 0; k < 4; k++) {
						int nx = x + next_x[k], ny = y + next_y[k];
						if (nx > -1 && ny > -1 && nx < M && ny < N) { // 범위 안이고
							if (Map[ny][nx] == 0) { // 감염될 수 있는 칸이라면
								virus.push({ nx,ny });
								Map[ny][nx] = 2;
							}
						}
					}
				}
				int ans = 0;
				for (int y = 0; y < N; y++) {
					for (int x = 0; x < M; x++) {
						if (Map[y][x] == 0) ans++;
					}
				}
				answer = max(answer, ans);
			}
		}
	}
}

void batch() {
	vector<int> s;
	vector<int> temp{ 1,1,1 }; // 기둥 3개를 박아야함

	for (int i = 0; i < N * M; i++) {
		s.push_back(i);
		if (i >= 3) {
			temp.push_back(0);
		}
	}

	do { // 모든 칸에서 3개를 뽑는 모든 경우의 수
		vector<int> B;
		for (int i = 0; i < N * M; i++) {
			if (temp[i] == 1) {
				B.push_back(s[i]);
			}
		}
		Batch.push_back(B);
	} while (prev_permutation(temp.begin(), temp.end()));
}

int main() {
	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
	input();
	batch();
	Test();
	cout << answer;
	return 0;
}