#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 5
//
// -1 0 1 2 3

int sol(vector<int> vec) {
    int left, right, sum, GOOD = 0;
    for (int i = 0; i < vec.size(); i++) {
        left = 0;
        right = vec.size() - 1;

        if (i == left) left++;
        if (i == right) right--;

        while (left < right) {
            sum = vec[left] + vec[right];
            if (sum == vec[i]) {
                GOOD++;
                break;
            }

            if (sum < vec[i]) left++;
            if (sum > vec[i]) right--;

            if (i == left)
                left++;
            else if (i == right)
                right--;
        }
    }
    return GOOD;
}

int main() {
    int N;
    cin >> N;
    vector<int> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }
    sort(vec.begin(), vec.end());

    cout << sol(vec);
    return 0;
}