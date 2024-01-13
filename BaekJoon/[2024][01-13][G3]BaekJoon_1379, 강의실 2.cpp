// �ִ��� ���� ���ǽ� �̿�
// ���� �ð��� ���� �ð��� ��ġ�°� OK
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define endl "\n"

using namespace std;

int N;
priority_queue<pair<int, int>> q; // ������ �ð�, ���ǽ� ��ȣ
vector<pair<int, pair<int,int>>> Class; // Start, end, num
vector<int> answer(100001); // ���Ǹ��� ������ ���ǽ� ��ȣ
void input() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		int num, start, end;
		cin >> num >> start >> end;
		Class.push_back({ start,{end,num} });
	}
	sort(Class.begin(), Class.end()); // ���� ���۽ð� �������� �������� ����
}

// ���ǽð��� �����ͺ��� pq�� push => pq�� ���廡�� ������ ���ǽð����� ��������
// �� ���� ���ǰ� �̾����� pq�� top ������ �� �� �ִ�? �׷� pop ���ְ� push ����.

void sol() {

	int K = 1;

	for (int i = 0; i < Class.size(); i++) {
		int st = Class[i].first;
		int et = Class[i].second.first;
		int cn = Class[i].second.second;

		if (!q.empty()) {
			if (-q.top().first <= st) { // ���� ���� ������ ���� ������ ���ǰ� �����ϴٸ�
				//cout << -q.top().first << ", " << st << endl;
				q.push({ -et,q.top().second }); 
				answer[cn] = q.top().second;
				q.pop();
			}
			else { // �ȵȴٸ�, ���ο� ���ǽ� ����
				q.push({ -et, ++K });
				answer[cn] = K;
			}
		}
		else {
			q.push({ -et,1 }); // �� ó���� 1�� ���ǽ� ����
			answer[cn] = 1;
		}
	}
	cout << K << endl;
	for (int i = 1; i <= N; i++) {
		cout << answer[i] << endl;
	}
}

int main() {

	ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0); // �̰� �����ָ� �ð��ʰ�
	input();
	sol();

	return 0;
}