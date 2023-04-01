#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int n = 1000, m = 1000;
int fa_old[n + 1], fa[n + 1], p[n + 1];

int main() {
    ios::sync_with_stdio(false);
    time_t t;
    srand(time(&t));
    cout << n << ' ' << m << endl;
    for (int i = 1; i <= n; i++) {
        cout << rand() % 100 << ' ';
        if (i)
            fa_old[i] = rand() % (i - 1) + 1;
        p[i] = i;
    }
    cout << endl;
    random_shuffle(p + 1, p + n + 1);
    for (int i = 1; i <= n; i++)
        fa[p[i]] = p[fa_old[i]];
    for (int i = 1; i <= n; i++)
        cout << fa[i] << ' ' << i << endl;
    for (int i = 1; i <= m; i++) {
        int opt = rand() % 2 + 1;
        if (opt == 1) {
            int x = rand() % n + 1, y = rand() % 100;
            cout << opt << ' ' << x << ' ' << y << endl;
        } else {
            int x = rand() % n + 1, y = rand() % n + 1;
            if (x > y)
                swap(x, y);
            cout << opt << ' ' << x << ' ' << y << endl;
        }
    }
    return 0;
}