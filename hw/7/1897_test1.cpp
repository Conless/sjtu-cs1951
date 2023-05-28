#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;  // NOLINT

const int MAXN = 1e5 + 5;

int n, m, u;
int head[MAXN], dis[MAXN], vis[MAXN];

struct Edge {
  int v_, w_, next_;
} edge[MAXN << 1];

struct Comp {
  auto operator()(int a, int b) const -> bool { return dis[a] > dis[b]; }
};
priority_queue<int, vector<int>, Comp> q;

void Dijkstra() {
  memset(dis, 0x5f, sizeof(dis));
  q.push(u);
  dis[u] = 0;
  while (!q.empty()) {
    int v = q.top();
    q.pop();
    vis[v] = 0;
    for (int i = head[v]; i != 0; i = edge[i].next_) {
      int to = edge[i].v_;
      if (dis[v] + edge[i].w_ < dis[to]) {
        dis[to] = dis[v] + edge[i].w_;
        if (vis[to] == 0) {
          q.push(to);
          vis[to] = 1;
        }
      }
    }
  }
}

auto main() -> int {
  scanf("%d%d%d", &n, &m, &u);
  for (int i = 1; i <= m; i++) {
    int a;
    scanf("%d%d%d", &a, &edge[i].v_, &edge[i].w_);
    edge[i].next_ = head[a];
    head[a] = i;
  }
  Dijkstra();
  for (int i = 1; i <= n; i++) {
    printf("%d ", dis[i]);
  }
  printf("\n");
  return 0;
}