#include <iostream>

using namespace std;

const int MAXN = 3e5 + 5;

int n, m, las, cnt;
string t[MAXN];
int pi[MAXN];

int kmp(const string &p, const string &s) {
    string t = p + '#' + s;
    int n = t.size(), pos = p.size(), res = 0;
    pi[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j && t[i] != t[j])
            j = pi[j - 1];
        if (t[i] == t[j])
            j++;
        pi[i] = j;
        if (pi[i] == pos && i > pos)
            res++;
    }
    return res;
}

int main() {
    cin >> n >> m;
    while (n--) {
        int opt;
        string p;
        cin >> opt >> p;
        if (m)
            opt ^= las;
        if (opt == 1) {
            t[++cnt] = p;
        } else if (opt == 2) {
            for (int i = 1; i <= cnt; i++) {
                if (t[i] == p) {
                    t[i] = "";
                    break;
                }
            }
        } else {
            int res = 0;
            for (int i = 1; i <= cnt; i++) {
                if (t[i] == "")
                    continue;
                res += kmp(t[i], p);
            }
            cout << (las = res) << endl;
        }
    }
}