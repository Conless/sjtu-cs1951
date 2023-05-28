#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;  // NOLINT

const int MAXN = 5e3 + 5;

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

#endif

int n, m, s, t, cnt;
int head[MAXN], dis[MAXN], vis[MAXN], pre[MAXN];

struct Edge {
  int u_, v_, w_, next_;
} edge[MAXN << 1];
struct Node {
  int v_, dis_;
  auto operator<(const Node &other) const -> bool { return dis_ > other.dis_; }
};

conless::priority_queue<Node> q;

void Dijkstra() {
  memset(dis, 0x5f, sizeof(dis));
  q.push({s, 0});
  dis[s] = 0;
  while (!q.empty()) {
    auto pru = q.top();
    q.pop();
    if (pru.dis_ != dis[pru.v_]) {
      continue;
    }
    int u = pru.v_;
    for (int i = head[u]; i != 0; i = edge[i].next_) {
      int v = edge[i].v_;
      if (dis[u] + edge[i].w_ < dis[v]) {
        dis[v] = dis[u] + edge[i].w_;
        pre[v] = i;
        q.push({v, dis[v]});
      }
    }
  }
}

void AddEdge(int u, int v, int w) {
  edge[++cnt] = {u, v, w, head[u]};
  head[u] = cnt;
}

auto main() -> int {
  ios::sync_with_stdio(false);
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++) {
    int u, v;  // NOLINT
    cin >> u >> v;
    AddEdge(u, v, 2);
  }
  Dijkstra();
  for (int u = t; u != s; u = edge[pre[u]].u_) {
    edge[pre[u]].w_ = MAXN - 1;
  }
  Dijkstra();
  bool flag = false;
  for (int u = t; u != s; u = edge[pre[u]].u_) {
    if (edge[pre[u]].w_ == 2) {
      edge[pre[u]].w_ = flag ? MAXN : -MAXN * MAXN;
      flag = true;
    } else {
      edge[pre[u]].w_ = 1;
    }
  }
  for (int i = 1; i <= m; i++) {
    if (edge[i].w_ == MAXN - 1) {
      edge[i].w_ = 1;
    }
    if (edge[i].w_ == 2) {
      edge[i].w_ = 1e9;
    }
    cout << edge[i].w_ << '\n';
  }
  return 0;
}