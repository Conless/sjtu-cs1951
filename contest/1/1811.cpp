#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 1e5 + 5;

typedef long long ll;

int n;
ll sum, a[MAXN], b[MAXN], f[MAXN], q[MAXN];

double slope(int i, int j) { return 1.0 * (f[i] - f[j]) / (b[j] - b[i]); }

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
        while (head < tail && slope(q[head], q[head + 1]) < (double)a[i])
            head++;
        f[i] = f[q[head]] + b[q[head]] * a[i];
        while (head < tail && slope(q[tail - 1], q[tail]) > slope(q[tail], i))
            tail--;
        q[++tail] = i;
        // cout << f[i] << ' ';
    }
    cout << f[n] + sum << endl;
}
