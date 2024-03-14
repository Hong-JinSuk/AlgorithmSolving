#include <iostream>
#include <cmath>

using namespace std;

int X, Y;
double D, T, dist;
double Time = 0;
void init()
{
    cin >> X >> Y >> D >> T;
    dist = sqrt(pow(X, 2) + pow(Y, 2)); // 현재 위치에서 목적지까지의 거리
}

// 2번 점프하는 거리보다 아직 멀리 떨어져있나? 묻는 조건식
bool Jump()
{
    if (dist > 2 * D)
    {
        return true;
    }
    return false;
}

double sol()
{
    double answer;
    double case3 = dist;

    if (T >= D)
    { // 점프보다 걷는게 빠르거나 같다면, 걸어간다.
        return dist;
    }

    // 최단경로로 아직 점프해도 된다면, 계속 점프
    while (Jump())
    {
        dist -= D;
        Time += T;
    }

    double case1 = Time + 2 * T;               // 점프 2번으로 도착
    double case2 = Time + T + (abs(dist - D)); // 이제 걸어서감

    answer = min(case1, case2);
    answer = min(answer, case3);

    return answer;
}

int main()
{

    cout << fixed;
    cout.precision(9);

    init();
    cout << sol() << endl;

    return 0;
}