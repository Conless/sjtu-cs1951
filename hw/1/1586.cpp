#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

const int MAXN = 1505;
const ll MOD = 1e9 + 7;

int cnt;
int tr[MAXN * 10][10], ed[MAXN * 10], fail[MAXN * 10];
string n;

void insert(string s) {
    int u = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        char ch = s[i];
        if (!tr[u][ch - '0'])
            tr[u][ch - '0'] = ++cnt;
        u = tr[u][ch - '0'];
    }
    ed[u] = 1;
}

void build() {
    int que[MAXN * 10];
    int head = 0, tail = 0;
    for (int i = 0; i < 10; i++)
        if (tr[0][i])
            que[++tail] = tr[0][i];
    while (head != tail) {
        int u = que[++head];
        for (int i = 0; i < 10; i++) {
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                que[++tail] = tr[u][i];
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}

ll f[MAXN * 10][2], g[MAXN * 10][2];

ll query() {
    ll res = 0;
    f[0][0] = 1;
    for (int i = n.size() - 1; i >= 0; i--) {
        memset(g, 0, sizeof(g));
        for (int j = 0; j <= cnt; j++) {
            int v;
            for (int k = 0; k < n[i] - '0'; k++) {
                v = tr[j][k];
                if (!ed[v])
                    g[v][0] = (g[v][0] + f[j][0] + f[j][1]) % MOD;
                else if (k == 0)
                    res = (res + f[j][0] + f[j][1]) % MOD;
            }
            v = tr[j][n[i] - '0'];
            if (!ed[v]) {
                g[v][0] = (g[v][0] + f[j][0]) % MOD;
                g[v][1] = (g[v][1] + f[j][1]) % MOD;
            } else if (n[i] == '0')
                res = (res + f[j][0] + f[j][1]) % MOD;
            for (int k = n[i] - '0' + 1; k < 10; k++) {
                v = tr[j][k];
                if (!ed[v])
                    g[v][1] = (g[v][1] + f[j][0] + f[j][1]) % MOD;
            }
        }
        memcpy(f, g, sizeof(g));
        // cout << "at position " << i << "\n";
        // for (int j = 0; j <= cnt; j++)
        //     cout << j << " " << g[j][0] << " " << g[j][1] << endl;
    }
    for (int j = 0; j <= cnt; j++)
        res = (res + g[j][0]) % MOD;
    return (res - 1 + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        insert(s);
    }
    build();
    cout << query() << endl;
    return 0;
}