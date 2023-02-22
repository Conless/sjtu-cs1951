#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

const int MAXN = 1e6 + 5;

int n, cnt, cnt_edge;
int tr[MAXN][26];
int ans[MAXN], ecnt[MAXN << 1], fail[MAXN], head[MAXN];

unordered_map<string, int> pos;
unordered_map<string, vector<int>> key;
vector<pair<int, string>> v;

std::string t;

struct {
    int v, next;
} edge[MAXN << 1];

void insert(std::string s) {
    int u = 0;
    for (auto ch : s) {
        if (!tr[u][ch - 'a'])
            tr[u][ch - 'a'] = ++cnt;
        u = tr[u][ch - 'a'];
    }
    pos[s] = u;
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
        ecnt[u]++;
    }
}

void add_edge(int u, int v) {
    cnt_edge++;
    edge[cnt_edge].v = v;
    edge[cnt_edge].next = head[u];
    head[u] = cnt_edge;
}

void dfs(int u) {
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        dfs(v);
        ecnt[u] += ecnt[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string s;
        cin >> s;
        insert(s);
        if (key.find(s) == key.end())
            key.insert(make_pair(s, vector<int>()));
        key[s].push_back(i);
    }
    cin >> t;
    build();
    query();
    for (int i = 1; i <= cnt; i++)
        add_edge(fail[i], i);
    dfs(0);
    for (auto pr : key) {
        for (auto str_pos : pr.second)
            ans[str_pos] = ecnt[pos[pr.first]];
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    return 0;
}
