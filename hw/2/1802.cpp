// finished with the help from DarkSharpness

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

int n;
double sqr[MAXN];
int h[MAXN];
double ans[MAXN];

/**
 * @brief calculate the answer of (l + r) / 2
 *
 * @param L the left scope of answer
 * @param R the right scope of answer
 */
void calc(int tag, int l, int r, int L, int R) {
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    int loc = L;
    double max_dis = sqr[mid - loc] + h[loc] - h[mid];
    for (int i = L + 1; i <= min(mid, R); ++i) {
        double cur_dis = sqr[mid - i] + h[i] - h[mid];
        if (max_dis <= cur_dis) {
            loc = i;
            max_dis = cur_dis;
        }
    }
    if (!tag)
        ans[mid] = max(ans[mid], max_dis);
    else
        ans[n - mid + 1] = max(ans[n - mid + 1], max_dis);
    /*
        Here, the correctness of answer is promised by the convexity of function sqrt(x), which suggests
            \forall x > a > b, f(x) = \sqrt{x-a}-\sqrt{x-b}=\frac{a-b}{\sqrt{x-a}+\sqrt{x-b}}
        is a decreasing function. Hence for all a < b < c < d, if
            \sqrt{c-b} + f[b] > \sqrt{c-a} + f[a]
        then
            \sqrt{d-b} + f[b] > \sqrt{d-a} + f[a]
        This idea is from DarkSharpness.
    */
    calc(tag, l, mid - 1, L, loc);
    calc(tag, mid + 1, r, loc, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    sqr[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        sqr[i] = sqrt(i);
    }
    calc(0, 1, n, 1, n);
    for (int i = 1; i < n - i + 1; i++)
        swap(h[i], h[n - i + 1]);
    calc(1, 1, n, 1, n);
    for (int i = 1; i <= n; i++)
        printf("%d\n", (int)ceil(ans[i]));
    return 0;
}