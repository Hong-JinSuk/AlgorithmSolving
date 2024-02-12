#include<iostream>
#include<vector>
#define endl "\n"

using namespace std;

int N, M;
int answer;
vector<pair<int,int>> cctv;
void input(vector<vector<int>>& Map) {

	cin >> N >> M;
	answer = N * M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int state; cin >> state;
			Map[y][x] = state;
			if (1 <= Map[y][x] && Map[y][x] <= 5) {
				cctv.push_back({ x,y });
			}
		}
	}
	cctv.push_back({ -1,-1 });
}
void sol(int x, int y, int order, vector<vector<int>> Map);
void Up(int X, int Y, vector<vector<int>>& Map) {
	while (1) {
		if (Y - 1 < 0 || Map[Y - 1][X] == 6) break; // ������ ����ų� ���� ������ break
		if (Map[Y - 1][X] == 0) Map[Y - 1][X] = -1; // �� �� �ִ� �� ǥ��
		Y--;
	}
}
void Down(int X, int Y, vector<vector<int>>& Map) {
	while (1) {
		if (Y + 1 >= N || Map[Y + 1][X] == 6) break;
		if (Map[Y + 1][X] == 0) Map[Y + 1][X] = -1;
		Y++;
	}
}
void Left(int X, int Y, vector<vector<int>>& Map) {
	while (1) {
		if (X - 1 < 0 || Map[Y][X - 1] == 6) break;
		if (Map[Y][X - 1] == 0) Map[Y][X - 1] = -1;
		X--;
	}
}
void Right(int X, int Y, vector<vector<int>>& Map) {
	while (1) {
		if (X + 1 > M || Map[Y][X + 1] == 6) break;
		if (Map[Y][X + 1] == 0) Map[Y][X + 1] = -1;
		X++;
	}
}
void Type1(int X, int Y, int dir, int order, vector<vector<int>> Map) {
	order++;
	int nx = cctv[order].first, ny = cctv[order].second;
	if (dir == 0) { // ��
		Up(X, Y, Map);
		sol(nx, ny, order, Map); // ���� cctv �˻��Ϸ�
	}
	if (dir == 1) { // �Ʒ�
		Down(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 2) { // ����
		Left(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 3) { // ������
		Right(X, Y, Map);
		sol(nx, ny, order, Map);
	}
}
void Type2(int X, int Y, int dir, int order, vector<vector<int>> Map) {
	order++;
	int nx = cctv[order].first, ny = cctv[order].second;
	int x = X, y = Y;
	if (dir == 0) { // �� �Ʒ�
		Up(X, Y, Map);
		Down(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 1) { // ���� ������
		Left(X, Y, Map);
		Right(X, Y, Map);
		sol(nx, ny, order, Map);
	}
}
void Type3(int X, int Y, int dir, int order, vector<vector<int>> Map) {
	order++;
	int nx = cctv[order].first, ny = cctv[order].second;
	int x = X, y = Y;
	if (dir == 0) { // �� ������
		Up(X, Y, Map);
		Right(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 1) { // �� ����
		Up(X, Y, Map);
		Left(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 2) { // �Ʒ� ������
		Down(X, Y, Map);
		Right(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 3) { // �Ʒ� ����
		Down(X, Y, Map);
		Left(X, Y, Map);
		sol(nx, ny, order, Map);
	}
}
void Type4(int X, int Y, int dir, int order, vector<vector<int>> Map) {
	order++;
	int nx = cctv[order].first, ny = cctv[order].second;
	int x = X, y = Y;
	if (dir == 0) { // �Ʒ� ����
		Up(X, Y, Map);
		Left(X, Y, Map);
		Right(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 1) { // ������ ����
		Left(X, Y, Map);
		Up(X, Y, Map);
		Down(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 2) { // �� ����
		Down(X, Y, Map);
		Right(X, Y, Map);
		Left(X, Y, Map);
		sol(nx, ny, order, Map);
	}
	if (dir == 3) { // ���� ����
		Right(X, Y, Map);
		Up(X, Y, Map);
		Down(X, Y, Map);
		sol(nx, ny, order, Map);
	}
}
void Type5(int X, int Y, int order, vector<vector<int>> Map) {
	order++;
	int x = X, y = Y;
	int nx = cctv[order].first, ny = cctv[order].second;
	Up(X, Y, Map);
	Down(X, Y, Map);
	Left(X, Y, Map);
	Right(X, Y, Map);
	sol(nx, ny, order, Map);
}
void sol(int x, int y, int order, vector<vector<int>> Map) { // cctv type, cctv order
	if (order >= cctv.size() - 1) {
		int Ans = 0;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				if (Map[y][x] == 0)  Ans++;
			}
		}
		answer = min(Ans, answer);
		return;
	}
	int type = Map[cctv[order].second][cctv[order].first];

	if (type == 1) {
		for (int dir = 0; dir < 4; dir++) {
			Type1(x, y, dir, order, Map);
		}
	}
	if (type == 2) {
		for (int dir = 0; dir < 2; dir++) {
			Type2(x, y, dir, order, Map);
		}
	}
	if (type == 3) {
		for (int dir = 0; dir < 4; dir++) {
			Type3(x, y, dir, order, Map);
		}
	}
	if (type == 4) {
		for (int dir = 0; dir < 4; dir++) {
			Type4(x, y, dir, order, Map);
		}
	}
	if (type == 5) {
		Type5(x, y, order, Map);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
	vector<vector<int>> Map(10, vector<int>(10, 6));
	input(Map);
	sol(cctv[0].first, cctv[0].second, 0, Map);
	cout << answer;
	return 0;
}