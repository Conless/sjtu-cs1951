#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e6 + 5;

struct Edge {
  int v_, next_;
} edge[MAXN];

int n, m, cnt, tim, tot;
int head[MAXN], low[MAXN], dfn[MAXN];
stack<int> st;
vector<int> bcc[MAXN];

void AddEdge(int u, int v) {
  cnt++;
  edge[cnt].v_ = v;
  edge[cnt].next_ = head[u];
  head[u] = cnt;
}

void Tarjan(int u, int las) {
  int siz = 0;
  dfn[u] = low[u] = ++tim;
  st.push(u);
  for (int i = head[u]; i; i = edge[i].next_) {
    int v = edge[i].v_;
    if (v == las) {
      continue;
    }
    if (dfn[v] == 0) {
      siz++;
      Tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        tot++;
        int tp;
        do {
          tp = st.top();
          bcc[tot].push_back(tp);
          st.pop();
        } while (tp != v);
        bcc[tot].push_back(u);
      }
    } else {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if ((las == 0) && (siz == 0)) {
    bcc[++tot].push_back(u);
  }
}

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u;
    int v;
    cin >> u >> v;
    AddEdge(u, v);
    AddEdge(v, u);
  }
  for (int i = 1; i <= n; i++) {
    if (dfn[i] == 0) {
      Tarjan(i, 0);
    }
  }
  printf("%d\n", tot);
  for (int i = 1; i <= tot; i++) {
    printf("%zu ", bcc[i].size());
    for (auto u : bcc[i]) {
      printf("%d ", u);
    }
    printf("\n");
  }
  return 0;
}