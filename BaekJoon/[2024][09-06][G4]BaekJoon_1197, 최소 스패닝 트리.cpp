#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int V, E;

vector<pair<int, pair<int, int>>> edges;
int root[10001];

void input() {
    cin >> V >> E;

    for (int i = 1; i <= V; i++) {
        root[i] = i;
    }

    for (int i = 0; i < E; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        edges.push_back({C, {A, B}});
    }

    sort(edges.begin(), edges.end());
}

int getRoot(int x) {
    if (root[x] == x) return x;
    return root[x] = getRoot(root[x]);
}

long long sol() {
    int cost, A, B;
    long sum = 0;
    for (auto edge : edges) {
        cost = edge.first;
        A = edge.second.first;
        B = edge.second.second;
        if (getRoot(A) != getRoot(B)) {
            sum += cost;
            root[getRoot(B)] = getRoot(A);
        }
    }
    return sum;
}

int main() {
    input();
    cout << sol();
    return 0;
}