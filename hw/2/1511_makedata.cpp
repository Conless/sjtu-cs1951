#include <asm-generic/errno.h>
#include <bits/stdc++.h>

using namespace std;

const int delta = 10;
const int maxnum = 100;

int main() {
    int n = 10, lasx = 0;
    time_t t;
    srand(time(&t));
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        int x, p, c;
        if (i == 1)
            x = 0;
        else
            x = rand() % delta + lasx + 1;
        lasx = x;
        p = rand() % 10 + 1;
        c = rand() % maxnum + 1;
        cout << x << ' ' << p << ' ' << c << endl;
    }
    return 0;
}
