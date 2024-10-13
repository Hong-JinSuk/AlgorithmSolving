#include <iostream>
#include <vector>

using namespace std;

struct MAP {
    int water = 0;
    bool isRain = false;
};

int N, M;
MAP Map[51][51];
int next_x[] = {99, 0, -1, -1, -1, 0, 1, 1, 1};
int next_y[] = {99, -1, -1, 0, 1, 1, 1, 0, -1};

int water_x[] = {-1, -1, 1, 1};
int water_y[] = {-1, 1, 1, -1};

vector<pair<int, int> > dir;
vector<pair<int, int> > clouds; // x,y

void Init() {
    cin >> N >> M;

    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            cin >> Map[x][y].water;
        }
    }

    for (int i = 0; i < M; i++) {
        int d, s;
        cin >> d >> s;
        dir.push_back({d, s});
    }

    clouds.push_back({N, 1});
    clouds.push_back({N, 2});
    clouds.push_back({N - 1, 1});
    clouds.push_back({N - 1, 2});
}

void Move(int index) {
    vector<pair<int, int> > tempClouds;
    int d = dir[index - 1].first, s = dir[index - 1].second;
    for (pair<int, int> cloud: clouds) {
        int curx = cloud.first, cury = cloud.second;
        int nx = curx + next_x[d] * s, ny = cury + next_y[d] * s;

        nx %= N;
        ny %= N;

        if (nx < 1)nx += N;
        if (ny < 1)ny += N;

        tempClouds.push_back({nx, ny});
        Map[nx][ny].water++;
        Map[nx][ny].isRain = true;
    }


    for (pair<int, int> cloud: tempClouds) {
        int x = cloud.first, y = cloud.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + water_x[i], ny = y + water_y[i];
            if (nx > 0 && nx <= N && ny > 0 && ny <= N && Map[nx][ny].water > 0) {
                Map[x][y].water++;
            }
        }
    }
}

void Vivaragi() {
    clouds.clear();

    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            if (!Map[x][y].isRain && Map[x][y].water >= 2) {
                clouds.push_back({x, y});
                Map[x][y].water -= 2;
            }
        }
    }
}

void ClearMap() {
    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            Map[x][y].isRain = false;
        }
    }
}

void sol() {
    int answer = 0;

    Init();

    for (int i = 1; i <= M; i++) {
        ClearMap();
        Move(i);
        Vivaragi();
    }

    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            answer += Map[x][y].water;
        }
    }

    cout << answer;
}

int main() {
    sol();

    return 0;
}
