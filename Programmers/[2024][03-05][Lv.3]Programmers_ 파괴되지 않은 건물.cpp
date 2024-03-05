#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
    int answer = 0;

    vector<vector<int>> MAP(board.size() + 1, vector<int>(board[0].size() + 1, 0));

    for (vector<int> sk : skill)
    {
        int r1 = sk[1], c1 = sk[2], r2 = sk[3], c2 = sk[4], degree = sk[5];
        if (sk[0] == 1)
        { // attack
            MAP[r1][c1] -= degree;
            MAP[r1][c2 + 1] += degree;
            MAP[r2 + 1][c1] += degree;
            MAP[r2 + 1][c2 + 1] -= degree;
        }
        else
        { // recovery
            MAP[r1][c1] += degree;
            MAP[r1][c2 + 1] -= degree;
            MAP[r2 + 1][c1] -= degree;
            MAP[r2 + 1][c2 + 1] += degree;
        }
    }
    // 누적합
    for (int y = 0; y < board.size(); y++)
    {
        for (int x = 0; x < board[0].size(); x++)
        {
            MAP[y][x + 1] += MAP[y][x];
        }
    }
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[0].size() - 1; y++)
        {
            MAP[y + 1][x] += MAP[y][x];
        }
    }

    // board에 더하기
    for (int y = 0; y < board.size(); y++)
    {
        for (int x = 0; x < board[0].size(); x++)
        {
            board[y][x] += MAP[y][x];
            if (board[y][x] > 0)
                answer++;
        }
    }
    return answer;
}