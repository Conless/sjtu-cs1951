#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;  // NOLINT

const int MAXN = 1e5 + 5;

int n, m, s, t, cnt;
int head[MAXN], dis[MAXN], vis[MAXN], known[MAXN];

struct Edge {
  int v_, w_, next_;
} edge[MAXN << 1];

priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> q;

void Dijkstra() {
  memset(dis, 0x5f, sizeof(dis));
  q.push({0, s});
  dis[s] = 0;
  while (!q.empty()) {
    auto pru = q.top();
    q.pop();
    if (pru.first != dis[pru.second]) {
      continue;
    }
    int u = pru.second;
    for (int i = head[u]; i != 0; i = edge[i].next_) {
      int v = edge[i].v_;
      if (dis[u] + edge[i].w_ < dis[v]) {
        dis[v] = dis[u] + edge[i].w_;
        q.push({dis[v], v});
      }
    }
  }
}

void AddEdge(int u, int v, int w) {
  edge[++cnt] = {v, w, head[u]};
  head[u] = cnt;
}

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> n >> m >> s;
  for (int i = 1; i <= m; i++) {
    int u, v, w; // NOLINT
    cin >> u >> v >> w;
    AddEdge(u, v, w);
  }
  Dijkstra();
  for (int i = 1; i <= n; i++) {
    cout << dis[i] << ' ';
  }
  cout << '\n';
  return 0;
}