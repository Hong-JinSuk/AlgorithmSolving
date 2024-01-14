#include<iostream>

using namespace std;

int n;
double E, W, S, N;
double answer = 0;
bool isvisit[30][30];
void input() {

	cin >> n >> E >> W >> S >> N;
	E /= 100.0; W /= 100.0; S /= 100.0; N /= 100.0;
	
}

// ���� ��ġ���� ���� ��ġ�� �̵��� �� ������ �� Ȯ���� ���ؼ� �̵�
// �̵��� �� ���ٸ� �� ������ Ȯ���� �������� �̵��ϴ� Ȯ���� ���ؼ� answer�� ������
// �̵��� �� ���� Ȯ�� = 1 - �ܼ� ��η� �̵��ϴ� Ȯ��
void gogo(double per, int x, int y, int cnt) {
	if (cnt == n) return; // �̵� Ƚ���� �ٵǸ� ��
	if (!isvisit[y - 1][x]) { 
		isvisit[y - 1][x] = true;
		gogo(per * N, x, y - 1, cnt + 1);
		isvisit[y - 1][x] = false;
	}
	else answer += (per * N);

	if (!isvisit[y + 1][x]) {
		isvisit[y + 1][x] = true;
		gogo(per * S, x, y + 1, cnt + 1);
		isvisit[y + 1][x] = false;
	}
	else answer += (per * S);

	if (!isvisit[y][x + 1]) {
		isvisit[y][x + 1] = true;
		gogo(per * E, x + 1, y, cnt + 1);
		isvisit[y][x + 1] = false;
	}
	else answer += (per * E);

	if (!isvisit[y][x - 1]) {
		isvisit[y][x - 1] = true;
		gogo(per * W, x - 1, y, cnt + 1);
		isvisit[y][x - 1] = false;
	}
	else answer += (per * W);
}

int main() {

	input();

	isvisit[15][15] = true; // �������� �׻� �湮����
	gogo(1.0, 15, 15, 0);

	cout.precision(16); // �̰� ���Ѵٰ� Ʋ���°� ��..
	cout << 1 - answer;
	return 0;
}