#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 5e4 + 5;
const int MAXM = 3e5 + 5;

struct Ask {
    int l, r, a, b, pos, id;
    bool operator<(const Ask &x) const {
        if (pos != x.pos)
            return pos < x.pos;
        return pos & 1 ? r < x.r : r > x.r;
    }
} ask[MAXM];

template <int SIZE> class BinaryIndexedTree {
  public:
    BinaryIndexedTree(int _n = SIZE) : n(_n) { memset(data, 0, sizeof(data)); }

    void add(int x, int k) {
        while (x <= n) {
            data[x] += k;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ans = 0;
        while (x) {
            ans += data[x];
            x -= lowbit(x);
        }
        return ans;
    }

  private:
    int n, data[SIZE << 1 | 1];
    inline int lowbit(int x) { return x & (-x); }
};

class QuickRead
{
public:
    inline char gc()
    {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
    }

    template <typename _Tp>
    inline QuickRead & operator >> (_Tp & num)
    {
        static char ch, sgn;
        ch = gc();
        sgn = 0;
        for(; !isdigit(ch); ch = gc())
        {
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


template <class T> void qsort(T *a, int l, int r) {
    T mid = a[(l + r) / 2];
    int i = l, j = r;
    do {
        while (a[i] < mid)
            i++;
        while (mid < a[j])
            j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j)
        qsort(a, l, j);
    if (i < r)
        qsort(a, i, r);
}

int n, q;
int num[MAXN], cnt[MAXN], ans[MAXM];

int main() {
    ios::sync_with_stdio(false);
    qin >> n >> q;
    BinaryIndexedTree<MAXM> m(n);
    int t = ceil(sqrt(n));
    for (int i = 1; i <= n; i++)
        qin >> num[i];
    for (int i = 1; i <= q; i++) {
        qin >> ask[i].l >> ask[i].r >> ask[i].a >> ask[i].b;
        ask[i].pos = ask[i].l / t;
        ask[i].id = i;
    }
    qsort(ask, 1, q);
    int l = 1, r = 0;
    for (int i = 1; i <= q; i++) {
        while (r < ask[i].r) {
            r++;
            if (!cnt[num[r]])
                m.add(num[r], 1);
            cnt[num[r]]++;
        }
        while (l > ask[i].l) {
            l--;
            if (!cnt[num[l]])
                m.add(num[l], 1);
            cnt[num[l]]++;
        }
        while (r > ask[i].r) {
            cnt[num[r]]--;
            if (!cnt[num[r]])
                m.add(num[r], -1);
            r--;
        }
        while (l < ask[i].l) {
            cnt[num[l]]--;
            if (!cnt[num[l]])
                m.add(num[l], -1);
            l++;
        }
        ans[ask[i].id] = m.query(ask[i].b) - m.query(ask[i].a - 1);
    }
    for (int i = 1; i <= q; i++)
        cout << ans[i] << '\n';
    return 0;
}