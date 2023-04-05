#include <bits/stdc++.h>
// #include <Dark/inout>
/* Read function part. */

namespace dark {

/* Read a visible char. (Using standard ASCII.) */
char &read_char(char &ch) {
    do { ch = getchar(); } while(ch > 126 || ch < 33);
    return ch;
}

/* Read a signed integer. */
template <class integer>
integer &read_s(integer &num) {
    char ch;
    bool flag = false;
    num = 0;
    while(!isdigit(ch = getchar())) if(ch == '-') flag = true;
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    if(flag) num = -num;
    return num;
}

/* Read an unsigned integer. */
template <class integer>
integer &read_u(integer &num) {
    char ch;
    num = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return num;
}

/* Special case : read a visible char. */
auto &read(char &ch) { return read_char(ch); }

auto &read(signed char  &num)  { return read_s(num); }
auto &read(signed short &num)  { return read_s(num); }
auto &read(signed int   &num)  { return read_s(num); }
auto &read(signed long  &num)  { return read_s(num); }

auto &read(unsigned char  &num) { return read_u(num); }
auto &read(unsigned short &num) { return read_u(num); }
auto &read(unsigned int   &num) { return read_u(num); }
auto &read(unsigned long  &num) { return read_u(num); }

auto &read(signed   long long &num) { return read_s(num); }
auto &read(unsigned long long &num) { return read_u(num); }

#ifdef __SIZEOF_INT128__ /* Special support for int128. */
auto &read(__int128_t &num)  { return read_s(num); }
auto &read(__uint128_t &num) { return read_u(num); }
#endif

auto &read(float &num)  { scanf("%f",&num) ; return num; }
auto &read(double &num) { scanf("%lf",&num); return num; }

#ifdef __SIZEOF_LONG_DOUBLE__
auto &read(long double &num) { scanf("%Lf",&num); return num; }
#endif

/* Read a visible string. (Using standard ASCII.) */
char *read(char *str) { 
    do { *str   = getchar(); } while(*str > 126 || *str < 33); 
    do { *++str = getchar(); } while(*str > 32 && *str < 127);
    *str = '\0';
    return str;
}


/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read_s(integer &arg,integers &...args) { read_s(arg); read_s(args...); }
/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read_u(integer &arg,integers &...args) { read_u(arg); read_u(args...); }
/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read(integer &arg,integers &...args)   { read(arg);   read(args...); }



/* Paramless version. */


/* Read an integer any given type. */
template <class integer>
integer read() { integer tmp; return read(tmp); }
/* Read an unsigned integer of given type. */
template <class integer>
integer read_u() { integer tmp; return read_u(tmp); }
/* Read a signed integer of given type. */
template <class integer>
integer read_s() { integer tmp; return read_s(tmp); }
/* Read a visible char. */
char read_char() { char tmp; return read_char(tmp); }

/* Avoid misusage. */
template <class integer>
void read(integer &arg) = delete;

}

using namespace std;


const int N = 3e5 + 9;
struct node { int x1,x2,w; } s[N];
long long f[N];
long long pre[N];

inline int lowbit(int x) { return x & (-x); }

int tot = 0;
inline void insert(int x,long long v) {
    while(x <= tot) {
        if(v > pre[x]) pre[x] = v;
        x += lowbit(x);
    }
}

inline long long query(int x) {
    long long ans = 0;
    while(x) {
        ans = max(ans,pre[x]);
        x ^= lowbit(x);
    }
    return ans;
}

signed main() {
    int n,v;
    dark::read_u(n,v);
    for(int i = 1 ; i <= n ; ++i) {
        int x,t;
        dark::read_u(x,t,s[i].w);
        t *= v;
        s[i].x1 = t + x;
        s[i].x2 = t - x;
    }
    sort(s + 1,s + n + 1,[](const node &lhs,const node &rhs) {
        return lhs.x2 < rhs.x2;
    });
    int last = -1e9;
    for(int i = 1 ; i <= n ; ++i) {
        if(s[i].x2 != last) ++tot;
        last = s[i].x2;
        s[i].x2 = tot;
    }
    sort(s + 1,s + n + 1,[](const node &lhs,const node &rhs) {
        return lhs.x1 != rhs.x1 ? lhs.x1 < rhs.x1 : lhs.x2 < rhs.x2;
    });
    long long premax = 0;
    for(int i = 1 ; i <= n ; ++i) {
        f[i] = s[i].w + query(s[i].x2);
        // cout << s[i].x2 << ' ' << f[i] << '\n';
        premax = max(premax,f[i]);
        insert(s[i].x2,f[i]);
    }
    printf("%lld",premax);
    return 0;
}