#include<iostream>

using namespace std;

int N, answer = 0;
int Map[500][500];
int next_x[][10] = {
    {0, -1, 1, -2, -1, 1, 2, -1, 1, 0}, {2, 1, 1, 0, 0, 0, 0, -1, -1, 1}, {0, -1, 1, -2, -1, 1, 2, -1, 1, 0},
    {-2, -1, -1, 0, 0, 0, 0, 1, 1, -1}
};
int next_y[][10] = {
    {-2, -1, -1, 0, 0, 0, 0, 1, 1, -1}, {0, -1, 1, -2, -1, 1, 2, -1, 1, 0}, {2, 1, 1, 0, 0, 0, 0, -1, -1, 1},
    {0, -1, 1, -2, -1, 1, 2, -1, 1, 0}
};
int percent[] = {5, 10, 10, 2, 7, 7, 2, 1, 1};

void Init() {
    cin >> N;
    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            cin >> Map[x][y];
        }
    }
}

bool isIn(int x, int y) {
    if (x > 0 && x <= N && y > 0 && y <= N) return true;
    return false;
}

void SpreadSand(int dir, int x, int y) {
    int sand = Map[x][y];
    int sandTemp = Map[x][y];
    int spreadSand;
    for (int i = 0; i < 9; i++) {
        spreadSand = sandTemp * percent[i] / 100;
        int nx = x + next_x[dir][i], ny = y + next_y[dir][i];
        if (isIn(nx, ny)) Map[nx][ny] += spreadSand;
        else answer += spreadSand;
        sand -= spreadSand;
    }
    int nx = x + next_x[dir][9], ny = y + next_y[dir][9];
    if(isIn(nx,ny)) Map[nx][ny] += sand;
    else answer += sand;
    Map[x][y] = 0;
}

void Move(int dir, int x, int y, int turnCnt, int dirCnt, int dirNum) {
    if (y == 0 || x == 0) {
        return;
    }

    if (dir == 0) y--;
    else if (dir == 1) x++;
    else if (dir == 2) y++;
    else if (dir == 3) x--;

    SpreadSand(dir, x, y);

    dirCnt--;
    if (dirCnt == 0) {
        turnCnt--;
        dirCnt = dirNum;
        dir++;
    }

    if (turnCnt == 0) {
        turnCnt = 2;
        dirCnt = ++dirNum;
    }
    dir %= 4;
    Move(dir, x, y, turnCnt, dirCnt, dirNum);
}

int main() {
    Init();
    Move(0, (N + 1) / 2, (N + 1) / 2, 2, 1, 1);
    cout << answer + Map[1][0]<< endl;
    return 0;
}
