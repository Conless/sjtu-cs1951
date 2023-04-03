#include <bits/stdc++.h>

using namespace std;

int main() {
    time_t t;
    srand(time(&t));
    int n = 20, v = 5;
    cout << n << ' ' << v << endl;
    for (int i = 1; i <= n; i++) {
        int x = rand() % 100 + 1, t = rand() % 100 + 1, w = rand() % 100 + 1;
        cout << x << ' ' << t << ' ' << w << endl;
    }
    return 0;
}