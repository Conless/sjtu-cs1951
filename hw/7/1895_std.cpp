#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define fre(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
using namespace std;

inline int read() {
  int sum = 0, f = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    sum = sum * 10 + ch - '0';
    ch = getchar();
  }
  return f * sum;
}

const int N = 400001;
struct edge {
  int to, next, w;
} e[N << 1];
struct ques {
  int x, y, w, id;
} q[N], E[N << 1], A[N << 1];
int n, s, m, Q, a[N], isoil[N], dep[N];
int head[N], cnt = 0, Head[N], Cnt = 0;
int w[N], d[N], v[N], ans[N];
int da[N], f[N][21], fa[N][21];
queue<int> que;

bool cmp(ques a, ques b) { return a.w < b.w; }

inline void add(int x, int y, int w) {
  e[++cnt] = (edge){head[x], y, w};
  head[x] = cnt;
}

inline void spfa() {
  memset(d, 0x3f, sizeof(d));
  for (int i = 1; i <= s; i++) que.push(a[i]), d[a[i]] = 0, w[a[i]] = a[i], v[a[i]] = 1;
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (int i = head[x]; i; i = e[i].to) {
      int k = e[i].next;
      if (d[k] <= d[x] + e[i].w) continue;
      d[k] = d[x] + e[i].w;
      w[k] = w[x];
      if (!v[k]) v[k] = 1, que.push(k);
    }
    v[x] = 0;
  }
}

inline int find_fa(int x) { return x == da[x] ? x : da[x] = find_fa(da[x]); }

inline void link(int i) {
  int a = find_fa(E[i].x), b = find_fa(E[i].y);
  if (a != b) da[a] = b;
}

int main() {
  n = read();
  s = read();
  m = read();
  for (int i = 1; i <= s; i++) a[i] = read(), isoil[a[i]] = 1;
  for (int i = 1; i <= n; i++) da[i] = i;
  for (int i = 1; i <= m; i++) {
    A[i].x = read();
    A[i].y = read();
    A[i].w = read();
    add(A[i].x, A[i].y, A[i].w);
    add(A[i].y, A[i].x, A[i].w);
  }
  spfa();
  for (int i = 1; i <= m; i++) {
    int x = A[i].x, y = A[i].y;
    if (w[x] != w[y]) E[++Cnt] = (ques){w[x], w[y], d[x] + d[y] + A[i].w};
  }
  Q = read();
  int tot = 1;
  for (int i = 1; i <= Q; i++) {
    q[i].x = read(), q[i].y = read(), q[i].w = read();
  }
  for (int i = 1; i <= Q; i++) q[i].id = i;
  sort(q + 1, q + Q + 1, cmp);
  sort(E + 1, E + Cnt + 1, cmp);
  for (int i = 1; i <= Q; i++) {
    while (E[tot].w <= q[i].w && tot <= Cnt) link(tot++);
    int a = find_fa(q[i].x), b = find_fa(q[i].y);
    if (a == b) ans[q[i].id] = 1;
  }
  for (int i = 1; i <= Q; i++) puts(ans[i] ? "TAK" : "NIE");
  return 0;
}
