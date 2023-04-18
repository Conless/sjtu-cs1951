#include <cstdio>
#include <cstring>
#include <iostream>

// #include <queue> // temp
// #include <algorithm> // temp

using namespace std;

// #define int long long

const int MAXN = 2e5 + 5;

class QuickRead {

  public:
    inline char gc() {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
    }

    template <typename _Tp> inline QuickRead &operator>>(_Tp &num) {
        static char ch, sgn;
        ch = gc();
        sgn = 0;
        for (; !isdigit(ch); ch = gc()) {
            if (ch == -1)
                return *this;
            sgn |= (ch == '-');
        }
        num = 0;
        for (num = 0; isdigit(ch); ch = gc())
            num = num * 10 + (ch ^ '0');
        sgn && (num = -num);
        return *this;
    }
} qin;

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template <typename T, class Compare = std::less<T>> class priority_queue {
  public:
    /**
     * TODO constructors
     */
    priority_queue() : rt(nullptr), siz(0) {}
    priority_queue(const priority_queue &other) : rt(tnode_copy(other.rt)), siz(other.siz) {}
    /**
     * TODO deconstructor
     */
    ~priority_queue() { tnode_clean(rt); }
    /**
     * TODO Assignment operator
     */
    priority_queue &operator=(const priority_queue &other) {
        if (this == &other)
            return *this;
        tnode_clean(rt);
        rt = tnode_copy(other.rt);
        siz = other.siz;
        return *this;
    }
    /**
     * get the top of the queue.
     * @return a reference of the top element.
     * throw container_is_empty if empty() returns true;
     */
    const T &top() const { return rt->data; }
    /**
     * TODO
     * push new element to the priority queue.
     */
    void push(const T &e) {
        tnode *tmp = new tnode(e);
        siz++;
        try {
            rt = tnode_merge(rt, tmp);
        } catch (...) {
            delete tmp;
            siz--;
            throw;
        }
    }
    /**
     * TODO
     * delete the top element.
     * throw container_is_empty if empty() returns true;
     */
    void pop() {
        try {
            tnode *tmp = rt;
            rt = tnode_merge(rt->lson, rt->rson);
            delete tmp;
            siz--;
        } catch (...) {
            throw;
        }
    }
    /**
     * return the number of the elements.
     */
    size_t size() const { return siz; }
    /**
     * check if the container has at least an element.
     * @return true if it is empty, false if it has at least an element.
     */
    bool empty() const { return siz == 0; }
    /**
     * merge two priority_queues with at least O(logn) complexity.
     * clear the other priority_queue.
     */
    void merge(priority_queue &other) {
        try {
            rt = tnode_merge(rt, other.rt);
            siz += other.siz;
            other.rt = nullptr;
            other.siz = 0;
        } catch (...) {
            throw;
        }
    }

  private:
    size_t siz;

    struct tnode {
        T data;
        int dis;
        tnode *lson, *rson;
        tnode(const T &_data, int _dis = 0) : data(_data), dis(_dis), lson(nullptr), rson(nullptr) {}
    } * rt;

    tnode *tnode_copy(tnode *org) {
        tnode *tmp = new tnode(org->data, org->dis);
        if (org->lson)
            tmp->lson = tnode_copy(org->lson);
        if (org->rson)
            tmp->rson = tnode_copy(org->rson);
        return tmp;
    }
    void tnode_clean(tnode *org) {
        if (org == nullptr)
            return;
        if (org->lson) {
            tnode_clean(org->lson);
            org->lson = nullptr;
        }
        if (org->rson) {
            tnode_clean(org->rson);
            org->rson = nullptr;
        }
        delete org;
        org = nullptr;
    }
    tnode *tnode_merge(tnode *nd1, tnode *nd2) {
        if (nd1 == nullptr)
            nd1 = nd2;
        if (nd2 == nullptr)
            nd2 = nd1;
        if (nd1 != nd2) {
            bool comp;
            try {
                if (Compare()(nd1->data, nd2->data))
                    std::swap(nd1, nd2);
                tnode *tmp = tnode_merge(nd1->rson, nd2);
                if (tmp != nullptr)
                    nd1->rson = tmp;
                if (nd1->lson == nullptr || nd1->lson->dis < nd1->rson->dis)
                    std::swap(nd1->lson, nd1->rson);
                nd1->dis = nd1->rson ? (nd1->rson->dis + 1) : 1;
            } catch (...) {
                throw;
            }
        }
        return nd1;
    }
};

template class priority_queue<int>;

} // namespace sjtu

struct Edge2 {
    int u, v, h;
} edge2[MAXN << 1];

Edge2 temp[MAXN << 1];

template <class Comp> void sort(Edge2 *a, int l, int r, Comp cmp) {
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    sort(a, l, mid, cmp);
    sort(a, mid + 1, r, cmp);
    int i, j, k = l;
    for (i = l, j = mid + 1; i <= mid && j <= r;) {
        if (cmp(a[i], a[j]))
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    if (i <= mid) {
        while (k <= r)
            temp[k++] = a[i++];
    } else {
        while (k <= r)
            temp[k++] = a[j++];
    }
    for (k = l; k <= r; k++)
        a[k] = temp[k];
}

sjtu::priority_queue<pair<int, int>> q;

struct Edge1 {
    int v, w, next;
} edge1[MAXN << 2];

int n, m, cnt;
int head[MAXN << 1], vis[MAXN << 1], dis[MAXN << 1], mind[MAXN << 1], par[MAXN << 1][21];
int node_cnt;
int fa[MAXN << 1], val[MAXN << 1];

void clear() {
    cnt = node_cnt = 0;
    memset(head, 0, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x7f, sizeof(dis));
    memset(mind, 0, sizeof(mind));
    memset(par, 0, sizeof(par));
    memset(fa, 0, sizeof(fa));
    memset(val, 0, sizeof(val));
}

void add_edge(int u, int v, int w) {
    cnt++;
    edge1[cnt] = {v, w, head[u]};
    head[u] = cnt;
}

void dijkstra() {
    q.push({0, 1});
    dis[1] = 0;
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        vis[u] = 1;
        for (int i = head[u]; i; i = edge1[i].next) {
            int v = edge1[i].v;
            if (dis[u] + edge1[i].w < dis[v]) {
                dis[v] = dis[u] + edge1[i].w;
                q.push({-dis[v], v});
            }
        }
    }
}

void dfs(int u, int last) {
    vis[u] = 1;
    mind[u] = dis[u];
    par[u][0] = last;
    for (int i = 1; i <= 20; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = edge1[i].next) {
        int v = edge1[i].v;
        if (v == last)
            continue;
        dfs(v, u);
        mind[u] = min(mind[u], mind[v]);
    }
}

inline int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

void kruskal() {
    sort(edge2, 1, m, [](const Edge2 &a, const Edge2 &b) { return a.h > b.h; });
    // std::sort(edge2 + 1, edge2 + m + 1, [](const Edge2 &a, const Edge2 &b) { return a.h > b.h; });
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    node_cnt = n;
    cnt = 0;
    memset(head, 0, sizeof(head));
    int j;
    for (int i = 1, j = 0; i <= m && j < n - 1; i++) {
        int fu = find(edge2[i].u), fv = find(edge2[i].v);
        if (fu != fv) {
            val[++node_cnt] = edge2[i].h;
            fa[fu] = fa[fv] = fa[node_cnt] = node_cnt;
            add_edge(node_cnt, fu, 0);
            add_edge(node_cnt, fv, 0);
            j++;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    int T;
    qin >> T;
    while (T--) {
        clear();
        qin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int u, v, w, h;
            qin >> u >> v >> w >> h;
            add_edge(u, v, w);
            add_edge(v, u, w);
            edge2[i] = {u, v, h};
        }
        dijkstra();
        kruskal();
        dfs(node_cnt, 0);
        int q, k, s, ans = 0;
        qin >> q >> k >> s;
        while (q--) {
            int v, p;
            qin >> v >> p;
            v = (v + k * ans - 1) % n + 1;
            p = (p + k * ans) % (s + 1);
            for (int i = 20; i >= 0; i--) {
                if (par[v][i] && val[par[v][i]] > p)
                    v = par[v][i];
            }
            cout << (ans = mind[v]) << endl;
        }
    }
    return 0;
}