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
		int curHeight = s.top(); // 높이
		int curNum = s.size(); // 번호
		s.pop();

		while (!q.empty()) {
			int MIN = - q.top().first; // 오른쪽 빌딩의 최소 높이
			int num = q.top().second; // 최소 높이의 빌딩의 번호
			if (curHeight >= MIN) {  // 오른쪽의 가장 작은 빌딩보다 내가 크다면 수신가능
				answer[num] = curNum;
				q.pop();
			}
			else { // 더 이상 자신보다 작은 빌딩이 오른쪽에 없다면
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