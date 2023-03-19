#include <iostream>
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

using ll = long long;
const ll N = 1e6+10;
ll sum[N],num[N],n,c[N],x[N];
ll head = 1,tail = 1,q[N],f[N];

inline double slope(ll i,ll j) noexcept
{ return double(f[j] + sum[j] - f[i] - sum[i]) / (num[j] - num[i]); } 


signed main() {
    dark::read_u(n);
	for(int i = 1 ; i <= n; ++i) {
        dark::read_u(x[i],num[i],c[i]);
		sum[i] =  sum[i-1] + x[i] * num[i]; 
		num[i] += num[i-1];
	}
	for(int i = 1 ; i <= n ; ++i) {
		while(head != tail && slope(q[head],q[head+1]) <= x[i])
            ++head;
		int j = q[head];
		f[i] = f[j] - sum[i] + sum[j] + (num[i] - num[j]) * x[i] + c[i];

		while(head != tail && slope(q[tail - 1],q[tail]) > 
                              slope(q[tail],i))
            --tail;
		q[++tail]=i;
	}
    int i = n;
    ll ans = f[n];
    while(num[i] - num[i - 1] == 0)
        if(ans > f[--i]) ans = f[i];
    printf("%lld\n",ans);
	return 0 ;
}

/* 

价格相当于先移到0再移到当前位置 
f[i] = f[j] - sum[i] + sum[j] + (num[i] - num[j]) * x[i] + c[i];
f[j] + sum[j] = x[i] * num[j] + f[i] + sum[i] - c[i] - num[i] * x[i]; 
k = x[i]; 单调
x = num[j]; 单调
y = f[j]+sum[j];

*/