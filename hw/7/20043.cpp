#include <cstring>
#include <iostream>
#include <vector>

using namespace std;  // NOLINT

const int MAXN = 1e5 + 5;

struct Edge {
  int v_, next_;
} edge[MAXN * 10];

int n, m, cnt, tim, tot;
int head[MAXN], low[MAXN], dfn[MAXN], quan[MAXN], cut_quan[MAXN], cut[MAXN];
vector<int> bcc[MAXN];
int top;
int st[MAXN];

void AddEdge(int u, int v) {
  cnt++;
  edge[cnt].v_ = v;
  edge[cnt].next_ = head[u];
  head[u] = cnt;
}

void Tarjan(int u, int las) {
  int siz = 0;
  dfn[u] = low[u] = ++tim;
  st[++top] = u;
  for (int i = head[u]; i != 0; i = edge[i].next_) {
    int v = edge[i].v_;
    if (v == las) {
      continue;
    }
    if (dfn[v] == 0) {
      siz++;
      Tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        cut[u] = static_cast<int>(las != 0);
        tot++;
        int tp;
        do {
          tp = st[top];
          bcc[tot].push_back(tp);
          top--;
        } while (tp != v);
        bcc[tot].push_back(u);
      }
    } else {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (las == 0 && siz >= 2) {
    cut[u] = 1;
  }
}

auto main() -> int {
  ios::sync_with_stdio(false);
  int t = 0;
  while (true) {
    n = m = cnt = tim = tot = top = 0;
    memset(head, 0, sizeof(head));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(quan, 0, sizeof(quan));
    memset(cut_quan, 0, sizeof(cut_quan));
    memset(cut, 0, sizeof(cut));
    cin >> m;
    if (m == 0) {
      break;
    }
    for (int i = 1; i <= m; i++) {
      int u;
      int v;
      cin >> u >> v;
      n = max(n, max(u, v));
      AddEdge(u, v);
      AddEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
      if (dfn[i] == 0) {
        Tarjan(i, 0);
      }
      // cout << cut[i] << ' ';
    }
    for (int i = 1; i <= tot; i++) {
      for (auto u : bcc[i]) {
        // cout << u << ' ';
        quan[i]++;
        cut_quan[i] += cut[u];
      }
      bcc[i].clear();
      // cout << cut_quan[i] << '\n';
    }
    int ans1 = 0;
    uint64_t ans2 = 1;
    for (int i = 1; i <= tot; i++) {
      if (cut_quan[i] == 0) {
        ans1 += 2;
        ans2 *= quan[i] * (quan[i] - 1) / 2;
      } else if (cut_quan[i] == 1) {
        ans1++;
        ans2 *= quan[i] - 1;
      }
    }
    cout << "Case " << ++t << ": " << ans1 << ' ' << ans2 << '\n';
  }
  return 0;
}