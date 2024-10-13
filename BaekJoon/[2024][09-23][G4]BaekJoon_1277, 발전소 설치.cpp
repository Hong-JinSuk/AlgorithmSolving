#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#define INF 98754321

using namespace std;

int N, W;
double M;
vector<pair<int, int> > ps; // 발전소
vector<vector<pair<int, double> > > edge(1001); // 발전소, 거리
double visited[1001];

void make_edge(int x, int y, int num) {
    for (int i = 1; i <= ps.size(); i++) {
        int cx = ps[i - 1].first, cy = ps[i - 1].second;
        double dist = sqrt(pow(x - cx, 2) + pow(y - cy, 2));
        if (dist < M) {
            edge[num].push_back({i, dist});
            edge[i].push_back({num, dist});
        }
    }
}

void input() {
    cin >> N >> W >> M;

    for (int i = 1; i <= N; i++) {
        int x, y;
        cin >> x >> y;
        make_edge(x, y, i);
        ps.push_back({x, y});
    }

    for (int i = 0; i < W; i++) {
        int a, b;
        cin >> a >> b;
        edge[a].insert(edge[a].begin(), {b, 0.0});
        edge[b].insert(edge[b].begin(), {a, 0.0});
    }

    for (int i = 2; i <= N; i++) {
        visited[i] = INF;
    }
}

void sol() {
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int i = 0; i < edge[cur].size(); i++) {
            double dist = edge[cur][i].second;
            int next = edge[cur][i].first;

            if (visited[cur] + dist < visited[next]) {
                visited[next] = visited[cur] + dist;
                q.push(next);
            }
        }
    }

}

int main() {

    input();
    sol();
    cout << (int) (visited[N] * 1000);

    return 0;
}
