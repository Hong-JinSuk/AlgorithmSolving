#include<iostream>
#include<vector>

using namespace std;

float A, B; // A와 B팀이 골을 넣을 확률
float answer = 0;
int sosu[] = { 2,3,5,7,11,13,17 };
float dp[19][19][19]; // 총 라운드는 18개 골수도 18골
// A만 소수, B만 소수, 둘다 소수 or 둘다 소수 X

float play_game(int round, int a, int b) {

	if (round == 18) {
		for (int x : sosu) {
			if (a == x || b == x) {
				return 1;
			}
		}
		return 0;
	}
	if (dp[round][a][b]) return dp[round][a][b];

	dp[round][a][b] += play_game(round + 1, a + 1, b + 1) * A * B;
	dp[round][a][b] += play_game(round + 1, a + 1, b) * A * (1 - B);
	dp[round][a][b] += play_game(round + 1, a, b + 1) * (1-A) * B;
	dp[round][a][b] += play_game(round + 1, a, b) * (1 - A) * (1 - B);

	return dp[round][a][b];
}

int main() {

	cin >> A >> B;
	A /= 100;
	B /= 100;

	cout << play_game(0, 0, 0);

	return 0;
}