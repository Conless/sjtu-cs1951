#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

namespace sjtu {

class hash_map {
  private:
    static const int MAXN = 1e6 + 5;
    pair<int, int> data[MAXN];

    int get_pos(int key) {
        int pos = key % MAXN;
        while (data[pos].first && data[pos].first != key)
            pos = (pos + 1) % MAXN;
        return pos;
    }

  public:
    void clear() {
        for (int i = 0; i < MAXN; i++)
            data[i] = {0, 0};
    }
    void insert(int key, int value) {
        int pos = get_pos(key);
        data[pos] = {key, value};
    }
    int find(int key) {
        int pos = get_pos(key);
        return data[pos].second;
    }
};

}

#define ll long long

sjtu::hash_map m;

ll pow(ll x, ll y, ll MOD) {
    int res = 1;
    while (y) {
        if (y & 1)
            res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}

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

int main() {
    ios::sync_with_stdio(false);
    int T;
    qin >> T;
    while (T--) {
        ll q, g, y, n, p, x;
        qin >> q >> g >> y >> n;
        p = q << 1 | 1;
        m.clear();
        ll mul = 1;
        int s = ceil(sqrt(p));
        m.insert(mul, 0);
        for (int t = 1; t < s; t++) {
            mul = mul * g % p;
            m.insert(mul, t);
        }
        // calc x, s.t. g^x = y (mod p)
        // assume x = ys - t, which leads to (g^s)^y * inv_y = g^t (mod p)
        mul = pow(y, p - 2, p);
        ll gs = pow(g, s, p);
        for (int y = 1; y <= s; y++) {
            mul = mul * gs % p;
            int iter = m.find(mul);
            if (iter) {
                x = y * s - iter;
                break;
            }
        }
        for (int i = 1; i <= n; i++) {
            int c1, c2;
            qin >> c1 >> c2;
            // since c1 = g^r mod p, we have c2 = y^r*m = (g^x)^r*m = c1^x*m mod p
            // therefore, m = c2 * inv(c1^x)
            printf("%lld ", 1LL * c2 * pow(pow(c1, x, p), p - 2, p) % p);
        }
        printf("\n");
    }
    return 0;
}