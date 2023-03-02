#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 1e5 + 5;
const int MOD = 1919810;

int n, m;
int ans1, ans2;
int vis[MOD], cnt[MOD], key[MAXN];
string word[MAXN], text[MAXN], str[MOD];

int get_hash(const string &s) {
    int res = 0;
    for (const auto &ch : s)
        res = (res * 26 + ch - 'a') % MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> word[i];
        int num = get_hash(word[i]);
        str[num] = word[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> text[i];
        int num = get_hash(text[i]);
        if (text[i] != str[num]) {
            key[i] = -1;
            continue;
        }
        key[i] = num;
        if (!vis[num])
            ans1++, vis[num] = 1;
    }
    cout << ans1 << endl;
    int l = 1;
    while (l <= m && key[l] == -1)
        l++;
    if (l >= m) {
        cout << m + 1 - l << endl;
        return 0;
    }
    cnt[key[l]]++;
    int r = l, res = 1;
    while (r < m && res < ans1) {
        r++;
        if (key[r] == -1)
            continue;
        if (cnt[key[r]] == 0)
            res++;
        cnt[key[r]]++;
    }
    while (l <= r) {
        if (key[l] >= 0) {
            if (cnt[key[l]] == 1)
                break;
            cnt[key[l]]--;
        }
        l++;
    }
    ans2 = r - l + 1;
    while (r < m) {
        r++;
        if (key[r] < 0)
            continue;
        cnt[key[r]]++;
        while (l <= r) {
            if (key[l] >= 0) {
                if (cnt[key[l]] == 1)
                    break;
                cnt[key[l]]--;
            }
            l++;
        }
        ans2 = min(ans2, r - l + 1);
    }
    cout << ans2 << endl;
    return 0;
}