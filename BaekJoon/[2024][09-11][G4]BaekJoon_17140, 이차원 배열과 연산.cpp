#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 101
#define endl "\n"

using namespace std;

int r, c, k, row = 3, col = 3;
int arr[MAX][MAX];
int numCount[MAX];

void input() {
    cin >> r >> c >> k;
    for (int y = 1; y <= 3; y++) {
        for (int x = 1; x <= 3; x++) {
            cin >> arr[y][x];
        }
    }
}

bool compare(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

void R() {
    for (int y = 1; y <= row; y++) {
        for (int i = 1; i <= 100; i++) numCount[i] = 0;
        for (int x = 1; x <= col; x++) numCount[arr[y][x]]++;

        vector<pair<int, int> > sum;
        for (int i = 1; i <= 100; i++) {
            if (numCount[i] == 0) continue;
            sum.push_back({i, numCount[i]});
        }
        sort(sum.begin(), sum.end(), compare);

        for (int i = 1; i <= col; i++) arr[y][i] = 0;

        int index = 1;
        for (int i = 0; i < sum.size(); i++) {
            if (i == 50) break;
            arr[y][index++] = sum[i].first;
            arr[y][index++] = sum[i].second;
        }
        int a = sum.size() * 2;
        col = max(col, a);
    }
    if (col > 100) col = 100;
}

void C() {
    for (int x = 1; x <= col; x++) {
        for (int i = 1; i <= 100; i++) numCount[i] = 0;
        for (int y = 1; y <= row; y++) numCount[arr[y][x]]++;

        vector<pair<int, int> > sum;
        for (int i = 1; i <= 100; i++) {
            if (numCount[i] == 0) continue;
            sum.push_back({i, numCount[i]});
        }
        sort(sum.begin(), sum.end(), compare);

        for (int i = 1; i <= col; i++) arr[i][x] = 0;

        int index = 1;
        for (int i = 0; i < sum.size(); i++) {
            if (i == 50) break;
            arr[index++][x] = sum[i].first;
            arr[index++][x] = sum[i].second;
        }

        int a = sum.size() * 2;
        row = max(row, a);
    }
    if (row > 100) row = 100;
}

int sol() {
    int cnt = 0;
    while (cnt <= 100) {

        if (arr[r][c] == k) return cnt;

        if (row >= col) R();
        else C();

        cnt++;
    }
    return -1;
}


int main() {
    input();
    cout << sol();
    return 0;
}
