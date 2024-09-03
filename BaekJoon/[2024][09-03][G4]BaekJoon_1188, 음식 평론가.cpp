#include <iostream>

using namespace std;

int N, M;  // 소시지, 평론가

int gcd(int p, int q) {
    if (q == 0) return p;
    return gcd(q, p % q);
}

int main() {
    cin >> N >> M;

    cout << M - gcd(M, N);

    return 0;
}