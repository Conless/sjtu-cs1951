#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

int n, cnt, ans;
int tr[MAXN][26];
int ecnt[MAXN], fail[MAXN];

std::string t;

void insert(std::string s) {
    int u = 0;
    for (auto ch : s) {
        if (!tr[u][ch - 'a'])
            tr[u][ch - 'a'] = ++cnt;
        u = tr[u][ch - 'a'];
    }
    ecnt[u]++;
}

void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (tr[0][i])
            q.push(tr[0][i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}

void query() {
    int u = 0;
    for (auto ch : t) {
        u = tr[u][ch - 'a'];
        for (int j = u; j && ecnt[j] != -1; j = fail[j]) {
            ans += ecnt[j];
            ecnt[j] = -1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string s;
        cin >> s;
        insert(s);
    }
    cin >> t;
    build();
    query();
    cout << ans << endl;
    return 0;
}