#include<iostream>
#define endl "\n"

using namespace std;

int N, L;
int MAP[101][101];
void init() {
	cin >> N >> L;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> MAP[y][x];
		}
	}
}

bool searchRow(int x, int y, int Stack) {
	if (x == N) {
		return true;
	}
	else {
		int diff = MAP[y][x + 1] - MAP[y][x];
		if (abs(diff) > 1) return false;
		else if (diff == 0) {
			return searchRow(x + 1, y, Stack + 1);
		}
		else if (diff > 0) { // �ö󰡴� ��
			if (Stack >= L) {
				return searchRow(x + 1, y, 1);
			}
			else return false;
		}
		else if (diff < 0) { // �������� ��
			if (x + L > N) return false; // ������ ���� ĭ ��ü�� ���ٸ�
			for (int i = 1; i <= L; i++) {
				if (MAP[y][x + i] != MAP[y][x] - 1) return false;
			}
			return searchRow(x + L, y, 0);
		}
	}
}

bool searchCol(int x, int y, int Stack) {
	if (y == N) {
		return true;
	}
	else {
		int diff = MAP[y + 1][x] - MAP[y][x];
		if (abs(diff) > 1) return false;
		else if (diff == 0) {
			return searchCol(x, y + 1, Stack + 1);
		}
		else if (diff > 0) { // �ö󰡴� ��
			if (Stack >= L) {
				return searchCol(x, y + 1, 1);
			}
			else return false;
		}
		else if (diff < 0) { // �������� ��
			if (y + L > N) return false; // ������ ���� ĭ ��ü�� ���ٸ�
			for (int i = 1; i <= L; i++) {
				if (MAP[y + i][x] != MAP[y][x] - 1) return false;
			}
			return searchCol(x, y + L, 0);
		}
	}
}

// case : �����̵�, �Ʒ����̵�, �����̵�
// ���� �̵��� ������ ���� ��ġ�ؾ߉�.
// ���� �̵��� ���� ĭ�� ���ø� �׾��ָ� ��.
// �Ʒ��� �̵��� ������ ������ � ���Ҵ��� �Ǵ��ؾ߉�.
void sol() {
	int answer = 0;
	for (int y = 1; y <= N; y++) {
		if (searchRow(1, y, 1)) answer++;
	}
	for (int x = 1; x <= N; x++) {
		if (searchCol(x, 1, 1)) answer++;
	}
	cout << answer;
}

int main() {
	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);

	init();
	sol();

	return 0;
}