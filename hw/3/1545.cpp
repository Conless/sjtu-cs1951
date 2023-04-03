#include <iostream>

constexpr int MAXN = 3000;

int m, n;
long long t[2 * MAXN + 10][2 * MAXN + 10];

void add(int x, int y, int d);
long long find(int x, int y, int d);

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

int main() {
    qin >> n >> m;
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= m; ++i) {
            int a;
            qin >> a;
            add(i, j, a);
        }
    }

    int opt = 0;
    int x, y, d;
    while (true) {
        qin >> opt >> x >> y >> d;
        if (opt == 1) {
            add(x, y, d);
        }
        else {
            printf("%lld\n", find(x, y, d));
        }
    }

    return 0;
}

long long sum(int x, int y) {
    if (x <= 0 || y <= 0 || x >= m + n || y >= m + n) return 0;
    long long ans = 0;
    for (int i = x; i > 0; i -= i & (-i)) {
        for (int j = y; j > 0; j -= j & (-j)) {
            ans += t[i][j];
        }
    }
    return ans;
}

long long find(int x, int y, int d) {
//    std::cout << sum(x + y - 1, y - x + d + m) << std::endl;
//    std::cout << sum(x + y - 1, y - x + d + m) << std::endl;
//    std::cout << sum(x + y + d - 1, y - x - d + m) << std::endl;
//    std::cout << sum(x + y - d - 1, y - x - d + m) << std::endl;
    return sum(x + y + d - 1, y - x + d + m) - sum(x + y + d - 1, y - x - d + m - 1) - sum(x + y - d - 1 - 1, y - x + d + m) + sum(x + y - d - 1 - 1, y - x - d + m - 1);
}

void add(int x, int y, int d) {
    for (int i = x + y - 1; i < m + n; i += i & (-i)) {
        for (int j = y - x + m; j < m + n; j += j & (-j)) {
            t[i][j] += d;
        }
    }
}
