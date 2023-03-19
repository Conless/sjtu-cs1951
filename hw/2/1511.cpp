#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 1e6 + 5;

typedef long long ll;

int n;
int x[MAXN], p[MAXN], c[MAXN];
ll s[MAXN], d[MAXN], f[MAXN], g[MAXN];
int que[MAXN];

// return whether a/b < c/d (ad < bc)
bool comp(ll a, ll b, ll c, ll d) {
    double k1 = 1.00 * a / b;
    double k2 = 1.00 * c / d;
    return k1 < k2;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> p[i] >> c[i];
        s[i] = s[i - 1] + p[i];
        d[i] = d[i - 1] + x[i] * p[i];
    }
    int head = 1, tail = 0;
    que[++tail] = 0;
    f[1] = g[1] = c[1];
    que[++tail] = 1;
    for (int i = 2; i <= n; i++) {
        while (head < tail) {
            if (!comp(g[que[head + 1]] - g[que[head]], s[que[head + 1]] - s[que[head]], x[i], 1))
                break;
            head++;
        }
        int j = que[head];
        f[i] = (f[j] + d[j] - x[i] * s[j]) + x[i] * s[i] - d[i] + c[i];
        g[i] = f[i] + d[i];
        while (head < tail) {
            if (!comp(g[i] - g[que[tail]], s[i] - s[que[tail]], g[que[tail]] - g[que[tail - 1]], s[que[tail] - s[que[tail - 1]]]))
                break;
            tail--;
        }
        que[++tail] = i;
        cout << f[i] << ' ';
    }
    cout << f[n] << endl;
    return 0;
}
