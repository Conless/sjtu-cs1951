#include <iostream>
#include <cmath>
using namespace std;
const int N = 1e6 + 3;
using ull = unsigned long long;
struct edge { int nxt,to; } e[N];
int head[N],tot = 0;
inline void adde(int fr,int to)
{ e[++tot] = {head[fr],to}; head[fr] = tot; }
ull w[N];
ull s[N];
int d[N],son[N];
int n,k,l;
void dfs0(int u) {
    d[u] = 1;
    s[u] = w[u];
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        dfs0(v);
        s[u] += s[v];
        if(d[v] >= d[u]) d[u] = d[v] + 1,son[u] = v;
    }
}
ull *f[N],g[N];
ull *p[N],q[N];
int dfn = 0;
ull ans;
ull c(int u,int x) {
    if(x >= d[u] - 1) return 0;
    return p[u][max(x + 1,0)];
}
void dfs1(int u) {
    ++dfn;
    *(f[u] = g + dfn) = w[u];
    *(p[u] = q + dfn) = w[u];
    if(!son[u]) return;

    dfs1(son[u]);
    p[u][0] += s[son[u]];
    if (w[u] > l && d[u] > k) {
        ans += w[u] * c(son[u], k - 1);
        // cout << ans << endl;
    }
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(v == son[u]) continue;
        dfs1(v);
        if(w[u] > l) {
            for(int j = 0 ; j < d[v] ; ++j)
                ans += c(u, k - j - 1) * f[v][j];
        }
        
        for(int j = 0 ; j < d[v] ; ++j) {        
            f[u][j + 1] += f[v][j];
            p[u][j + 1] += p[v][j];
        }
        p[u][0] += s[v];
    }
}


signed main() {
    ios::sync_with_stdio(false);
    std::cin >> n >> k >> l;
    for(int i = 1 ; i <= n ; ++i) cin >> w[i];
    for(int i = 1 ; i < n ; ++i) {
        int x,y;
        cin >> x >> y;
        adde(x,y);
    }
    dfs0(1);
    dfs1(1);
    std::cout << ans << std::endl;
    return 0;
}
