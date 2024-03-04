#include <iostream>
#include <vector>
#include <cmath>
#define endl "\n"
using namespace std;

int N, L, R, y, x;
int MAP[50][50];
bool isvisit[50][50];
int next_x[] = {1, -1, 0, 0};
int next_y[] = {0, 0, 1, -1};
vector<pair<int, int>> Sum;

void init()
{
    cin >> N >> L >> R;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            cin >> MAP[y][x];
        }
    }
}

void dfs(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        int nx = x + next_x[i], ny = y + next_y[i];
        if (nx > -1 && ny > -1 && nx < N && ny < N)
        {
            int diff = abs(MAP[y][x] - MAP[ny][nx]); // 두 나라 사이의 인궃이
            if (!isvisit[ny][nx] && diff >= L && diff <= R)
            {
                isvisit[ny][nx] = true;
                Sum.push_back({nx, ny}); // 국경이 열린 나라 push_back
                dfs(nx, ny);
            }
        }
    }
}

void sumMap()
{
    int All = 0;
    for (auto xy : Sum)
    {
        int x = xy.first, y = xy.second;
        All += MAP[y][x];
    }
    All /= Sum.size();
    for (auto xy : Sum)
    {
        int x = xy.first, y = xy.second;
        MAP[y][x] = All;
    }
}

void sol()
{
    int answer = 0; // 인구이동 횟수
    while (1)
    {
        bool isEnd = true; // 인구 이동이 일어나지 않아 끝내도 되는가?
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                if (!isvisit[y][x])
                { // 탐색
                    isvisit[y][x] = true;
                    Sum.push_back({x, y});
                    dfs(x, y); // 이웃한 나라중에 국경이 열릴만한 나라를 찾아본다.
                }
                if (Sum.size() > 1)
                {                  // 국경이 열린나라가 있다면,
                    isEnd = false; // 인구 이동이 일어나서 끝내면 안된다.
                    sumMap();      // Sum에 속해있는 위치들에서 인구이동을 시킨다.
                }
                Sum.clear(); // 인구이동을 시키고 비워서 다음 인구 이동이 일어날 나라들을 받게해준다.
            }
        }
        if (isEnd)
        {
            cout << answer << endl;
            return;
        }
        answer++;
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                isvisit[y][x] = false;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    init(); // 인구를 넣어줌
    sol();  // 풀이
    return 0;
}