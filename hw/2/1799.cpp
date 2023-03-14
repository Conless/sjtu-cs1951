#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 1e5 + 5;

int n;
long long ans;
int cost[MAXN], st[MAXN], l[MAXN], r[MAXN];
long long sum[MAXN], res[MAXN];


int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
        sum[i] = sum[i - 1] + cost[i];
    }
    int tp = 0;
    st[++tp] = l[1] = 1;
    for (int i = 2; i <= n; i++) {
        while (tp && cost[st[tp]] >= cost[i]) {
            r[st[tp]] = i - 1;
            tp--;
        }
        l[i] = st[tp] + 1;
        st[++tp] = i;
    }
    while (tp) {
        r[st[tp]] = n;
        tp--;
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, (sum[r[i]] - sum[l[i] - 1]) * cost[i]);
        // printf("%d %d\n", l[i], r[i]);
    }
    cout << ans << endl;
    return 0;
}
