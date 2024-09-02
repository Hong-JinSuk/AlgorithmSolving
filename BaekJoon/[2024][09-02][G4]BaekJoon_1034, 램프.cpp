#include <iostream>
#include <map>

using namespace std;

int N, M, K;
int answer = 0;

map<string, pair<int, int>> lampsPattern;  // {pattern, {0의 갯수, 패턴의 갯수}}

void input() {
    cin >> N >> M;
    string line;
    for (int x = 0; x < N; x++) {
        cin >> line;
        if (lampsPattern.find(line) != lampsPattern.end()) {
            lampsPattern[line].second++;
        } else {
            int zeroCount = 0;
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == '0') zeroCount++;
            }
            lampsPattern.insert({line, {zeroCount, 1}});
        }
    }
    cin >> K;
}

void sol() {
    for (auto pattern : lampsPattern) {
        string str = pattern.first;
        int zeroCount = pattern.second.first;
        int patternCount = pattern.second.second;

        cout << str << " " << zeroCount << ", " << patternCount << endl;

        if (patternCount <= answer || zeroCount > K) continue;
        if ((zeroCount - K) % 2 != 0) continue;

        answer = patternCount;
    }

    cout << answer;
}

int main() {
    input();
    sol();
    return 0;
}