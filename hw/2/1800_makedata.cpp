#include <bits/stdc++.h>

using namespace std;

const int mp = 100;

int main() {
    time_t t;
    srand(time(&t));
    int n = 10, maxp = 10, w = 2;
    printf("%d %d %d\n", n, maxp, w);
    for (int i = 1; i <= n; i++) {
        int as = rand() % maxp, bs = rand() % maxp;
        int ap = rand() % mp + mp, bp = rand() % mp + mp;
        if (bp > ap)
            bp = ap - 1;
        printf("%d %d %d %d\n", ap, bp, as, bs);
    }
    return 0;
}