#include <bits/stdc++.h>

using namespace std;

int main() {
    time_t t;
    srand(time(&t));
    int n = 20000, v = 5;
    cout << n << ' ' << v << endl;
    for (int i = 1; i <= n; i++) {
        int x = rand() % 10000000 + 1, t = rand() % 1000000 + 1, w = rand() % 1000000 + 1;
        cout << x << ' ' << t << ' ' << w << endl;
    }
    return 0;
}