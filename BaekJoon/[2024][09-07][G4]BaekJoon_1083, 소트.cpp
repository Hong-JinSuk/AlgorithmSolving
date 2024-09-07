#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N, S;
vector<int> A;

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        A.push_back(num);
    }
    cin >> S;
}

void change(int left_index, int right_index) {
    for (int i = right_index; i > left_index; i--) {
        int temp = A[i];
        A[i] = A[i - 1];
        A[i - 1] = temp;
    }
}

void sol() {
    int left_index = 0;
    while (S > 0) {
        int MAX = -1, right_index = left_index;
        if (left_index == N) break;
        for (int i = left_index; i <= left_index + S; i++) {
            if (i >= N) break;
            if (A[i] > MAX) {
                MAX = A[i];
                right_index = i;
            }
        }
        if (left_index == right_index) {
            left_index++;
            continue;
        } else {
            change(left_index, right_index);
            S -= right_index - left_index;
        }
        left_index++;
    }
}

int main() {
    input();
    sol();
    for (int i : A) {
        cout << i << " ";
    }

    return 0;
}