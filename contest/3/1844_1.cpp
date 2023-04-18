#include <iostream>
using namespace std;

int gcd(int x,int y)
{ return x ? gcd(y % x,x) : y; }

struct node {
    int x , y , z; /* Require x < y < z , or it might crash. */

    inline bool is_root() const noexcept { return y << 1 == x + z; }

    /* O(1) function */
    node top() const noexcept {
        int a = y - x;
        int b = z - y;
        return a < b ? node { z - (b - 1) % a - 1 - a , z - (b - 1) % a - 1 , z } :
                       node { x , x + (a - 1) % b + 1 , x + (a - 1) % b + 1 + b };
    }

    int dist() const noexcept {
        int a = y - x;
        int b = z - y;
        return a < b ? (b - 1) / a: (a - 1) / b;
    }

    /* Left or right branch. */
    bool dir() const noexcept {
        int a = y - x;
        int b = z - y;
        return a < b;
    }

    void sort() {
        if(x > y) std::swap(x,y);
        if(x > z) std::swap(x,z);
        if(y > z) std::swap(y,z);
    }
};

istream &operator >> (istream &is,node &tmp) 
{ return is >> tmp.x >> tmp.y >> tmp.z; }
ostream &operator << (ostream &os,const node &tmp) 
{ return os << tmp.x << ' ' << tmp.y << ' ' << tmp.z << '\n'; }

int depA,depB;

bool operator != (const node &a,const node &b) 
{ return a.x != b.x || a.y != b.y || a.z != b.z; }


bool check(node a,node b) {
    while(!a.is_root()) {
        depA += a.dist();
        a = a.top();
    }
    while(!b.is_root()) {
        depB += b.dist();
        b = b.top();
    }
    return a != b;
}

int cmp(int x,int y) { return x < y ? -1 : x > y; }


signed main() {
    node a,b;
    // ios::sync_with_stdio(false);
    cin >> a >> b;
    a.sort();
    b.sort();
    if(check(a,b)) { puts("NO"); return 0; }
    puts("YES");
    int ans = depA + depB;

    while(a != b) {
        node x = a.top();
        node y = b.top();
        int A = depA - a.dist();
        int B = depB - b.dist();
        if(A == B) {
            if(x != y) {
                a = x , depA = A;
                b = y , depB = B;
            } else break; /* a.top() == b.top() */
        } else if(A < B) {
            b = y , depB = B;
        } else/* A > B */{
            a = x , depA = A;       
        }
    }
    /* Now a == b || a.top() = b.top() */
    if(a != b) {
        if(a.dir() == b.dir()) ans -= min(depA,depB) << 1;
        else ans -= (depA - a.dist()) << 1;
    } else ans -= depA << 1; /* a == b case */
    cout << ans << '\n';
    return 0;
}
