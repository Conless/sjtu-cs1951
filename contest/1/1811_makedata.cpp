#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int n = 5;
int a[MAXN], b[MAXN];

int main() {
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        a[i] = a[i - 1] + rand() % 10 + 1;
        if (i == 1)
            a[i] = 1;
        b[n - i + 1] = b[n - i + 2] + rand() % 10 + 1;
        cout << a[i] << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++)
        cout << b[i] << ' ';
    cout << '\n';
    return 0;
}