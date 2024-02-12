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
				if (MAP[y][x] != 0) continue; // �̹� ������ �ڼ��� �н�
				int NearF = 0, NearS = 0; // ������ ģ��ģ�� & ������ ���¼�
				for (int i = 0; i < 4; i++) {
					int nx = x + near_x[i], ny = y + near_y[i];
					if (nx > 0 && nx <= N && ny > 0 && ny <= N) { // ������ ���� ��
						if (MAP[ny][nx] == 0) NearS++;
						// ģ�� ģ���� ������ ĭ�� �ִٸ�
						else if (find(ML[student].begin(), ML[student].end(), MAP[ny][nx]) != ML[student].end()) {
							NearF++;
						}
					}
				}
				// ģ�� ģ��, �� ����, ��, �� ������ ����
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
					// ģ�� ģ���� ������ ĭ�� �ִٸ�
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