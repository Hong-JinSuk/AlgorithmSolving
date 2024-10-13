#include <iostream>
#include <vector>
#define X 0246

using namespace std;

int N, M, K;

int next_y[] = {0, 1, 1, 1, 0, -1, -1, -1};
int next_x[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dir_even[] = {0, 2, 4, 6};
int dir_odd[] = {1, 3, 5, 7};

struct FIREBALL {
    int x;
    int y;
    int weight;
    int fast;
    int dir;
};

vector<FIREBALL> FireBalls;
vector<FIREBALL> Map[51][51];

void Init() {
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >> d;
        FireBalls.push_back({r, c, m, s, d});
    }
}

void ClearMap() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            Map[i][j].clear();
        }
    }
}

void Move() {
    ClearMap();

    for (int i = 0; i < FireBalls.size(); i++) {
        auto fireball = FireBalls[i];
        int nx = fireball.x + next_x[fireball.dir] * (fireball.fast % N);
        int ny = fireball.y + next_y[fireball.dir] * (fireball.fast % N);

        if (nx > N) nx -= N;
        if (nx < 1) nx += N;
        if (ny > N) ny -= N;
        if (ny < 1) ny += N;

        fireball.x = nx;
        fireball.y = ny;

        Map[nx][ny].push_back(fireball);
    }
}

void Div() {
    vector<FIREBALL> tempFireBall;

    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            if (Map[x][y].size() == 0) continue;
            if (Map[x][y].size() == 1) {
                tempFireBall.push_back(Map[x][y][0]);
                continue;
            }

            int weightSum = 0, fastSum = 0, cnt = Map[x][y].size();
            int dir = -1;

            for (int i = 0; i < Map[x][y].size(); i++) {
                weightSum += Map[x][y][i].weight;
                fastSum += Map[x][y][i].fast;
                if (dir == -1) dir = Map[x][y][i].dir % 2;
                else if (dir != Map[x][y][i].dir % 2) dir = X;
            }

            int weight = weightSum / 5;
            int fast = fastSum / cnt;

            if (weight == 0) continue;
            if (dir == X) {
                for (int i = 0; i < 4; i++) {
                    tempFireBall.push_back({x, y, weight, fast, dir_odd[i]});
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    tempFireBall.push_back({x, y, weight, fast, dir_even[i]});
                }
            }
        }
    }

    FireBalls = tempFireBall;
}

int Sol() {
    int answer = 0;

    Init();

    while (K > 0) {
        K--;
        Move();
        Div();
    }

    for (auto i: FireBalls) answer += i.weight;

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cout << Sol();

    return 0;
}
