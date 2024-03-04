// bfs 코드 중간 출력 주석을 풀면 진행 경로를 알 수 있습니다.
#include <iostream>
#include <queue>
#define endl "\n"
using namespace std;

int N, M, Y, X, K;
int sx, sy, ex, ey;
int next_x[] = {1, -1, 0, 0};
int next_y[] = {0, 0, 1, -1};
bool visit[501][501];
bool prohibitArea[501][501];

void init()
{
    cin >> N >> M >> Y >> X >> K;
    for (int i = 0; i < K; i++)
    {
        int prohibit_y, prohibit_x;
        cin >> prohibit_y >> prohibit_x;
        prohibitArea[prohibit_y][prohibit_x] = true; // 금지구역 설정
    }
    cin >> sy >> sx >> ey >> ex;
}

bool move(int nx, int ny, int dir)
{
    switch (dir)
    {
    case 0: // 동쪽 모서리 검사
        for (int i = ny; i < ny + Y; i++)
        {
            if (prohibitArea[i][nx + X - 1])
                return false;
        }
        return true;
        break;
    case 1: // 서쪽 모서리 검사
        for (int i = ny; i < ny + Y; i++)
        {
            if (prohibitArea[i][nx])
                return false;
        }
        return true;
        break;
    case 2: // 남쪽 모서리 검사
        for (int i = nx; i < nx + X; i++)
        {
            if (prohibitArea[ny + Y - 1][i])
                return false;
        }
        return true;
        break;
    case 3: // 북쪽 모서리 검사
        for (int i = nx; i < nx + X; i++)
        {
            if (prohibitArea[ny][i])
                return false;
        }
        return true;
        break;
    default:
        return false;
        break;
    }
}

int bfs(int x, int y)
{

    queue<pair<int, int>> q; // x,y
    q.push({x, y});
    visit[y][x] = true;

    int answer = 0;
    while (!q.empty())
    {
        int q_size = q.size(); // 현재 상황에서 1번 이동할 크기 지정
        while (q_size--)
        {
            int cur_x = q.front().first, cur_y = q.front().second;
            // cout << cur_y << ", " << cur_x << endl;
            q.pop();
            for (int i = 0; i < 4; i++)
            { // 동서남북
                int nx = cur_x + next_x[i];
                int ny = cur_y + next_y[i];
                if (nx > 0 && ny > 0 && nx + X - 1 <= M && ny + Y - 1 <= N && !visit[ny][nx])
                {
                    if (move(nx, ny, i))
                    {
                        q.push({nx, ny});
                        visit[ny][nx] = true;
                    }
                }
            }
        }
        // cout << "---------------------------\n";
        answer++;
        if (visit[ey][ex])
            break;
    }
    if (!visit[ey][ex])
        return -1;
    return answer;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    init();
    cout << bfs(sx, sy);

    return 0;
}