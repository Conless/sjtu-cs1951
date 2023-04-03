#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 1e5 + 5;

int n, m;
pair<int, int> x[MAXN];

const int MAXM = 5005;

pair<int, int> temp[MAXN];

void sort(pair<int, int> *a, int l, int r) {
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

void solve1() {
    sort(x, 1, n);
    int lasans = 0;
    while (m--) {
        int a, b;
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        cout << (a ^ lasans) << ' ' << (b ^ lasans) << endl;
        int lasa = -1, lasb = -1, ans = 1e8 + 1;
        for (int i = 1; i <= n; i++)
            if (x[i].second == a) {
                if (lasb != -1)
                    ans = min(ans, x[i].first - lasb);
                lasa = x[i].first;
            } else if (x[i].second == b) {
                if (lasa != -1)
                    ans = min(ans, x[i].first - lasa);
                lasb = x[i].first;
            }
        if (ans != 1e8 + 1) {
            // cout << ans << endl;
            lasans = ans;
        } else {
            // cout << "invalid\n";
            lasans = 0;
        }
    }
}

void solve2() {
    sort(x, 1, n);
    int lasa = 0, lasb = 0;
    int near[MAXN][2];
    for (int i = 1; i < MAXN; i++)
        near[i][0] = near[i][1] = 1e8 + 1;
    for (int i = 1; i <= n; i++) {
        if (x[i].second == 1) {
            lasa = x[i].first;
        } else if (x[i].second == 2) {
            lasb = x[i].first;
        }
        if (lasa)
            near[x[i].second][0] = min(near[x[i].second][0], x[i].first - lasa);
        if (lasb)
            near[x[i].second][1] = min(near[x[i].second][1], x[i].first - lasb);
    }
    lasa = lasb = 0;
    for (int i = n; i >= 1; i--) {
        if (x[i].second == 1) {
            lasa = x[i].first;
        } else if (x[i].second == 2) {
            lasb = x[i].first;
        }
        if (lasa)
            near[x[i].second][0] = min(near[x[i].second][0], lasa - x[i].first);
        if (lasb)
            near[x[i].second][1] = min(near[x[i].second][1], lasb - x[i].first);
    }
    int lasans = 0;
    for (int i = 1; i <= m; i++) {
        int a, b;
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        cout << (a ^ lasans) << ' ' << (b ^ lasans) << endl;
        if (a == 1) {
            if (near[b][0] != 1e8 + 1) {
                // cout << near[b][0] << endl;
                lasans = near[b][0];
            } else {
                // cout << "invalid\n";
                lasans = 0;
            }
        } else {
            if (near[b][1] != 1e8 + 1) {
                // cout << near[b][1] << endl;
                lasans = near[b][1];
            } else {
                // cout << "invalid\n";
                lasans = 0;
            }
        }
    }
}

int main() {
    time_t t;
    srand(time(&t));
    ios::sync_with_stdio(false);
    n = 20;
    m = 10;
    cout << n << ' ' << m << '\n';
    for (int i = 1; i <= n; i++) {
        x[i].first = rand() % 100 + 1;
        x[i].second = rand() % 10 + 1;
        cout << x[i].first << ' ' << x[i].second << endl;
    }
    solve1();
}
