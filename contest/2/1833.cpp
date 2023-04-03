#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 3e5 + 5;

struct mouse {
    int x, t, w;
    int x_minus, x_plus;
    bool operator<(const mouse &x) const { return t < x.t; }
} m[MAXN];

mouse temp[MAXN];

template <class Compare> void sort(mouse *a, int l, int r, Compare comp) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    sort(a, l, mid, comp);
    sort(a, mid + 1, r, comp);
    int i, j, k = l;
    for (i = l, j = mid + 1; i <= mid && j <= r;) {
        if (comp(a[i], a[j]))
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

int n, v;

#define sn segTree[node]
class SegmentTree {
  private:
    struct tnode {
        int l, r;
        int lson, rson;
        long long data;
    } segTree[MAXN << 2];

  public:
    void build(int node, int l, int r) {
        sn.l = l;
        sn.r = r;
        if (l < r) {
            int mid = (l + r) >> 1;
            build(sn.lson = node << 1, l, mid);
            build(sn.rson = node << 1 | 1, mid + 1, r);
        }
    }
    void edit(int node, int pos, long long val) {
        if (sn.r < pos || sn.l > pos)
            return;
        if (sn.l == sn.r)
            sn.data = val;
        else {
            edit(sn.lson, pos, val);
            edit(sn.rson, pos, val);
            sn.data = max(segTree[sn.lson].data, segTree[sn.rson].data);
        }
    }
    long long query(int node, int l, int r) {
        if (sn.r < l || sn.l > r)
            return 0;
        if (sn.l >= l && sn.r <= r)
            return sn.data;
        return max(query(sn.lson, l, r), query(sn.rson, l, r));
    }
} tree_minus;

class {
  public:
    bool operator()(const mouse &a, const mouse &b) { return a.x_minus > b.x_minus; }
} cp1;
class {
  public:
    bool operator()(const mouse &a, const mouse &b) { return a.x_plus != b.x_plus ? a.x_plus < b.x_plus : a.x_minus < b.x_minus; }
} cp2;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> v;
    for (int i = 1; i <= n; i++) {
        cin >> m[i].x >> m[i].t >> m[i].w;
        m[i].x_minus = m[i].x - m[i].t * v;
        m[i].x_plus = m[i].x + m[i].t * v;
    }
    sort(m, 1, n, cp1);
    int sum = 0, las = m[1].x_minus;
    m[1].x_minus = ++sum;
    for (int i = 2; i <= n; i++) {
        if (m[i].x_minus != las)
            ++sum;
        las = m[i].x_minus;
        m[i].x_minus = sum;
    }
    tree_minus.build(1, 1, sum);
    sort(m, 1, n, cp2);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        long long res = m[i].w + tree_minus.query(1, 1, m[i].x_minus);
        ans = max(res, ans);
        tree_minus.edit(1, m[i].x_minus, res);
    }
    cout << ans << endl;
    return 0;
}