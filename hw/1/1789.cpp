#include <iostream>
#include <map>

using namespace std;

const int MAXN = 2e6 + 5;


class QuickRead {
  public:
    inline char gc() {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
    }

    template <typename _Tp> inline QuickRead &operator>>(_Tp &num) {
        static char ch, sgn;
        ch = gc();
        sgn = 0;
        for (; !isdigit(ch); ch = gc()) {
            if (ch == -1)
                return *this;
            sgn |= (ch == '-');
        }
        num = 0;
        for (num = 0; isdigit(ch); ch = gc())
            num = num * 10 + (ch ^ '0');
        sgn && (num = -num);
        return *this;
    }
} qin;

int num[MAXN], fail[MAXN], len[MAXN];
map<int, int> tr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    int n, m = 0, cnt = 0;
    qin >> n;
    while (n--) {
        int opt, x;
        qin >> opt;
        if (opt == 1) {
            qin >> x;
            if (m) {
                int u = num[m];
                num[++m] = x;
                tr[u][x] = ++cnt;
                len[cnt] = m;
                fail[cnt] = tr[fail[u]][m];
                printf("%d\n", m - len[fail[cnt]]);
            } else {
                num[++m] = ++cnt;
                puts("1");
            }
        } else {
            int u = num[m - 1];
            tr[u][num[m]] = 0;
            m--;
        }
    }
    return 0;
}