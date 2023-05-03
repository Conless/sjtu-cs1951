#include <bits/stdc++.h>

#define sn segtree[node]
#define sls segtree[sn.lson_]
#define srs segtree[sn.rson_]

#define sl segtree[lhs]
#define sr segtree[rhs]

#define int int64_t

using namespace std;  // NOLINT

constexpr int MAXN = 2e5 + 5;
constexpr int MAXM = MAXN * 40;

struct Tnode {
  int lson_, rson_;
  int cnt_;
} segtree[MAXM];

int n, m, cnt, ans;
int rt[MAXN];

void Pushup(int node) {
  sn.cnt_ = sls.cnt_ + srs.cnt_;
}

void Add(int &node, int l, int r, int pos) {
  if (node == 0) {
    node = ++cnt;
  }
  if (l == r) {
    sn.cnt_++;
    return;
  }
  int mid = (l + r) >> 1;
  if (pos <= mid) {
    Add(sn.lson_, l, mid, pos);
  } else {
    Add(sn.rson_, mid + 1, r, pos);
  }
  Pushup(node);
}

auto Merge(int lhs, int rhs, int l, int r, int &res) -> int {
  if (lhs == 0 || rhs == 0) {
    return lhs | rhs;
  }
  if (sl.rson_ && sr.lson_) {
    res += segtree[sl.rson_].cnt_ * segtree[sr.lson_].cnt_;
  }
  int mid = (l + r) >> 1;
  sl.lson_ = Merge(sl.lson_, sr.lson_, l, mid, res);
  sl.rson_ = Merge(sl.rson_, sr.rson_, mid + 1, r, res);
  Pushup(lhs);
  return lhs;
}

int num[MAXN], lson[MAXN], rson[MAXN];

void Dfs(int u) {
  cin >> num[u];
  if (num[u] == 0) {
    Dfs(lson[u] = ++m);
    Dfs(rson[u] = ++m);
    int res = 0;
    int siz = segtree[rt[lson[u]]].cnt_ * segtree[rt[rson[u]]].cnt_;
    rt[u] = Merge(rt[lson[u]], rt[rson[u]], 1, n, res);
    ans += min(res, siz - res);
  } else {
    Add(rt[u], 1, n, num[u]);
  }
}

auto main() -> signed {
  ios::sync_with_stdio(false);
  cin >> n;
  Dfs(++m);
  cout << ans << '\n';
  return 0;
}