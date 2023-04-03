#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int n, m, p, q;
pair<int, int> x[MAXN];
vector<pair<int, int>> y[MAXN];
int cnt[MAXN], is_long_comp[MAXN], long_comp[MAXN];
int dis[MAXN][350];

int comp_to_key[MAXN];

void pre() {
    sort(x + 1, x + n + 1, [](const auto &a, const auto &b) { return a.second < b.second; });
    for (int i = 1; i <= n; i++) {
        if (!comp_to_key[x[i].second])
            comp_to_key[x[i].second] = ++m;
        x[i].second = m;
        cnt[m]++;
    }
    int t = floor(sqrt(n));
    sort(x + 1, x + n + 1, [](const auto &a, const auto &b) { return a.first < b.first; });
    memset(dis, 0x7f, sizeof(dis));
    for (int i = 1; i <= m; i++) {
        if (cnt[i] >= t) {
            p++;
            is_long_comp[i] = p;
            long_comp[p] = i;
            int last = 0;
            for (int j = 1; j <= n; j++) {
                if (x[j].second == i)
                    last = j;
                else if (last)
                    dis[x[j].second][p] = min(dis[x[j].second][p], x[j].first - x[last].first);
            }
            last = 0;
            for (int j = n; j >= 1; j--) {
                if (x[j].second == i)
                    last = j;
                else if (last)
                    dis[x[j].second][p] = min(dis[x[j].second][p], x[last].first - x[j].first);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!is_long_comp[x[i].second])
            y[x[i].second].push_back(x[i]);
    }
}

int query(int a, int b) { // here the argument is the value after comp_to_key, which means <= m
    if (!a || !b)
        return 0;
    if (is_long_comp[b])
        swap(a, b);
    if (is_long_comp[a])
        return dis[b][is_long_comp[a]];
    int siza = y[a].size(), sizb = y[b].size();
    pair<int, int> las = {0, 0};
    int i, j, ans = 1e8 + 1;
    for (i = 0, j = 0; i < siza && j < sizb; ) {
        if (y[a][i].first < y[b][j].first) {
            if (las.first && las.second == b)
                ans = min(ans, y[a][i].first - las.first);
            las = y[a][i];
            i++;
        } else {
            if (las.first && las.second == a)
                ans = min(ans, y[b][j].first - las.first);
            las = y[b][j];
            j++;
        }
    }
    if (las.second == a && j < sizb)
        ans = min(ans, y[b][j].first - las.first);
    if (las.second == b && i < siza)
        ans = min(ans, y[a][i].first - las.first);
    return ans == 1e8 + 1 ? 0 : ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> x[i].first >> x[i].second;
    pre();
    int lasans = 0;
    while (q--) {
        int a, b;
        cin >> a >> b;
        a = comp_to_key[a ^ lasans];
        b = comp_to_key[b ^ lasans];
        lasans = query(a, b);
        if (!lasans)
            cout << "invalid\n";
        else
            cout << lasans << '\n';
    }
    return 0;
}
