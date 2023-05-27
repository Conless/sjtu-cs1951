#include <bits/stdc++.h>

using namespace std;  // NOLINT

const int MAXN = 13;

int n, m;
int a[MAXN], d[MAXN][MAXN];
int x[MAXN * MAXN], y[MAXN * MAXN];

auto Dfs(int depth, int exp, int eval) -> bool {
  if (eval == 0) {
    return true;
  }
  if (depth + ceil(eval / 2) > exp) {
    return false;
  }
  for (int t = 1; t <= m; t++) {
    int i = x[t], j = y[t]; // NOLINT
    int next_eval = eval;
    next_eval -= d[i][a[i]] + d[j][a[j]];
    swap(a[i], a[j]);
    next_eval += d[i][a[i]] + d[j][a[j]];
    if (Dfs(depth + 1, exp, next_eval)) {
      swap(a[i], a[j]);
      return true;
    }
    swap(a[i], a[j]);
  }
  return false;
}

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  memset(d, 0x3f, sizeof(d));
  for (int i = 1; i <= m; i++) {
    cin >> x[i] >> y[i];
    d[x[i]][y[i]] = d[y[i]][x[i]] = 1;
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  int eval = 0;
  for (int i = 1; i <= n; i++) {
    d[i][i] = 0;
    eval += d[i][a[i]];
  }
  int l = 0, r = 30, res = -1;  // NOLINT
  for (int i = 0; i <= 30; i++) {
    if (Dfs(0, i, eval)) {
      cout << i << endl;
      return 0;
    }
  }
  return 0;
}