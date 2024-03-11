#include<iostream>
#include<stack>
#include<queue>
using namespace std;

int N;
stack<int> s;
priority_queue<pair<int,int>> q; // height, num
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int Height; cin >> Height;
		s.push(Height);
	}
}
	
void sol() {

	int* answer = new int[N + 1];
	for (int i = 0; i <= N; i++) answer[i] = 0;

	while (!s.empty()) {
		int curHeight = s.top(); // ����
		int curNum = s.size(); // ��ȣ
		s.pop();

		while (!q.empty()) {
			int MIN = - q.top().first; // ������ ������ �ּ� ����
			int num = q.top().second; // �ּ� ������ ������ ��ȣ
			if (curHeight >= MIN) {  // �������� ���� ���� �������� ���� ũ�ٸ� ���Ű���
				answer[num] = curNum;
				q.pop();
			}
			else { // �� �̻� �ڽź��� ���� ������ �����ʿ� ���ٸ�
				break;
			}
		}
		q.push({-curHeight,curNum});
	}

	for (int i = 1; i <= N; i++)
		cout << answer[i] << " ";

}

int main() {

	input();
	sol();

	return 0;
}