#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

const int MAXN = 1e5 + 5, MAXQ = 320;

struct {
    int v, next;
} edge[MAXN << 1];

int n, m, t, cnt, rt;
int w[MAXN], s[MAXN], head[MAXN], bel[MAXN];
int l[MAXQ], r[MAXQ];
int res[MAXQ], lazy[MAXN];

int near[MAXN][MAXQ]; // here near means nearest on the tree path
int sum[MAXN][MAXQ];

void pre() {
    t = ceil(sqrt(n));
    for (int i = 1; i <= t; i++)
        l[i] = (i - 1) * t + 1, r[i] = i * t;
    if (l[t] <= n)
        r[t] = n;
    else
        r[t - 1] = n;
    for (int i = 1; i <= n; i++)
        bel[i] = (i - 1) / t + 1;
}

void dfs(int u, int las) {
    // inherit the data from its father
    s[u] = w[u];
    for (int j = 1; j * t <= n; j++) {
        near[u][j] = near[las][j];
        sum[u][j] = sum[las][j];
    }
    near[u][bel[las]] = las;
    sum[u][bel[u]]++;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (v == las)
            continue;
        dfs(v, u);
        s[u] += s[v];
    }
    res[bel[u]] += s[u];
}

void add_edge(int u, int v) {
    cnt++;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void fix_its_range(int u, int delta) {
    int pos = (u - 1) / t + 1;
    while (u) {
        s[u] += delta;
        u = near[u][pos];
    }
}

void fix_the_range(int pos) {
    for (int i = l[pos]; i <= r[pos]; i++) {
        if (lazy[i]) {
            fix_its_range(i, lazy[i]);
            lazy[i] = 0;
        }
    }
    int summ = 0;
    for (int i = l[pos]; i <= r[pos]; i++)
        summ += s[i];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        if (u == 0)
            rt = v;
        else if (v == 0)
            rt = u;
        else {
            add_edge(u, v);
            add_edge(v, u);
        }
    }
    pre();
    dfs(rt, 0);
    while (m--) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            // deal with its own range
            int pos = bel[x], delta = y - w[x];
            w[x] = y;
            res[pos] += sum[x][pos] * delta;
            fix_its_range(x, delta);
            // deal with other ranges
            for (int j = 1; j * t <= n; j++) {
                if (j == pos)
                    continue;
                lazy[near[x][j]] += delta;
                res[j] += sum[x][j] * delta;
            }
        } else {
            long long ans = 0;
            int mid_start, mid_end;
            int left_range = (x - 1) / t + 1, right_range = (y - 1) / t + 1;
            if (left_range == right_range) {
                fix_the_range(left_range);
                for (int i = x; i <= y; i++)
                    ans += s[i];
            } else {
                if ((x - 1) % t == 0)
                    mid_start = left_range;
                else {
                    mid_start = left_range + 1;
                    fix_the_range(left_range);
                    for (int i = x; i <= r[left_range]; i++)
                        ans += s[i];
                }
                if (y % t == 0)
                    mid_end = right_range;
                else {
                    mid_end = right_range - 1;
                    fix_the_range(right_range);
                    for (int i = l[right_range]; i <= y; i++)
                        ans += s[i];
                }
                for (int i = mid_start; i <= mid_end; i++)
                    ans += res[i];
            }
            cout << ans << '\n';
        }
    }
    return 0;
}