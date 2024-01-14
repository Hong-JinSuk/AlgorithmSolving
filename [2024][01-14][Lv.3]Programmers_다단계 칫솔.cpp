#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map<string, int> Ref;
int Amount[10001];
int parent[10001];

void Cul(int num, int Cash) {
    
    int Up = Cash / 10; // 위로 보내줄 금액
    Amount[num] += (Cash - Up); // 이건 내가 먹음
    if (Up == 0 || parent[num] == num) return; // 추천인에게 줄 돈이 없거나, 추천인이 없다면

    Cul(parent[num], Up); // 추천인에게 돈을 보냄

}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {

    vector<int> answer;

    for (int i = 0; i < enroll.size(); i++) {
        Ref.insert({ enroll[i],i }); // 이름마다 번호 매칭
        parent[i] = i; // 자기 자신은 추천인이 없음
    }

    for (int i = 0; i < referral.size(); i++) {
        if (referral[i] == "-") continue;
        parent[i] = Ref[referral[i]];
    }

    for (int i = 0; i < seller.size(); i++) {
        int num = Ref[seller[i]]; // 판 사람의 번호
        int Cash = amount[i] * 100; // 판 사람의 금액
        Cul(num, Cash);
    }

    for (int i = 0; i < enroll.size(); i++) {
        answer.push_back(Amount[i]);
    }

    return answer;
}

int main() {

    vector<string> enroll = {"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"};
    vector<string> referral = { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
    vector<string> seller = { "young", "john", "tod", "emily", "mary" };
    vector<int> amount = { 12,4,2,5,10 };
    
    vector<int> answer = solution(enroll, referral, seller, amount);
    for (auto x : answer)
        cout << x << endl;
    return 0;
}