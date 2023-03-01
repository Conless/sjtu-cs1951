#include <iostream>
#include <cstring>

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

bool check(int len) {
    int res = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= len; i++) {
        if (key[i] == -1)
            continue;
        if (!cnt[key[i]])
            res++;
        cnt[key[i]]++;
    }
    if (res >= ans1)
        return true;
    for (int i = len + 1; i <= m; i++) {
        if (key[i - len] != -1) {
            cnt[key[i - len]]--;
            if (!cnt[key[i - len]])
                res--;
        }
        if (key[i] == -1)
            continue;
        if (!cnt[key[i]])
            res++;
        cnt[key[i]]++;
        if (res >= ans1)
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> word[i];
        int num = get_hash(word[i]);
        vis[num] = 1;
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
        if (vis[num] && !cnt[num])
            ans1++, cnt[num] = 1;
    }
    int l = ans1, r = m;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans2 = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans1 << endl << ans2 << endl; 
}