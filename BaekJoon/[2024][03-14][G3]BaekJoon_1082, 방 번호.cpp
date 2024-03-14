#include <iostream>
#include <vector>
using namespace std;

int N;
int budget;
vector<int> P;
void init()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int cost;
        cin >> cost;
        P.push_back(cost);
    }
    cin >> budget;
}

string sol()
{

    if (N == 1)
        return "0";
    // 예산으로 살 수 있는 숫자가 없을 때(0을 제외한), 0을 반환
    for (int i = 1; i < N; i++)
    {
        if (budget >= P[i])
            break;
        if (i == N - 1)
            return "0";
    }

    string answer = "";
    int minCost = 999;
    string minNum;

    // 가장 코스트가 낮은 숫자를 구한다. 단, 같은 코스트면 큰 숫자를 선택.
    for (int i = N - 1; i > 0; i--)
    {
        if (P[i] < minCost)
        {
            minCost = P[i];
            minNum = i + '0';
        }
    }

    // 맨 앞자리에 배치
    answer += minNum;
    budget -= minCost;

    // 가장 코스트가 낮은 숫자를 뒤에 쭉~ 붙혀준다.
    if (P[0] < minCost)
    {
        minCost = P[0];
        minNum = "0";
        while (budget >= minCost)
        {
            budget -= minCost;
            answer += minNum;
        }
    }
    else
    {
        while (budget >= minCost)
        {
            budget -= minCost;
            answer += minNum;
        }
    }

    int index = 0;
    // 숫자 끝까지 보거나 예산이 남아있을 때까지 반복한다.
    while (answer.size() > index && budget > 0)
    {
        int num = answer[index] - '0';
        for (int i = N - 1; i > num; i--)
        { // 더 큰 앞자리로 바꿀 수 있나?
            if (budget >= (P[i] - P[num]))
            {                            // 예산이 교체비용보다 크다면
                answer[index] = i + '0'; // 교체
                budget -= (P[i] - P[num]);
                break;
            }
        }
        index++; // 다음 자릿수로 이동
    }

    return answer;
}

int main()
{

    init();
    cout << sol();
}