#include <bits/stdc++.h>

using namespace std;  // NOLINT

int r, c, m;

namespace case1 {

const int MAXN = 2e2 + 2;
const int MAXM = 1e3 + 2;

int p[MAXN][MAXN];
int cnt[MAXN][MAXN][MAXM], sum[MAXN][MAXN][MAXM], num[MAXN][MAXN][MAXM];  // NOLINT

auto Calc(int a[MAXN][MAXN][MAXM], int x1, int y1, int x2, int y2, int k) -> int {
  return a[x2][y2][k] - a[x2][y1 - 1][k] - a[x1 - 1][y2][k] + a[x1 - 1][y1 - 1][k];
}

void Solve() {
  int tmp[MAXM];
  for (int i = 1; i <= r; i++) {
    memset(tmp, 0, sizeof(tmp));
    for (int j = 1; j <= c; j++) {
      cin >> p[i][j];
      tmp[p[i][j]]++;
      for (int k = MAXM - 2; k > 0; k--) {
        cnt[i][j][k] = cnt[i - 1][j][k] + tmp[k];
        num[i][j][k] = num[i][j][k + 1] + cnt[i][j][k];
        sum[i][j][k] = sum[i][j][k + 1] + cnt[i][j][k] * k;
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    int x1, y1, x2, y2, h;  // NOLINT
    cin >> x1 >> y1 >> x2 >> y2 >> h;
    int l = 1, r = 1000, res = -1;  // NOLINT
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (Calc(sum, x1, y1, x2, y2, mid) >= h) {
        l = mid + 1;
        res = mid;
      } else {
        r = mid - 1;
      }
    }
    if (res == -1) {
      cout << "Impossible\n";
    } else {
      cout << Calc(num, x1, y1, x2, y2, res) - (Calc(sum, x1, y1, x2, y2, res) - h) / res << '\n';
    }
  }
}

}  // namespace case1

namespace case2 {

#define sn segtree[node]
#define so segtree[old]
#define sl segtree[lhs]
#define sr segtree[rhs]
#define sls segtree[sn.lson_]
#define srs segtree[sn.rson_]

const int MAXN = 5e5;

struct Tnode {
  int lson_, rson_;
  int sum_, cnt_;
} segtree[MAXN * 40];

int cnt;

void Pushup(int node) {
  sn.sum_ = sls.sum_ + srs.sum_;
  sn.cnt_ = sls.cnt_ + srs.cnt_;
}

void Insert(int &node, int old, int l, int r, int pos) {
  node = ++cnt;
  sn.sum_ = so.sum_;
  sn.cnt_ = so.cnt_;
  sn.lson_ = so.lson_;
  sn.rson_ = so.rson_;
  if (l == r) {
    sn.sum_ += pos;
    sn.cnt_++;
  } else {
    int mid = (l + r) >> 1;
    if (pos <= mid) {
      Insert(sn.lson_, so.lson_, l, mid, pos);
    } else {
      Insert(sn.rson_, so.rson_, mid + 1, r, pos);
    }
    Pushup(node);
  }
}

auto Query(int lhs, int rhs, int l, int r, int req, int &sum, int &cnt) {
  if (l == r) {
    sum = sr.sum_ - sl.sum_;
    cnt = sr.cnt_ - sl.cnt_;
    return l;
  }
  int sumr = segtree[sr.rson_].sum_ - segtree[sl.rson_].sum_;
  int mid = (l + r) >> 1;
  if (sumr < req) {
    int suml, cntl, cntr = segtree[sr.rson_].cnt_ - segtree[sl.rson_].cnt_; // NOLINT
    int res = Query(sl.lson_, sr.lson_, l, mid, req - sumr, suml, cntl);
    sum = suml + sumr;
    cnt = cntl + cntr;
    return res;
  }
  return Query(sl.rson_, sr.rson_, mid + 1, r, req, sum, cnt);
}

int rt[MAXN], p[MAXN];

void Solve() {
  int maxp = 0;
  for (int i = 1; i <= c; i++) {
    cin >> p[i];
    maxp = max(maxp, p[i]);
  }
  for (int i = 1; i <= c; i++) {
    Insert(rt[i], rt[i - 1], 1, maxp, p[i]);
  }
  for (int i = 1; i <= m; i++) {
    int tmp, l, r, h, cnt, sum;  // NOLINT
    cin >> tmp >> l >> tmp >> r >> h;
    int res = Query(rt[l - 1], rt[r], 1, maxp, h, sum, cnt);
    if (sum < h) {
      cout << "Impossible\n";
    } else {
      cout << cnt - (sum - h) / res << '\n';
    }
  }
}
}  // namespace case2

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> r >> c >> m;
  if (r != 1) {
    case1::Solve();
  } else {
    case2::Solve();
  }
  return 0;
}