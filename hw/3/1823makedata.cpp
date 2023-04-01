#include <bits/stdc++.h>

using namespace std;

int n = 50000, m = 250000;

int main() {
    freopen("1823.in", "w", stdout);
    ios::sync_with_stdio(false);
    cout << n << ' ' << m << endl;
    for (int i = 1; i <= n; i++)
        cout << rand() % n + 1 << ' ';
    cout << endl;
    for (int i = 1; i <= m; i++) {
        int l = rand() % n + 1, r = rand() % n + 1;
        if (l > r)
            swap(l, r);
        int a = rand() % n + 1, b = rand() % n + 1;
        if (a > b)
            swap(a, b);
        cout << l << ' ' << r << ' ' << a << ' ' << b << endl;
    }
    return 0;
}