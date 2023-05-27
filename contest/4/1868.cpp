#include <iostream>
#include <cstdio>

using namespace std; // NOLINT

#define sn segtree[node]
#define sls segtree[sn.lson_]
#define srs segtree[sn.rson_]

#define sl segtree[lhs]
#define sr segtree[rhs]

constexpr int MAXN = 2e5 + 5;

struct Tnode {
  int lson_, rson_;
  int cnt_;
} segtree[MAXN * 40];

int n, q, cnt, maxc;
int rt[102], ans[MAXN];

void Pushup(int &node) {
  sn.cnt_ = sls.cnt_ + srs.cnt_;
  if (sn.cnt_ == 0) {
    node = 0;
  }
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

void Merge(int &lhs, int &rhs, int l, int r, int x, int y) {
  if (rhs == 0) {
    return;
  }
  if (lhs == 0) {
    if (l >= x && r <= y) {
      lhs = rhs;
      rhs = 0;
      return;
    }
    lhs = ++cnt;
  }
  int mid = (l + r) >> 1; 
  if (x <= mid) {
    Merge(sl.lson_, sr.lson_, l, mid, x, min(y, mid));
  }
  if (y > mid) {
    Merge(sl.rson_, sr.rson_, mid + 1, r, max(x, mid + 1), y);
  }
  Pushup(lhs);
  Pushup(rhs);
}

void Calc(int node, int l, int r, int col) {
  if (node == 0) {
    return;
  }
  if (l == r) {
    ans[l] = col;
    return;
  }
  int mid = (l + r) >> 1;
  Calc(sn.lson_, l, mid, col);
  Calc(sn.rson_, mid + 1, r, col);
}

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int col;
    cin >> col;
    maxc = max(maxc, col);
    Add(rt[col], 1, n, i);
  }
  cin >> q;
  for (int i = 1; i <= q; i++) {
    int l, r, x, y;  // NOLINT
    cin >> l >> r >> x >> y;
    if (x == y) {
      continue;
    }
    Merge(rt[y], rt[x], 1, n, l, r);
  }
  for (int i = 1; i <= maxc; i++) {
    Calc(rt[i], 1, n, i);
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
  return 0;
}