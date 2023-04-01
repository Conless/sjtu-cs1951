#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

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
    const T &top() const {
        // if (siz == 0)
        //     throw container_is_empty();
        return rt->data;
    }
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
        // if (siz == 0)
        //     throw container_is_empty();
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

const int MAXN = 1e5 + 5;

int n, m;
long long ans;
sjtu::priority_queue<int, greater<int>> q;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        q.push(val);
    }
    int addz = (n - 1) % (m - 1) ? ((m - 1) - (n - 1) % (m - 1)) : 0;
    for (int i = 1; i <= addz; i++)
        q.push(0);
    while (q.size() > 1) {
        int sum = 0;
        for (int i = 1; i <= m; i++) {
            sum += q.top();
            q.pop();
        }
        ans += sum;
        q.push(sum);
    }
    cout << ans << endl;
    return 0;
}
