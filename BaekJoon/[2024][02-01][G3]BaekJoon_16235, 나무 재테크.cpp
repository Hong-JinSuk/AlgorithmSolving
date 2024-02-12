#include<iostream>
#include<queue>
#include<deque>

using namespace std;

struct Node
{
	int energy = 5;
	deque<int> q; // ĭ�� �ɾ��� ������
	int canBreed = 0; // ������ �� �ִ� ������ ��
};

int N, M, K;
Node MAP[11][11]; // ���� �� ����
int supply[11][11]; // �ܿ�ö ���� ����
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
		MAP[y][x].q.push_back(z); // ��ǥ�� � �������� ������� �԰� ����.
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
				if (isSummer) { // ������ ����� ������ ������ �״´�.
					MAP[y][x].energy += (tree / 2);
					continue;
				}
				if (tree <= MAP[y][x].energy) {
					MAP[y][x].energy -= tree; // ������ ���̸�ŭ ������� �Դ´�.
					tree += 1; // ������ ����+1
					if (tree % 5 == 0) MAP[y][x].canBreed++; // ���� �� �� �ִ� ������ ���� �� ����
					newTree.push_back(tree);
				}
				else { // �� �̻� ����� ���� �� �ִ� ������ ���ٸ� ������ �װ� ����� �ȴ�.
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
			for (int i = 0; i < 8; i++) { // �ֺ����� ����
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