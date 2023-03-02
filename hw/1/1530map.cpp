#include <bits/stdc++.h>

using namespace std;

map<string, int> mp;

int main() {
    int n, m, ans = 0;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        mp[s] = 1;
    }
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        if (mp[s] == 1) {
            ans++;
            mp[s] = 0;
        }
    }
    cout << ans << endl;
    return 0;
}
