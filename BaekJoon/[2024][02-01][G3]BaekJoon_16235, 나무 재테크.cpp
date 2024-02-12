#include<iostream>
#include<queue>
#include<deque>

using namespace std;

struct Node
{
	int energy = 5;
	deque<int> q; // 칸에 심어진 나무들
	int canBreed = 0; // 번식할 수 있는 나무들 수
};

int N, M, K;
Node MAP[11][11]; // 상도의 땅 정보
int supply[11][11]; // 겨울철 영양 공급
int Next[8][2] = { {-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0} };
void init() {
	cin >> N >> M >> K;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> supply[y][x];
		}
	}
	for (int i = 0; i < M; i++) {
		int y, x, z;
		cin >> y >> x >> z;
		MAP[y][x].q.push_back(z); // 좌표에 어린 나무부터 영양분을 먹게 심음.
	}
}
void spring() {
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			deque<int> newTree;
			bool isSummer = false;
			while (!MAP[y][x].q.empty()) {
				int tree = MAP[y][x].q.front();
				MAP[y][x].q.pop_front();
				if (isSummer) { // 여름엔 양분을 못먹은 나무가 죽는다.
					MAP[y][x].energy += (tree / 2);
					continue;
				}
				if (tree <= MAP[y][x].energy) {
					MAP[y][x].energy -= tree; // 나무의 나이만큼 영양분을 먹는다.
					tree += 1; // 나무는 나이+1
					if (tree % 5 == 0) MAP[y][x].canBreed++; // 번식 할 수 있는 나무는 따로 또 저장
					newTree.push_back(tree);
				}
				else { // 더 이상 양분을 먹을 수 있는 나무가 없다면 여름에 죽고 양분이 된다.
					isSummer = true;
					MAP[y][x].energy += (tree / 2);
				}
			}
			MAP[y][x].q = newTree;
		}
	}
}
void autumn() {
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			for (int i = 0; i < 8; i++) { // 주변으로 번식
				int nx = x + Next[i][0];
				int ny = y + Next[i][1];
				if (nx > 0 && ny > 0 && nx <= N && ny <= N) {
					for (int i = 0; i < MAP[y][x].canBreed; i++) {
						MAP[ny][nx].q.push_front(1);
					}
				}
			}
			MAP[y][x].canBreed = 0;
		}
	}
}
void winter() {
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			MAP[y][x].energy += supply[y][x];
		}
	}
}
void sol() {
	while (K--) {
		spring();
		autumn();
		winter();
	}
	int livingTree = 0;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			livingTree += MAP[y][x].q.size();
		}
	}
	cout << livingTree;
}
int main() {
	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
	init();
	sol();
	return 0;
}