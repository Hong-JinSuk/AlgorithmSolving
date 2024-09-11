#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

int N, M, sx, sy, sharkSize = 2;
int next_x[] = {-1, 0, 0, 1};
int next_y[] = {0, -1, 1, 0};
vector<vector<int> > MAP;

void input() {
    cin >> N;
    for (int x = 0; x < N; x++) {
        vector<int> temp;
        for (int y = 0; y < N; y++) {
            int num;
            cin >> num;
            temp.push_back(num);
            if (num == 9) {
                sx = x;
                sy = y;
                temp[y] = 0;
            }
        }
        MAP.push_back(temp);
    }
}

bool compare(pair<int, int> a, pair<int, int> b) {
    if(a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

vector<int> bfs(int x, int y, bool visit[20][20]) {
    queue<pair<int, int> > q;
    q.push({x, y});
    visit[x][y] = true;

    vector<int> answer;
    vector<pair<int, int> > tempAnswer;
    bool isEnd = false;
    int cnt = 0;

    while (!q.empty()) {
        int q_size = q.size();

        for (int i = 0; i < q_size; i++) {
            int cur_x = q.front().first, cur_y = q.front().second;
            q.pop();

            for (int j = 0; j < 4; j++) {
                int nx = cur_x + next_x[j], ny = cur_y + next_y[j];
                if (nx > -1 && ny > -1 && nx < N && ny < N && !visit[nx][ny]) {
                    if (MAP[nx][ny] > 0 && MAP[nx][ny] < sharkSize) {
                        isEnd = true;
                        tempAnswer.push_back({nx, ny});
                    } else if (MAP[nx][ny] == 0 || MAP[nx][ny] == sharkSize) {
                        visit[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }
        cnt++;
        if (isEnd) {
            sort(tempAnswer.begin(), tempAnswer.end(), compare);
            x = tempAnswer[0].first;
            y = tempAnswer[0].second;
            answer.push_back(x);
            answer.push_back(y);
            answer.push_back(cnt);
            MAP[x][y] = 0;
            return answer;
        }
    }
    return answer;
}

int sol() {
    int cnt = 0, x = sx, y = sy, need = 2;
    bool visit[20][20];

    while (1) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                visit[i][j] = false;
            }
        }
        vector<int> answer = bfs(x, y, visit);
        if (answer.empty()) break;

        cnt += answer[2]; // 횟수 더해줌
        x = answer[0];
        y = answer[1];
        need--;
        if (need == 0) {
            sharkSize++;
            need = sharkSize;
        }
    }
    return cnt;
}

int main() {
    input();
    cout << sol();
    return 0;
}
