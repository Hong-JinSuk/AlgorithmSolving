// 최대한 적은 강의실 이용
// 종료 시간과 시작 시간이 겹치는건 OK
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define endl "\n"

using namespace std;

int N;
priority_queue<pair<int, int>> q; // 끝나는 시간, 강의실 번호
vector<pair<int, pair<int,int>>> Class; // Start, end, num
vector<int> answer(100001); // 강의마다 배정된 강의실 번호
void input() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		int num, start, end;
		cin >> num >> start >> end;
		Class.push_back({ start,{end,num} });
	}
	sort(Class.begin(), Class.end()); // 강의 시작시간 기준으로 오름차순 정렬
}

// 강의시간이 빠른것부터 pq에 push => pq에 가장빨리 끝나는 강의시간부터 나와있음
// 그 다음 강의가 이어질수 pq의 top 다음에 들어갈 수 있다? 그럼 pop 해주고 push 해줌.

void sol() {

	int K = 1;

	for (int i = 0; i < Class.size(); i++) {
		int st = Class[i].first;
		int et = Class[i].second.first;
		int cn = Class[i].second.second;

		if (!q.empty()) {
			if (-q.top().first <= st) { // 가장 빨리 끝나는 강의 다음에 강의가 가능하다면
				//cout << -q.top().first << ", " << st << endl;
				q.push({ -et,q.top().second }); 
				answer[cn] = q.top().second;
				q.pop();
			}
			else { // 안된다면, 새로운 강의실 배정
				q.push({ -et, ++K });
				answer[cn] = K;
			}
		}
		else {
			q.push({ -et,1 }); // 맨 처음은 1번 강의실 배정
			answer[cn] = 1;
		}
	}
	cout << K << endl;
	for (int i = 1; i <= N; i++) {
		cout << answer[i] << endl;
	}
}

int main() {

	ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 이거 안해주면 시간초과
	input();
	sol();

	return 0;
}