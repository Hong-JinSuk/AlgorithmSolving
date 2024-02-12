#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>

using namespace std;

int N;
int MAP[21][21];
int near_x[] = { -1,1,0,0 };
int near_y[] = { 0,0,1,-1 };
queue<int> q;
vector<int> ML[401]; // MyLike

void input() {
	cin >> N;
	for (int i = 0; i < N * N; i++) {
		int student;
		cin >> student;
		q.push(student);
		for (int j = 0; j < 4; j++) {
			int Like;
			cin >> Like;
			ML[student].push_back(Like);
		}
	}
}

void sol() {
	long long answer = 0;
	while (!q.empty()) {
		int student = q.front(); q.pop();
		priority_queue<pair<int, pair<int, pair<int, int>>>> pq;
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				if (MAP[y][x] != 0) continue; // 이미 배정된 자석은 패스
				int NearF = 0, NearS = 0; // 인접한 친한친구 & 인접한 빈좌석
				for (int i = 0; i < 4; i++) {
					int nx = x + near_x[i], ny = y + near_y[i];
					if (nx > 0 && nx <= N && ny > 0 && ny <= N) { // 인접한 범위 안
						if (MAP[ny][nx] == 0) NearS++;
						// 친한 친구가 인접한 칸에 있다면
						else if (find(ML[student].begin(), ML[student].end(), MAP[ny][nx]) != ML[student].end()) {
							NearF++;
						}
					}
				}
				// 친한 친구, 빈 공간, 행, 열 순으로 정렬
				pq.push({ NearF,{NearS,{-y,-x}} });
			}
		}
		int Y = -pq.top().second.second.first;
		int X = -pq.top().second.second.second;
		MAP[Y][X] = student;
	}

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			int student = MAP[y][x];
			int NearF = 0;
			for (int i = 0; i < 4; i++) {
				int nx = x + near_x[i], ny = y + near_y[i];
				if (nx > 0 && nx <= N && ny > 0 && ny <= N) {
					// 친한 친구가 인접한 칸에 있다면
					if (find(ML[student].begin(), ML[student].end(), MAP[ny][nx]) != ML[student].end()) {
						NearF++;
					}
				}
			}
			answer += pow(10, NearF - 1);
		}
	}

	cout << answer;
}

int main() {

	input();
	sol();
	return 0;
}