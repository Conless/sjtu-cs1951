#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAXN = 2e3 + 5;

int n, maxp, w, head, tail;
int ap[MAXN], bp[MAXN], as[MAXN], bs[MAXN];
ll f[MAXN][MAXN];
pair<int, ll> que[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> maxp >> w;
    for (int i = 1; i <= n; i++)
        cin >> ap[i] >> bp[i] >> as[i] >> bs[i];
    memset(f, -0x7f, sizeof(f));
    for (int i = 1; i <= w + 1; i++) {
        for (int j = 0; j <= as[i]; j++)
            f[i][j] = -j * ap[i];
        for (int j = 0; j <= maxp; j++)
            f[i][j] = max(f[i][j], f[i - 1][j]);
    }
    for (int i = w + 2; i <= n; i++) {
        int k = i - w - 1;
        for (int j = 0; j <= maxp; j++)
            f[i][j] = f[i - 1][j];
        // sell stock
        head = 1, tail = 0;
        for (int j = 0; j <= bs[i]; j++) {
            ll res = f[k][j] + j * bp[i];
            while (head <= tail && que[tail].second <= res)
                tail--;
            que[++tail] = {j, res};
        }
        f[i][0] = max(f[i][0], que[head].second);
        for (int j = 1; j < maxp; j++) {
            while (head <= tail && que[head].first < j)
                head++;
            if (j + bs[i] <= maxp) {
                ll res = f[k][j + bs[i]] + (j + bs[i]) * bp[i];
                while (head <= tail && que[tail].second <= res)
                    tail--;
                que[++tail] = {j + bs[i], res};
            }
            f[i][j] = max(f[i][j], que[head].second - j * bp[i]);
        }
        // buy stock
        head = 1, tail = 0;
        que[++tail] = {0, f[k][0]};
        f[i][0] = max(f[i][0], que[tail].second);
        for (int j = 1; j <= maxp; j++) {
            while (head <= tail && que[head].first < j - as[i])
                head++;
            ll res = f[k][j] + j * ap[i];
            while (head <= tail && que[tail].second <= res)
                tail--;
            que[++tail] = {j, res};
            f[i][j] = max(f[i][j], que[head].second - j * ap[i]);
        }
        // for (int j = 0; j <= maxp; j++)
        //     cout << f[i][j] << ' ';
        // cout << endl;
    }
    ll ans = 0;
    for (int j = 0; j <= maxp; j++)
        ans = max(ans, f[n][j]);
    cout << ans << endl;
    return 0;
}