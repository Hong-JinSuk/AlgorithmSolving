#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n, t;

vector<string> init()
{
    cin >> n;
    vector<string> numberBook(n);
    for (int i = 0; i < n; i++)
    {
        cin >> numberBook[i];
    }
    sort(numberBook.begin(), numberBook.end());
    return numberBook;
}

void sol(vector<string> numBook)
{

    for (int i = 0; i < n - 1; i++)
    {
        string cur = numBook[i];
        string next = numBook[i + 1];

        if (cur.size() >= next.size())
            continue;
        if (cur == next.substr(0, cur.size()))
        {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);

    cin >> t;
    for (int testcase = 0; testcase < t; testcase++)
    {
        vector<string> numberBook = init();
        sol(numberBook);
    }

    return 0;
}