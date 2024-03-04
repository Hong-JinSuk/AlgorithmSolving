#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#define INF 987654321
using namespace std;

int T, N, M, K;
int moveCost[101];                // 100개의 방에 가는 최솟값 비용
int roomCost[101];                // 방에 오는 코스트
vector<pair<int, int>> road[101]; // start , {end ,cost};
vector<int> inK;

void init()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int start, end, cost;
        cin >> start >> end >> cost;
        road[start].push_back({end, cost});
        road[end].push_back({start, cost});
    }
    cin >> K;
    for (int i = 0; i < K; i++)
    {
        int num;
        cin >> num;
        inK.push_back(num);
    }
}

void dik(int start)
{

    moveCost[start] = 0;
    queue<int> q;
    q.push(start);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < road[cur].size(); i++)
        {
            int next = road[cur][i].first;
            int cost = road[cur][i].second;
            int nextCost = moveCost[cur] + cost;
            if (moveCost[next] > nextCost)
            {
                moveCost[next] = nextCost;
                q.push(next);
            }
        }
    }
    for (int i = 1; i <= N; i++)
    {
        roomCost[i] += moveCost[i];
    }
}

void sol()
{
    for (int i = 1; i <= N; i++)
    {
        roomCost[i] = 0; // 테스트 케이스마다 roomCost는 초기화 시켜줘야함.
    }
    for (int i = 0; i < inK.size(); i++)
    {
        for (int i = 1; i <= N; i++)
        {
            moveCost[i] = INF; // 각각의 방에서 탐색이 끝나면 매번 초기화 시켜줘야함.
        }
        int start = inK[i];
        dik(start);
    }
}

int main()
{

    cin >> T;

    while (T--)
    {
        init();
        sol();
        int answerCost = INF;
        int answerNum;
        // 낮은 방번호부터 검사하므로 방까지 가는 거리가 같으면 번호가 낮은 방이 출력된다.
        for (int i = 1; i <= N; i++)
        {
            if (answerCost > roomCost[i])
            {
                answerNum = i;
                answerCost = roomCost[i];
            }
        }
        cout << answerNum << endl;
        // 테스트 케이스마다 전역변수 초기화
        inK.clear();
        for (int i = 1; i <= N; i++)
        {
            road[i].clear();
        }
    }

    return 0;
}