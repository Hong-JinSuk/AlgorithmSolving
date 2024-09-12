#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define INF 987654321

using namespace std;

int N, M;
struct NODE {
    int status = INF;
    int origin = 0;
};

NODE MAP[50][50];

int next_x[] = {-1, 1, 0, 0};
int next_y[] = {0, 0, 1, -1};
vector<pair<int, int> > starting;
vector<vector<pair<int, int> > > answer;

void input() {
    cin >> N >> M;
    int num;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> num;
            if (num == 0) {
                MAP[y][x].status = INF;
            } else if (num == 2) {
                MAP[y][x].origin = 2;
                MAP[y][x].status = INF;
                starting.push_back({x, y});
            } else if (num == 1) {
                MAP[y][x].origin = 1;
                MAP[y][x].status = -1;
            }
        }
    }
}

void combination(int depth, int next, vector<pair<int, int> > tempAnswer) {
    if (depth == M) {
        answer.push_back(tempAnswer);
        return;
    }

    for (int i = next; i < starting.size(); i++) {
        tempAnswer.push_back({starting[i].first, starting[i].second});
        combination(depth + 1, i + 1, tempAnswer);
        tempAnswer.pop_back();
    }
}

int bfs(vector<pair<int, int>> test) {

    queue<pair<int, int> > q;
    for (pair<int, int> i: test) {
        q.push({i.first, i.second});
        MAP[i.second][i.first].status = 0;
    }

    while (!q.empty()) {
        int q_size = q.size();
        for (int i = 0; i < q_size; i++) {
            int cx = q.front().first, cy = q.front().second;
            q.pop();

            for (int j = 0; j < 4; j++) {
                int nx = cx + next_x[j], ny = cy + next_y[j];
                if (nx > -1 && ny > -1 && nx < N && ny < N && MAP[ny][nx].status != -1) {
                    if (MAP[ny][nx].status > MAP[cy][cx].status + 1) {
                        q.push({nx, ny});
                        MAP[ny][nx].status = MAP[cy][cx].status + 1;
                    }
                    if (MAP[ny][nx].status == -2) {
                        q.push({nx,ny});
                    }
                }
            }
        }
    }

    int answer = 0;
    for(int y=0; y<N; y++) {
        for(int x=0; x<N; x++) {
            if(MAP[y][x].origin == 2) continue;
            if(MAP[y][x].status == INF) return INF;
            answer=max(answer,MAP[y][x].status);
        }
    }

    return answer;
}

int main() {

    input();
    vector<pair<int, int> > tempAnswer;
    combination(0, 0, tempAnswer);

    int ans = INF;
    for (auto test : answer) {
        for(int y=0; y<N; y++) {
            for(int x=0; x<N; x++) {
                if(MAP[y][x].origin != 1) MAP[y][x].status=INF;
            }
        }
        ans = min(ans,bfs(test));
    }

    if(ans == INF) cout<<-1;
    else cout <<ans;

    return 0;
}
