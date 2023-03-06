#include <iostream>

using namespace std;

const int MAXN = 2e5 + 5;

string s;
int cnt[2];
int tr[2][MAXN][26], fail[2][MAXN << 3];
int st[MAXN], ed[MAXN];
int st_tag[MAXN], ed_tag[MAXN];

void insert(const string &p) {
    int u = 0;
    for (int i = 0; i < p.size(); i++) {
        if (!tr[0][u][p[i] - 'a'])
            tr[0][u][p[i] - 'a'] = ++cnt[0];
        u = tr[0][u][p[i] - 'a'];
    }
    ed[u]++;
    u = 0;
    for (int i = p.size() - 1; i >= 0; i--) {
        if (!tr[1][u][p[i] - 'a'])
            tr[1][u][p[i] - 'a'] = ++cnt[1];
        u = tr[1][u][p[i] - 'a'];
    }
    st[u]++;
}

void build(int opt) {
    int head = 0, tail = 0;
    int que[MAXN];
    for (int i = 0; i < 26; i++)
        if (tr[opt][0][i])
            que[++tail] = tr[opt][0][i];
    while (head != tail) {
        int u = que[++head];
        for (int i = 0; i < 26; i++) {
            if (tr[opt][u][i]) {
                fail[opt][tr[opt][u][i]] = tr[opt][fail[opt][u]][i];
                que[++tail] = tr[opt][u][i];
            } else {
                tr[opt][u][i] = tr[opt][fail[opt][u]][i];
            }
        }
    }
}

void query() {
    int u = 0;
    for (int i = 0; i < s.size(); i++) {
        u = tr[0][u][s[i] - 'a'];
        int v = u;
        while (v) {
            ed_tag[i] += ed[v];
            v = fail[0][v];
        }
    }
    u = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        u = tr[1][u][s[i] - 'a'];
        int v = u;
        while (v) {
            st_tag[i] += st[v];
            v = fail[1][v];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> s >> n;
    while (n--) {
        string t;
        cin >> t;
        insert(t);
    }
    build(0);
    build(1);
    query();
    long long ans = 0;
    for (int i = 0; i < s.size() - 1; i++)
        ans += ed_tag[i] * st_tag[i + 1];
    cout << ans << endl;
    return 0;
}