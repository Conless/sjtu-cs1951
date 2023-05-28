#include <climits>
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

void Dijkstra() {
  memset(dis, 0x5f, sizeof(dis));
  dis[u] = 0;
  for (int i = 1; i < n; i++) {
    int k = 0;
    int mindis = INT_MAX;
    for (int j = 1; j <= n; j++) {
      if (vis[j] == 0 && dis[j] < mindis) {
        mindis = dis[j];
        k = j;
      }
    }
    vis[k] = 1;
    for (int e = head[k]; e != 0; e = edge[e].next_) {
      int v = edge[e].v_;
      if (vis[v] == 0 && dis[v] > dis[k] + edge[e].w_) {
        dis[v] = dis[k] + edge[e].w_;
      }
    }
    // cout << k << '\n';
    // for (int j = 1; j <= n; j++) {
    //   cout << dis[j] << ' ';
    // }
    // cout << '\n';
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