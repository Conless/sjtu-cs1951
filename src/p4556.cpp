#include <bits/stdc++.h>

#define sn segtree[node]
#define sls segtree[sn.lson_]
#define srs segtree[sn.rson_]

#define sl segtree[lhs]
#define sr segtree[rhs]

using namespace std;  // NOLINT

constexpr int MAXN = 1e5 + 5;
constexpr int MAXM = MAXN * 80;

struct Tnode {
  int lson_, rson_;
  int pos_, cnt_;
} segtree[MAXM];

int n, cnt, maxc;
int rt[MAXN];

void Pushup(int node) {
  if (sn.lson_ == 0 || sn.rson_ == 0) {
    sn.pos_ = segtree[sn.lson_ | sn.rson_].pos_;
    sn.cnt_ = segtree[sn.lson_ | sn.rson_].cnt_;
    return;
  }
  if (sls.cnt_ >= srs.cnt_) {
    sn.pos_ = sls.pos_;
    sn.cnt_ = sls.cnt_;
  } else {
    sn.pos_ = srs.pos_;
    sn.cnt_ = srs.cnt_;
  }
}

void Add(int &node, int l, int r, int pos, int num) {
  if (node == 0) {
    node = ++cnt;
  }
  if (l == r) {
    sn.pos_ = pos;
    sn.cnt_ += num;
    return;
  }
  int mid = (l + r) >> 1;
  if (pos <= mid) {
    Add(sn.lson_, l, mid, pos, num);
  } else {
    Add(sn.rson_, mid + 1, r, pos, num);
  }
  Pushup(node);
}

auto Merge(int lhs, int rhs, int l, int r) -> int {
  if (lhs == 0 || rhs == 0) {
    return lhs | rhs;
  }
  if (l == r) {
    sl.cnt_ += sr.cnt_;
    return lhs;
  }
  int mid = (l + r) >> 1;
  sl.lson_ = Merge(sl.lson_, sr.lson_, l, mid);
  sl.rson_ = Merge(sl.rson_, sr.rson_, mid + 1, r);
  Pushup(lhs);
  return lhs;
}

struct Edge {
  int v_, next_;
} edge[MAXN << 1];

int m;
int fa[MAXN][20], depth[MAXN], head[MAXN], ans[MAXN];

void AddEdge(int u, int v) {
  edge[++m] = {v, head[u]};
  head[u] = m;
}

void Dfs1(int u, int las) {
  fa[u][0] = las;
  depth[u] = depth[las] + 1;
  for (int i = 1; i < 20; i++) {
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
  }
  for (int i = head[u]; i != 0; i = edge[i].next_) {
    int v = edge[i].v_;
    if (v == las) {
      continue;
    }
    Dfs1(v, u);
  }
}

auto Lca(int u, int v) -> int {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  for (int i = 19; i >= 0; i--) {
    if (depth[fa[u][i]] >= depth[v]) {
      u = fa[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 19; i >= 0; i--) {
    if (fa[u][i] != fa[v][i]) {
      u = fa[u][i];
      v = fa[v][i];
    }
  }
  return fa[u][0];
}

void Dfs2(int u) {
  for (int i = head[u]; i != 0; i = edge[i].next_) {
    int v = edge[i].v_;
    if (v == fa[u][0]) {
      continue;
    }
    Dfs2(v);
    rt[u] = Merge(rt[u], rt[v], 1, maxc);
  }
  ans[u] = segtree[rt[u]].cnt_ != 0 ? segtree[rt[u]].pos_ : 0;
}

auto main() -> int {
  ios::sync_with_stdio(false);
  int t;
  cin >> n >> t;
  for (int i = 1; i < n; i++) {
    int u, v; // NOLINT
    cin >> u >> v;
    AddEdge(u, v);
    AddEdge(v, u);
  }
  Dfs1(1, 0);
  maxc = 1e5;
  for (int i = 1; i <= t; i++) {
    int u, v, num;  // NOLINT;
    cin >> u >> v >> num;
    int f = Lca(u, v);
    Add(rt[u], 1, maxc, num, 1);
    Add(rt[v], 1, maxc, num, 1);
    Add(rt[f], 1, maxc, num, -1);
    Add(rt[fa[f][0]], 1, maxc, num, -1);
  }
  Dfs2(1);
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}