#include <bits/stdc++.h>

#define sn segtree[node]
#define sls segtree[sn.lson_]
#define srs segtree[sn.rson_]

using namespace std;  // NOLINT

struct Bucket {
  int cnt_[26];
  Bucket() { memset(cnt_, 0, sizeof(cnt_)); }
  Bucket(const Bucket &other) { memcpy(cnt_, other.cnt_, sizeof(other.cnt_)); }
  auto operator+(const Bucket &other) -> Bucket {
    Bucket res;
    for (int i = 0; i < 26; i++) {
      res.cnt_[i] = cnt_[i] + other.cnt_[i];
    }
    return res;
  }
  auto operator+=(const Bucket &other) -> Bucket & { return *this = *this + other; }
};

auto SeparateTo(const Bucket &org, int siz) -> pair<Bucket, Bucket> {
  pair<Bucket, Bucket> res;
  for (int i = 0; i < 26; i++) {
    if (siz > 0) {
      if (org.cnt_[i] <= siz) {
        siz -= org.cnt_[i];
        res.first.cnt_[i] = org.cnt_[i];
      } else {
        res.first.cnt_[i] = siz;
        res.second.cnt_[i] = org.cnt_[i] - siz;
        siz = 0;
      }
    } else {
      res.second.cnt_[i] = org.cnt_[i];
    }
  }
  return res;
}

const int MAXN = 1e5 + 5;

struct Tnode {
  int lson_, rson_;
  int size_, tag_;
  Bucket data_;
} segtree[MAXN << 2];

void Pushup(int node) { sn.data_ = sls.data_ + srs.data_; }

void Pushdown(int node) {
  if (sn.tag_ == 0) {
    return;
  }
  if (sn.tag_ > 0) {
    auto res = SeparateTo(sn.data_, sls.size_);
    sls.data_ = res.first;
    sls.tag_ = sn.tag_;
    srs.data_ = res.second;
    srs.tag_ = sn.tag_;
    sn.tag_ = 0;
  } else {
    auto res = SeparateTo(sn.data_, srs.size_);
    sls.data_ = res.second;
    sls.tag_ = sn.tag_;
    srs.data_ = res.first;
    srs.tag_ = sn.tag_;
    sn.tag_ = 0;
  }
}

void Build(int node, int l, int r, const char *str) {
  sn.size_ = r - l + 1;
  if (l == r) {
    sn.data_.cnt_[str[l] - 'a']++;
  } else {
    int mid = (l + r) >> 1;
    Build(sn.lson_ = node << 1, l, mid, str);
    Build(sn.rson_ = node << 1 | 1, mid + 1, r, str);
    Pushup(node);
  }
}

auto Calc(int node, int l, int r, int x, int y) -> Bucket {
  if (l >= x && r <= y) {
    return sn.data_;
  }
  Pushdown(node);
  Bucket res;
  int mid = (l + r) >> 1;
  if (x <= mid) {
    res += Calc(sn.lson_, l, mid, x, y);
  }
  if (y > mid) {
    res += Calc(sn.rson_, mid + 1, r, x, y);
  }
  return res;
}

void Modify(int node, int l, int r, int x, int y, int opt, const Bucket &sum) {
  if (l >= x && r <= y) {
    sn.data_ = sum;
    sn.tag_ = opt;
    return;
  }
  Pushdown(node);
  int mid = (l + r) >> 1;
  if (y <= mid) {
    Modify(sn.lson_, l, mid, x, y, opt, sum);
  } else if (x > mid) {
    Modify(sn.rson_, mid + 1, r, x, y, opt, sum);
  } else {
    if (opt > 0) {
      auto res = SeparateTo(sum, mid - x + 1);
      Modify(sn.lson_, l, mid, x, mid, opt, res.first);
      Modify(sn.rson_, mid + 1, r, mid + 1, y, opt, res.second);
    } else {
      auto res = SeparateTo(sum, y - mid);
      Modify(sn.lson_, l, mid, x, mid, opt, res.second);
      Modify(sn.rson_, mid + 1, r, mid + 1, y, opt, res.first);
    }
  }
  Pushup(node);
}

void Query(int node, int l, int r, char *ans) {
  if (l == r) {
    for (int i = 0; i < 26; i++) {
      if (sn.data_.cnt_[i]) {
        ans[l] = 'a' + i;
        break;
      }
    }
    return;
  }
  Pushdown(node);
  int mid = (l + r) >> 1;
  Query(sn.lson_, l, mid, ans);
  Query(sn.rson_, mid + 1, r, ans);
}

int n, m;
char str[MAXN], ans[MAXN];

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  cin >> (str + 1);
  Build(1, 1, n, str);
  for (int i = 1; i <= m; i++) {
    int opt, l, r;  // NOLINT
    cin >> l >> r >> opt;
    auto res = Calc(1, 1, n, l, r);
    if (opt == 1) {
      Modify(1, 1, n, l, r, 1, res);
    } else {
      Modify(1, 1, n, l, r, -1, res);
    }
  }
  Query(1, 1, n, ans);
  ans[n + 1] = '\0';
  cout << (ans + 1) << '\n';
  return 0;
}