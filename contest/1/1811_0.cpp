#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 1e5 + 5;

typedef long long ll;

int n;
ll sum, a[MAXN], b[MAXN], f[MAXN], q[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    sum *= b[n];
    for (int i = 1; i <= n; i++)
        b[i] -= b[n];
    memset(f, 0x7f, sizeof(f));
    f[1] = 0;
    int head = 1, tail = 0;
    q[++tail] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++)
            f[i] = min(f[i], f[j] + b[j] * a[i]);
        cout << f[i] << ' ';
    }
    cout << f[n] + sum << endl;
}