#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map<string, int> Ref;
int Amount[10001];
int parent[10001];

void Cul(int num, int Cash) {
    
    int Up = Cash / 10; // ���� ������ �ݾ�
    Amount[num] += (Cash - Up); // �̰� ���� ����
    if (Up == 0 || parent[num] == num) return; // ��õ�ο��� �� ���� ���ų�, ��õ���� ���ٸ�

    Cul(parent[num], Up); // ��õ�ο��� ���� ����

}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {

    vector<int> answer;

    for (int i = 0; i < enroll.size(); i++) {
        Ref.insert({ enroll[i],i }); // �̸����� ��ȣ ��Ī
        parent[i] = i; // �ڱ� �ڽ��� ��õ���� ����
    }

    for (int i = 0; i < referral.size(); i++) {
        if (referral[i] == "-") continue;
        parent[i] = Ref[referral[i]];
    }

    for (int i = 0; i < seller.size(); i++) {
        int num = Ref[seller[i]]; // �� ����� ��ȣ
        int Cash = amount[i] * 100; // �� ����� �ݾ�
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