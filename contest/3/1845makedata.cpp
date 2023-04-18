#include <bits/stdc++.h>

using namespace std; // NOLINT

const int SIZ = 20;
auto main() -> int {
    ios::sync_with_stdio(false);
    time_t t;
    srand(time(&t));
    int n = SIZ;
    int k = 3;
    int l = 3;
    cout << n << " " << k << " " << l << endl;
    for (int i = 1; i <= n; i++) {
        cout << rand() % SIZ + 1 << " ";
    }
    cout << endl;
    for (int i = 2; i <= n; i++) {
        cout << rand() % (i - 1) + 1 << " " << i << '\n';
    }
    return 0;
}