#include <iostream>

using namespace std;

const int MAXN = 1e3 + 5;

int pi[MAXN], st[MAXN], ed[MAXN];
long long ans = 0;
string s;

void kmp(const string &p) {
    string t = p + '#' + s;
    int n = t.size(), pos = p.size(), res = 0;
    pi[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j && t[i] != t[j])
            j = pi[j - 1];
        if (t[i] == t[j])
            j++;
        pi[i] = j;
        if (pi[i] == pos && i > pos)
            st[i - pos * 2]++, ed[i - pos - 1]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> s >> n;
    string t[MAXN];
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        kmp(t[i]);
    }
    //	for (int i = 0; i < s.size(); i++)
    //		cout << st[i] << ' ' << ed[i] << endl;
    for (int i = 0; i < s.size() - 1; i++)
        ans += ed[i] * st[i + 1];
    cout << ans << endl;
    return 0;
}
