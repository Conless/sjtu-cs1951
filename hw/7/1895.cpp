#include <cstring>
#include <iostream>

#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include <iostream>

namespace conless {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template <typename T, class Compare = std::less<T>>
class priority_queue {  // NOLINT
 public:
  /**
   * TODO constructors
   */
  priority_queue() : rt_(nullptr) {}
  priority_queue(const priority_queue &other) : rt_(TnodeCopy(other.rt_)), siz_(other.siz_) {}
  /**
   * TODO deconstructor
   */
  ~priority_queue() { TnodeClean(rt_); }
  /**
   * TODO Assignment operator
   */
  auto operator=(const priority_queue &other) -> priority_queue & {
    if (this == &other) {
      return *this;
    }
    TnodeClean(rt_);
    rt_ = TnodeCopy(other.rt_);
    siz_ = other.siz_;
    return *this;
  }
  /**
   * get the top of the queue.
   * @return a reference of the top element.
   * throw container_is_empty if empty() returns true;
   */
  auto top() const -> const T & {  // NOLINT
    if (siz_ == 0) {
      // throw Exception("Container is empty");
    }
    return rt_->data_;
  }
  /**
   * TODO
   * push new element to the priority queue.
   */
  void push(const T &e) {  // NOLINT
    auto *tmp = new Tnode(e);
    siz_++;
    try {
      rt_ = TnodeMerge(rt_, tmp);
    } catch (...) {
      delete tmp;
      siz_--;
      throw;
    }
  }
  /**
   * TODO
   * delete the top element.
   * throw container_is_empty if empty() returns true;
   */
  void pop() {  // NOLINT
    if (siz_ == 0) {
      // throw Exception("Container is empty");
    }
    try {
      Tnode *tmp = rt_;
      rt_ = TnodeMerge(rt_->lson_, rt_->rson_);
      delete tmp;
      siz_--;
    } catch (...) {
      throw;
    }
  }
  /**
   * return the number of the elements.
   */
  auto size() const -> size_t { return siz_; }  // NOLINT
  /**
   * check if the container has at least an element.
   * @return true if it is empty, false if it has at least an element.
   */
  auto empty() const -> bool { return siz_ == 0; }  // NOLINT
  /**
   * merge two priority_queues with at least O(logn) complexity.
   * clear the other priority_queue.
   */
  void merge(priority_queue &other) {  // NOLINT
    try {
      rt_ = TnodeMerge(rt_, other.rt_);
      siz_ += other.siz_;
      other.rt_ = nullptr;
      other.siz_ = 0;
    } catch (...) {
      throw;
    }
  }

 private:
  size_t siz_{};

  struct Tnode {
    T data_;
    int dis_;
    Tnode *lson_, *rson_;
    explicit Tnode(const T &data, int _dis = 0) : data_(data), dis_(_dis), lson_(nullptr), rson_(nullptr) {}
  } * rt_;

  auto TnodeCopy(Tnode *org) -> Tnode * {
    auto *tmp = new Tnode(org->data_, org->dis_);
    if (org->lson_) {
      tmp->lson_ = TnodeCopy(org->lson_);
    }
    if (org->rson_) {
      tmp->rson_ = TnodeCopy(org->rson_);
    }
    return tmp;
  }
  void TnodeClean(Tnode *org) {
    if (org == nullptr) {
      return;
    }
    if (org->lson_) {
      TnodeClean(org->lson_);
      org->lson_ = nullptr;
    }
    if (org->rson_) {
      TnodeClean(org->rson_);
      org->rson_ = nullptr;
    }
    delete org;
    org = nullptr;
  }
  auto TnodeMerge(Tnode *nd1, Tnode *nd2) -> Tnode * {
    if (nd1 == nullptr) {
      nd1 = nd2;
    }
    if (nd2 == nullptr) {
      nd2 = nd1;
    }
    if (nd1 != nd2) {
      bool comp;
      try {
        if (Compare()(nd1->data_, nd2->data_)) {
          std::swap(nd1, nd2);
        }
        Tnode *tmp = TnodeMerge(nd1->rson_, nd2);
        if (tmp != nullptr) {
          nd1->rson_ = tmp;
        }
        if (nd1->lson_ == nullptr || nd1->lson_->dis_ < nd1->rson_->dis_) {
          std::swap(nd1->lson_, nd1->rson_);
        }
        nd1->dis_ = nd1->rson_ ? (nd1->rson_->dis_ + 1) : 1;
      } catch (...) {
        throw;
      }
    }
    return nd1;
  }
};

template class priority_queue<int>;

}  // namespace conless

namespace conless {
template <typename Iterator, typename Compare>
void sort(Iterator first, Iterator last, Compare comp) {  // NOLINT
  auto low = first;
  auto high = last - 1;
  if (low - high >= 0) {
    return;
  }
  auto temp = *first;
  while (low != high) {
    while (!comp(*high, temp) && high - low > 0) {
      high--;
    }
    while (!comp(temp, *low) && high - low > 0) {
      low++;
    }
    if (high - low > 0) {
      std::swap(*low, *high);
    }
  }

  std::swap(*first, *low);
  conless::sort(first, low, comp);
  conless::sort(high + 1, last, comp);
}
}  // namespace conless

#endif

using namespace std;  // NOLINT

const int MAXN = 2e5 + 5;

struct Edge0 {
  int u_, v_, w_;
  auto operator==(const Edge0 &x) -> bool { return u_ == x.u_ && v_ == x.v_; }
} edge0[MAXN];
struct Edge1 {
  int u_, v_, w_, next_;
} edge1[MAXN << 1];
struct Edge2 {
  int v_, w_, next_;
} edge2[MAXN << 1];

int n, s, m, cnt0, cnt1, cnt2;
int c[MAXN], dis[MAXN], head1[MAXN], near[MAXN], fa[MAXN], head2[MAXN];

void Dijkstra() {
  memset(dis, 0x5f, sizeof(dis));
  struct Node {
    int v_, dis_;
    auto operator<(const Node &other) const -> bool { return dis_ > other.dis_; }
  };
  conless::priority_queue<Node> q;
  for (int i = 1; i <= s; i++) {
    q.push({c[i], dis[c[i]] = 0});
    near[c[i]] = i;
  }
  while (!q.empty()) {
    auto pru = q.top();
    q.pop();
    if (pru.dis_ != dis[pru.v_]) {
      continue;
    }
    int u = pru.v_;
    for (int i = head1[u]; i != 0; i = edge1[i].next_) {
      int v = edge1[i].v_;
      if (dis[u] + edge1[i].w_ < dis[v]) {
        dis[v] = dis[u] + edge1[i].w_;
        near[v] = near[u];
        q.push({v, dis[v]});
      }
    }
  }
}

void AddEdge1(int u, int v, int w) {
  edge1[++cnt1] = {u, v, w, head1[u]};
  head1[u] = cnt1;
}
void AddEdge2(int u, int v, int w) {
  edge2[++cnt2] = {v, w, head2[u]};
  head2[u] = cnt2;
}

auto Find(int x) -> int { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

void Kruskal() {
  for (int i = 1; i <= s; i++) {
    fa[i] = i;
  }
  conless::sort(edge0 + 1, edge0 + cnt0 + 1, [](const auto &a, const auto &b) { return a.w_ < b.w_; });
  for (int i = 1, j = 0; i <= cnt0 && j < s - 1; i++) {
    if (i > 1 && edge0[i] == edge0[i - 1]) {
      continue;
    }
    int fu = Find(edge0[i].u_);
    int fv = Find(edge0[i].v_);
    if (fu != fv) {
      j++;
      AddEdge2(edge0[i].u_, edge0[i].v_, edge0[i].w_);
      AddEdge2(edge0[i].v_, edge0[i].u_, edge0[i].w_);
      fa[fu] = fv;
    }
  }
}

int h[MAXN], f[MAXN][20], d[MAXN][20];

void Build(int u, int last, int w) {
  h[u] = h[last] + 1;
  f[u][0] = last;
  d[u][0] = w;
  for (int i = 1; i < 20; i++) {
    f[u][i] = f[f[u][i - 1]][i - 1];
    d[u][i] = max(d[u][i - 1], d[f[u][i - 1]][i - 1]);
  }
  for (int i = head2[u]; i != 0; i = edge2[i].next_) {
    int v = edge2[i].v_;
    if (v == last) {
      continue;
    }
    Build(v, u, edge2[i].w_);
  }
}

auto Lca(int u, int v) -> int {
  if (h[u] < h[v]) {
    swap(u, v);
  }
  int ans = 0;
  for (int i = 19; i >= 0; i--) {
    if (h[f[u][i]] >= h[v]) {
      ans = max(ans, d[u][i]);
      u = f[u][i];
    }
  }
  if (u == v) {
    return ans;
  }
  for (int i = 19; i >= 0; i--) {
    if (f[u][i] != f[v][i]) {
      ans = max(ans, max(d[u][i], d[v][i]));
      u = f[u][i];
      v = f[v][i];
    }
  }
  if (f[u][0] == 0 || f[u][0] != f[v][0]) {
    return -1;
  }
  return max(ans, max(d[u][0], d[v][0]));
}

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> n >> s >> m;
  for (int i = 1; i <= s; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;  // NOLINT
    cin >> u >> v >> w;
    AddEdge1(u, v, w);
    AddEdge1(v, u, w);
  }
  Dijkstra();
  for (int i = 1; i <= (m << 1); i += 2) {
    int u = edge1[i].u_;
    int v = edge1[i].v_;
    if (near[u] != near[v]) {
      edge0[++cnt0] = {near[u], near[v], dis[u] + dis[v] + edge1[i].w_};
    }
  }
  Kruskal();
  for (int i = 1; i <= n; i++) {
    if (h[i] == 0) {
      Build(i, 0, 0);
    }
  }
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++) {
    int x, y, b;  // NOLINT
    cin >> x >> y >> b;
    int res = Lca(near[x], near[y]);
    if (res == -1 || res > b) {
      cout << "NIE\n";
    } else {
      cout << "TAK\n";
    }
  }
  return 0;
}