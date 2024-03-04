#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int N, Q;
int MAP[64][64];
bool visit[64][64];
int temp[64];
int next_x[] = {1, -1, 0, 0};
int next_y[] = {0, 0, 1, -1};
vector<int> Ls;
queue<pair<int, int>> q;

void init()
{
    cin >> N >> Q;
    for (int y = 0; y < pow(2, N); y++)
    {
        for (int x = 0; x < pow(2, N); x++)
        {
            cin >> MAP[y][x];
        }
    }
    for (int i = 0; i < Q; i++)
    {
        int L;
        cin >> L;
        Ls.push_back(L);
    }
}

void rotate(int sx, int sy, int size)
{
    if (size == 0)
        return;

    int ex = sx + size - 1, ey = sy + size - 1;
    int index = 0;
    for (int i = sx; i < sx + size - 1; i++)
        temp[index++] = MAP[sy][i]; // N 복사
    for (int i = sx; i < sx + size - 1; i++)
        MAP[sy][i] = MAP[ey--][sx]; // W => N
    ey = sy + size - 1;
    for (int i = ey; i > ey - size + 1; i--)
        MAP[i][sx] = MAP[ey][ex--]; // S => W
    ex = sx + size - 1;
    for (int i = sy; i < sy + size - 1; i++)
        MAP[ey][ex--] = MAP[i][sx + size - 1]; // E => S
    ex = sx + size - 1;
    index = 0;
    for (int i = sy; i < sy + size - 1; i++)
        MAP[i][ex] = temp[index++]; // N복사 => E

    rotate(sx + 1, sy + 1, size - 2);
}

bool melt(int x, int y, int size)
{
    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + next_x[i];
        int ny = y + next_y[i];
        if (nx > -1 && ny > -1 && nx < size && ny < size)
        {
            if (MAP[ny][nx] > 0)
                cnt++;
        }
    }
    if (cnt < 3)
        return true;
    return false;
}

void fire(int size)
{
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (MAP[y][x] == 0)
                continue;
            else if (x == 0 && y == 0)
                continue;
            else if (x == 0 && y == size - 1)
                continue;
            else if (x == size - 1 && y == 0)
                continue;
            else if (x == size - 1 && y == size - 1)
                continue;
            if (melt(x, y, size))
                q.push({x, y});
        }
    }
    while (!q.empty())
    {
        int X = q.front().first, Y = q.front().second;
        MAP[Y][X]--;
        q.pop();
    }
    if (MAP[0][0] > 0)
        MAP[0][0]--;
    if (MAP[size - 1][0] > 0)
        MAP[size - 1][0]--;
    if (MAP[0][size - 1] > 0)
        MAP[0][size - 1]--;
    if (MAP[size - 1][size - 1] > 0)
        MAP[size - 1][size - 1]--;
}

int bfs(int x, int y)
{
    int Size = 0;

    q.push({x, y});
    visit[y][x] = true;
    while (!q.empty())
    {
        int cur_x = q.front().first, cur_y = q.front().second;
        q.pop();
        Size++;
        for (int i = 0; i < 4; i++)
        {
            int nx = cur_x + next_x[i], ny = cur_y + next_y[i];
            if (nx > -1 && ny > -1 && nx < pow(2, N) && ny < pow(2, N))
            {
                if (!visit[ny][nx] && MAP[ny][nx] > 0)
                {
                    q.push({nx, ny});
                    visit[ny][nx] = true;
                }
            }
        }
    }

    return Size;
}

int main()
{

    init();

    for (int i = 0; i < Q; i++)
    {
        int size = pow(2, Ls[i]);
        for (int y = 0; y < pow(2, N); y += pow(2, Ls[i]))
        {
            if (size == 1)
                break;
            for (int x = 0; x < pow(2, N); x += pow(2, Ls[i]))
            {
                rotate(x, y, size);
            }
        }
        fire(pow(2, N));
    }

    int answer = 0;
    int Size = 0;
    for (int y = 0; y < pow(2, N); y++)
    {
        for (int x = 0; x < pow(2, N); x++)
        {
            answer += MAP[y][x];
            if (!visit[y][x] && MAP[y][x] > 0)
                Size = max(Size, bfs(x, y));
        }
    }

    cout << answer << endl
         << Size;

    return 0;
}