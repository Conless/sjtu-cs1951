#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 3e5 + 5;
const int MAXM = 3e3 + 5;

struct mouse {
    int x, t, w;
    bool operator<(const mouse &x) const { return t < x.t; }
} m[MAXN];

mouse temp[MAXN];

void sort(mouse *a, int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    sort(a, l, mid);
    sort(a, mid + 1, r);
    int i, j, k = l;
    for (i = l, j = mid + 1; i <= mid && j <= r;) {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    if (i <= mid) {
        while (k <= r)
            temp[k++] = a[i++];
    } else {
        while (k <= r)
            temp[k++] = a[j++];
    }
    for (k = l; k <= r; k++)
        a[k] = temp[k];
}


int n, v;
long long f[MAXN];

int ok[MAXM][MAXM];

void solve() {
    sort(m, 1, n);
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++)
            ok[i][j] = (abs(m[i].x - m[j].x) <= (m[j].t - m[i].t) * v);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = 0;
        for (int j = 1; j < i; j++)
            if (ok[j][i])
                f[i] = max(f[i], f[j]);
        f[i] += m[i].w;
        ans = max(ans, f[i]);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> m[i].x >> m[i].t >> m[i].w;
    if (n <= 3000)
        solve();
    return 0;
}