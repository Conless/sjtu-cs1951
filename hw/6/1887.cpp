#include <bits/stdc++.h>

using namespace std;  // NOLINT

const int MAXN = 50;

int n;
int cnt[MAXN];

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a, b; // NOLINT
    cin >> a >> b;
    cnt[a]++;
    cnt[b]++;
  }
  int ans = 0;
  for (int i : cnt) {
    ans += i & 1;
  }
  printf(ans > 2 ? "Impossible\n" : "Possible\n");
  return 0;
}