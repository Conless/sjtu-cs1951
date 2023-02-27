#include <iostream>
#include <unordered_set>

using namespace std;

typedef long long ll;

const ll MOD = 5743895789234;
const int MAXN = 1e6 + 5;

int n, m, ans;
string s;
unordered_set<ll> st;
ll pw[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    cin >> s;
    ll res = 0;
    pw[0] = 1;
    for (int i = 1; i < n; i++)
        pw[i] = pw[i - 1] * 26 % MOD;
    for (int i = 0; i < m; i++)
        res = (res * 26 + s[i] - 'a') % MOD;
    st.insert(res);
    ans = 1;
    for (int i = m; i < n; i++) {
        res = (res * 26 + s[i] - 'a') % MOD;
        res = (res - (s[i - m] - 'a') * pw[m] % MOD + MOD) % MOD;
        if (st.find(res) == st.end()) {
            st.insert(res);
            ans++;
            // cout << res << ' ';
        }
    }
    cout << ans << endl;
    return 0;
}