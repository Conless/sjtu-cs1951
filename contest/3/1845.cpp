#include <cstdio>
#include <iostream>

using namespace std; // NOLINT

const int MAXN = 1e6 + 5;

using ll = uint64_t;

int n, k, l, cnt;
int head[MAXN], depth[MAXN], mson[MAXN];
ll ans = 0;
ll w[MAXN], siz[MAXN];
ll buff[MAXN], bufg[MAXN];
ll *curf = buff, *f[MAXN];
ll *curg = bufg, *g[MAXN];

struct {
    int v_, next_;
} edge[MAXN << 1];

void AddEdge(int u, int v) {
    cnt++;
    edge[cnt] = {v, head[u]};
    head[u] = cnt;
}

void Build(int u, int last) {
    depth[u] = 1;
    siz[u] = w[u];
    for (int i = head[u]; i != 0; i = edge[i].next_) {
        int v = edge[i].v_;
        if (v == last) {
            continue;
        }
        Build(v, u);
        if (depth[v] + 1 > depth[u]) {
            mson[u] = v;
            depth[u] = depth[v] + 1;
        }
        siz[u] += siz[v];
    }
}

void Dfs(int u, int tp, int last) {
    if (tp == u) {
        f[u] = curf;
        curf += depth[u];
        g[u] = curg;
        curg += depth[u];
    }
    f[u][0] = g[u][0] = w[u];
    if (mson[u] != 0) {
        f[mson[u]] = f[u] + 1;
        g[mson[u]] = g[u] + 1;
        Dfs(mson[u], tp, u);
        if (depth[u] > k + 1 && w[u] > l) {
            ans += f[mson[u]][k] * g[u][0];
            // cout << ans << endl;
        }
        f[u][0] += siz[mson[u]];
    }
    for (int i = head[u]; i != 0; i = edge[i].next_) {
        int v = edge[i].v_;
        if (v == mson[u] || v == last) {
            continue;
        }
        Dfs(v, v, u);
        if (w[u] > l) {
            for (int j = max(0, k - depth[u] + 1); j < depth[v]; j++) {
                ans += g[v][j] * f[u][max(0, k - j)];
                // cout << ans << endl;
            }
        }
        for (int j = 0; j < depth[v]; j++) {
            g[u][j + 1] += g[v][j];
            f[u][j + 1] += f[v][j];
        }
        f[u][0] += siz[v];
    }
}

auto main() -> int {
    ios::sync_with_stdio(false);
    cin >> n >> k >> l;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i < n; i++) {
        int u;
        int v;
        cin >> u >> v;
        AddEdge(u, v);
        AddEdge(v, u);
    }
    Build(1, 0);
    Dfs(1, 1, 0);
    cout << ans << endl;
    return 0;
}
