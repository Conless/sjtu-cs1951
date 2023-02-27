#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2e6 + 5;

int pi[MAXN];
vector<int> ans1, ans2;

void kmp(string t, string p) {
    string res = p + '#' + t;
    int n = res.size(), m = p.size();
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && res[i] != res[j])
            j = pi[j - 1];
        if (res[i] == res[j])
            j++;
        pi[i] = j;
    }
    ans2.reserve(m);
    for (int i = 0; i < m; i++)
        ans2.push_back(pi[i]);
    for (int i = m + 1; i < n; i++) {
        if (pi[i] == m)
            ans1.push_back(i - 2 * m + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    string s1, s2;
    cin >> s1 >> s2;
    kmp(s1, s2);
    sort(ans1.begin(), ans1.end());
    for (auto x : ans1)
        cout << x << endl;
    for (auto x : ans2)
        cout << x << ' ';
    cout << '\n';
    return 0;
}