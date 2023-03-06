#include <cstring>
#include <iostream>

using std::string;

int next[1000001];
int short_[1000001];
// string str;
char str[1000001];

long long cal_guyi(const char *a) {
    next[0] = -1, short_[0] = 0;
    int c1 = 0, c2 = -1; //需要再额外开一个最短的字符串数组
    int len = strlen(a);
    while (c1 <= len) {
        if (c2 == -1 || a[c1] == a[c2]) {
            ++c1;
            ++c2;
            next[c1] = c2;
            if (short_[c2] > 0) {
                short_[c1] = short_[c2];
            } else {
                short_[c1] = c2;
            }
        } else {
            c2 = next[c2];
        }
    }
    long long ans = 0;
    for (int k = 1; k <= len; ++k) {
        if (next[k] > 0) {
            ans += k - short_[k];
        }
    }
    return ans;
}
int main() {
    //    freopen("t.in","r",stdin);
    //    freopen("t.out","w",stdout);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> str;
        std::cout << cal_guyi(str) << '\n';
    }
}