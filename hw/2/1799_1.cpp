#include <iostream>

constexpr int MAXN = 1e5;
int n;
long long sum[MAXN + 5];
int cost[MAXN + 5];
int stk[MAXN + 5];
int lf[MAXN + 5];
int rt[MAXN + 5];
int top = -1;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> cost[i];
        sum[i] = cost[i] + sum[i - 1];
        while (top >= 0 && cost[stk[top]] >= cost[i]) {
            rt[stk[top]] = i - 1;
            --top;
        }
        stk[++top] = i;
        if (top == 0) lf[i] = 0;
        else lf[i] = stk[top - 1];
    }
    while (top >= 0) {
        rt[stk[top]] = n;
        --top;
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = std::max(ans, cost[i] * (sum[rt[i]] - sum[lf[i]]));
    }
    std::cout << ans;
    return 0;
}