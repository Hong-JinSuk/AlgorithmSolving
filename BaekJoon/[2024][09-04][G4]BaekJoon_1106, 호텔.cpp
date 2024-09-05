#include <algorithm>
#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;

int C, N;  // 늘려야 하는 수, 도시의 갯수
int cost[1101];
vector<pair<int, int>> vec;

void input() {
    cin >> C >> N;

    for (int i = 1; i <= 1100; i++) {
        cost[i] = INF;
    }

    for (int i = 0; i < N; i++) {
        int cost, customer;
        cin >> cost >> customer;
        vec.push_back({customer, cost});
    }
    sort(vec.begin(), vec.end());
}

void sol() {
    for (int i = 1; i <= 1100; i++) {
        for (auto v : vec) {
            int customer = v.first;
            int cost_ = v.second;
            if (i - customer > -1 && cost[i - customer] + cost_ < cost[i]) {
                cost[i] = cost[i - customer] + cost_;
            }
        }
    }
}

int main() {
    input();
    sol();

    int answer = INF;
    for (int i = C; i <= 1100; i++) {
        answer = min(cost[i], answer);
    }

    cout << answer;

    return 0;
}