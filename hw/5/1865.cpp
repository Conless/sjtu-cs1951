#include <bits/stdc++.h>

#define sn segtree[node]
#define sl segtree[sn.lson_]
#define sr segtree[sn.rson_]

#define add(a, b) (a = (a + b) % mod)
#define mul(a, b) (a = (a * b) % mod)

#define int int64_t

using namespace std;  // NOLINT

const int MAXN = 1e5 + 5;

struct Tnode {
  int l_, r_;
  int lson_, rson_;
  int data_{0}, add_{0}, mul_{1};
} segtree[MAXN << 2];

int n, mod;
int a[MAXN];

void Pushup(int node) { sn.data_ = (sl.data_ + sr.data_) % mod; }
void Pushdown(int node) {
  if (sn.mul_ != 1) {
    mul(sl.data_, sn.mul_);
    mul(sl.add_, sn.mul_);
    mul(sl.mul_, sn.mul_);
    mul(sr.data_, sn.mul_);
    mul(sr.add_, sn.mul_);
    mul(sr.mul_, sn.mul_);
    sn.mul_ = 1;
  }
  if (sn.add_ != 0) {
    add(sl.data_, sn.add_ * (sl.r_ - sl.l_ + 1));
    add(sl.add_, sn.add_);
    add(sr.data_, sn.add_ * (sr.r_ - sr.l_ + 1));
    add(sr.add_, sn.add_);
    sn.add_ = 0;
  }
}

void Build(int node, int l, int r, const int *num) {
  sn.l_ = l;
  sn.r_ = r;
  if (l == r) {
    sn.data_ = num[l];
  } else {
    int mid = (l + r) >> 1;
    Build(sn.lson_ = node << 1, l, mid, num);
    Build(sn.rson_ = node << 1 | 1, mid + 1, r, num);
    Pushup(node);
  }
}
void Add(int node, int l, int r, int num) {
  if (sn.l_ > r || sn.r_ < l) {
    return;
  }
  if (sn.l_ >= l && sn.r_ <= r) {
    add(sn.add_, num);
    add(sn.data_, (sn.r_ - sn.l_ + 1) * num);
    return;
  }
  Pushdown(node);
  Add(sn.lson_, l, r, num);
  Add(sn.rson_, l, r, num);
  Pushup(node);
}
void Mul(int node, int l, int r, int num) {
  if (sn.l_ > r || sn.r_ < l) {
    return;
  }
  if (sn.l_ >= l && sn.r_ <= r) {
    mul(sn.mul_, num);
    mul(sn.add_, num);
    mul(sn.data_, num);
    return;
  }
  Pushdown(node);
  Mul(sn.lson_, l, r, num);
  Mul(sn.rson_, l, r, num);
  Pushup(node);
}
auto Query(int node, int l, int r) -> int64_t {
  if (sn.l_ > r || sn.r_ < l) {
    return 0;
  }
  if (sn.l_ >= l && sn.r_ <= r) {
    return sn.data_;
  }
  Pushdown(node);
  return (Query(sn.lson_, l, r) + Query(sn.rson_, l, r)) % mod;
}

auto main() -> signed {
  ios::sync_with_stdio(false);
  cin >> n >> mod;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Build(1, 1, n, a);
  int m;
  cin >> m;
  while ((m--) != 0) {
    int opt, a, b, c;  // NOLINT
    cin >> opt;
    if (opt == 1) {
      cin >> a >> b >> c;
      Mul(1, a, b, c);
    } else if (opt == 2) {
      cin >> a >> b >> c;
      Add(1, a, b, c);
    } else if (opt == 3) {
      cin >> a >> b;
      cout << Query(1, a, b) << '\n';
    }
  }
  return 0;
}