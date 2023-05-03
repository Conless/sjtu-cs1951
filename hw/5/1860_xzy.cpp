#include <iostream>

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

/* Write function part. */

namespace dark {

/* Write a integer. */
template <class integer>
void writeInt(integer num) {
    if(!num) return (void) putchar('0');
    if(num < 0) num = -num , putchar('-');
    static char ch[3 * sizeof(integer)];
    int top = 0;
    while(num) {
        ch[top++] = '0' ^ (num % 10);
        num /= 10;
    }
    while(top--) putchar(ch[top]);
}

/* Write a integer and start a new line.*/
template <class integer>
void writelineInt(integer num) {
    if(!num) return (void) puts("0");
    if(num < 0) num = -num,putchar('-');
    static char ch[3 * sizeof(integer) + 1] = {0};
    int top = 3 * sizeof(integer) - 1;
    while(num) {
        ch[--top] = '0' ^ (num % 10);
        num /= 10;
    }
    puts(ch + top);
}

/* Write an integer */

void write(signed char  num) { writeInt(num); } 
void write(signed short num) { writeInt(num); } 
void write(signed int   num) { writeInt(num); } 
void write(signed long  num) { writeInt(num); } 

void write(unsigned char  num) { writeInt(num); } 
void write(unsigned short num) { writeInt(num); } 
void write(unsigned int   num) { writeInt(num); } 
void write(unsigned long  num) { writeInt(num); } 

void write(signed long long   num) { writeInt(num); }
void write(unsigned long long num) { writeInt(num); }


void writeline(signed char  num) { writelineInt(num); } 
void writeline(signed short num) { writelineInt(num); } 
void writeline(signed int   num) { writelineInt(num); } 
void writeline(signed long  num) { writelineInt(num); } 

void writeline(unsigned char  num) { writelineInt(num); } 
void writeline(unsigned short num) { writelineInt(num); } 
void writeline(unsigned int   num) { writelineInt(num); } 
void writeline(unsigned long  num) { writelineInt(num); } 

void writeline(signed long long   num) { writelineInt(num); }
void writeline(unsigned long long num) { writelineInt(num); }



/* Write a char. */
void write (char _ch) { putchar(_ch); }
/* Write a char and start a new line. */
void writeline (char _ch) { putchar(_ch);putchar('\n'); }

/* Write a string. */
void write(char *__s) { while(*__s) { putchar(*(__s++)); } }
/* Write a string. */
void write(const char *__s) { while(*__s) { putchar(*(__s++)); } }

/* Write a string and start a new line. */
void writeline(char *__s) { puts(__s); }
/* Write a string. */
void writeline(const char *__s) { puts(__s); }


void write(float num)  { printf("%f" ,num); }
void writeline(float num)  { printf("%f\n" ,num); }

void write(double num) { printf("%lf",num); }
void writeline(double num) { printf("%lf\n",num); }

#ifdef __SIZEOF_LONG_DOUBLE__
void write(long double num) { printf("%Lf",num); }
void writeline(long double num) { printf("%Lf\n",num); }
#endif


/* Following is multiple-variable case. */

/* Special case. */

void write() {}
void writeline() { putchar('\n'); }


/* Write a sequence of integers , separated by ' '. */
template <class integer,class ...integers>
void write(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    write(args...);
}
/* Write a line of integers , separated by ' '. */
template <class integer,class ...integers>
void writeline(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    writeline(args...);
}

/* Print just one integer. */
template <class integer>
void print(const integer &arg) { write(arg); }

/* Print a sequence of integers without no separation. */
template <class integer,class ...integers>
void print(const integer &arg,const integers &...args) {
    write(arg);
    print(args...);
}

/* Print just one integer and start a new line. */
template <class integer>
void printline(const integer &arg) { writeline(arg); }

/* Print a line of integers without no separation. */
template <class integer,class ...integers>
void printline(const integer &arg,const integers &...args) {
    write(arg);
    printline(args...);
}

/* Avoid misusage. */
template <class integer>
void write(const integer &) = delete;
/* Avoid misusage. */
template <class integer>
void writeline(const integer &) = delete;



}

int g[202][202][1002];
int v[202][202][1002];
int r,c,m;


int brute_force() {
    int maxn = 0;
    for(int i = 1 ; i <= r ; ++i)
        for(int j = 1 ; j <= c ; ++j) {
            int t;
            maxn = std::max(maxn,dark::read(t));
            g[i][j][t] += t;
            ++v[i][j][t];
        }
    for(int l = maxn ; l >= 1 ; --l)
        for(int i = 1 ; i <= r ; ++i)
            for(int j = 1 ; j <= c ; ++j)
                g[i][j][l] += g[i - 1][j][l] + g[i][j - 1][l]
                            - g[i - 1][j - 1][l],
                v[i][j][l] += v[i - 1][j][l] + v[i][j - 1][l]
                            - v[i - 1][j - 1][l];

    for(int i = 1 ; i <= r ; ++i)
        for(int j = 1 ; j <= c ; ++j)
          for (int l = maxn; l >= 1; --l) {
            g[i][j][l] += g[i][j][l + 1], v[i][j][l] += v[i][j][l + 1];
            std::cout << g[i][j][l] << ' ' << v[i][j][l] << '\n';
          }
    while(m--) {
        int a,b,c,d,h;
        dark::read(a,b,c,d,h); --a,--b;
        if(g[c][d][1] - g[a][d][1] - g[c][b][1] + g[a][b][1] < h) puts("Impossible");
        else {
            int l = 1;
            int r = maxn + 1;
            while(l != r) {
                int mid = (l + r) >> 1;
                int tmp = g[c][d][mid] - g[a][d][mid] - g[c][b][mid] + g[a][b][mid];
                if(tmp < h) r = mid;
                else l = mid + 1;
            } /* Now f(l) < h , f(l - 1) >= h */
            --l;
            int ret = (g[c][d][l] - g[a][d][l] - g[c][b][l] + g[a][b][l] - h) / l;
            dark::writeline(v[c][d][l] - v[a][d][l] - v[c][b][l] + v[a][b][l] - ret);
        }
    }
    return 0;
}

constexpr int N = 5e5 + 7;

struct node { int ls,rs,cnt,sum; } t[N * 20];

int tot = 0;
int build(int l,int r) {
    int root = ++tot;
    if(l == r) return root;
    int mid = (l + r) >> 1;
    t[root].ls = build( l , mid );
    t[root].rs = build(mid + 1,r);
    return root;
}

int update(int id,int l,int r,int loc) {
    int root = ++tot;
    t[root] = t[id]; 
    t[root].cnt += 1;
    t[root].sum += loc;
    if(l == r) return root;
    int mid = (l + r) >> 1;
    if(loc <= mid) t[root].ls = update(t[root].ls, l , mid ,loc);
    else           t[root].rs = update(t[root].rs,mid + 1,r,loc);
    return root;
}

/* Prefix sum of [1,target] in [L,R] larger than h. */
int query(int L,int R,int l,int r,int h) {
    int ans = 0;
    while(l != r) {
        int sum = t[t[R].ls].sum - t[t[L].ls].sum;
        int cnt = t[t[R].ls].cnt - t[t[L].ls].cnt;
        int mid = (l + r) >> 1;
        if(sum > h) L = t[L].ls , R = t[R].ls , r = mid;
        else if(sum == h) return ans + cnt;
        else        L = t[L].rs , R = t[R].rs , l = mid + 1,
                    h -= sum , ans += cnt;
    } /* Now l == r && h > 0 */
    return ans + h / r;
}

int a[N];
int rt[N];

signed main() {
    dark::read(r,c,m);
    if(r != 1) return brute_force();
    int maxn = 0;
    for(int i = 1 ; i <= c ; ++i)
        if(dark::read(a[i]) > maxn) maxn = a[i];

    rt[0] = build(1,maxn);

    for(int i = 1 ; i <= c ; ++i)
        rt[i] = update(rt[i - 1],1,maxn,a[i]); 

    while(m--) {
        int l,r,h;
        dark::read(l,l,r,r,h); --l;
        int sum = t[rt[r]].sum - t[rt[l]].sum;
        if(sum < h) puts("Impossible");
        else {
            dark::writeline(t[rt[r]].cnt - t[rt[l]].cnt - 
                            query(rt[l],rt[r],1,maxn,sum - h));
        }
    }
    return 0;
}