#include <iostream>

using namespace std;

const int MAXN = 3e5 + 5;

int cnt;
int tr[MAXN][26], ed[MAXN], fail[MAXN];
string s;

void insert(string t) {
    int u = 0;
    for (int i = 0; i < t.size(); i++) {
        char ch = t[i];
        if (!tr[u][ch - 'a'])
            tr[u][ch - 'a'] = ++cnt;
        u = tr[u][ch - 'a'];
    }
    ed[u] = t.size();
}

void build() {
    int que[MAXN];
    int head = 0, tail = 0;
    for (int i = 0; i < 26; i++)
        if (tr[0][i])
            que[++tail] = tr[0][i];
    while (head != tail) {
        int u = que[++head];
        for (int i = 0; i < 26; i++) {
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                ed[tr[u][i]] = max(ed[tr[u][i]], ed[fail[tr[u][i]]]);
                que[++tail] = tr[u][i];
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}

int query() {
    int len = s.size(), u = 0, tail = 0;
    int las[MAXN];
    las[0] = -1;
    for (int i = 0; i < len; i++) {
        u = tr[u][s[i] - 'a'];
        int beg = i - ed[u] + 1;
        while (tail && beg <= las[tail - 1] + 1)
            tail--;
        if (tail || !beg)
            las[++tail] = i;
    }
    return tail ? tail : -1;
}

int main() {
    ios::sync_with_stdio(false);
    int L;
    cin >> L >> s;
    while (L--) {
        string t;
        cin >> t;
        insert(t);
    }
    build();
    cout << query() << endl;
    return 0;
}