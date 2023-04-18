#include <bits/stdc++.h>

using namespace std; // NOLINT

const int siz = 100000;
auto main() -> int {
    ios::sync_with_stdio(false);
    time_t t;
    srand(time(&t));
    int n = siz;
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        cout << rand() % siz + 1 << " ";
    }
    cout << endl;
    for (int i = 2; i <= n; i++) {
        cout << rand() % (i - 1) + 1 << " ";
    }
    cout << endl;
    int q = siz;
    cout << q << endl;
    for (int i = 1; i <= q; i++) {
        int x = rand() % n + 1;
        int k = rand() % 3;
        cout << x << ' ' << k << endl;
    }
    cout << 1 << endl;
    return 0;
}