#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

struct node {
    pair<int, int> data;
    int dis;
    node *lson, *rson, *rt;
    node(pair<int, int> _data) : data(_data), dis(0), lson(nullptr), rson(nullptr), rt(this) {}
} * x[MAXN];

int n, m;

node *find(node *u) { return u->rt == u ? u : u->rt = find(u->rt); }

node *merge(node *x, node *y) {
    if (x == nullptr || y == nullptr) {
        if (x == nullptr)
            x = y;
        else
            y = x;
        return x;
    }
    if (x->data > y->data)
        swap(x, y);
    x->rson = merge(x->rson, y);
    x->rson->rt = x->rt;
    if (x->lson == nullptr || x->lson->dis < x->rson->dis)
        swap(x->lson, x->rson);
    x->dis = (x->rson != nullptr) ? x->rson->dis + 1 : 0;
    return x;
}

void erase(node *x) {
    x->rt = merge(x->lson, x->rson);
    if (x->lson)
        x->lson->rt = x->rt;
    if (x->rson)
        x->rson->rt = x->rt;
    x->dis = -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;
        x[i] = new node(make_pair(num, i));
    }
    while (m--) {
        int opt, num1, num2;
        cin >> opt;
        if (opt == 1) {
            cin >> num1 >> num2;
            if (x[num1]->dis == -1 || x[num2]->dis == -1)
                continue;
            node *f1 = find(x[num1]), *f2 = find(x[num2]);
            if (f1 != f2)
                merge(f1, f2);
        } else {
            cin >> num1;
            if (x[num1]->dis == -1)
                cout << -1 << endl;
            else {
                node *u = find(x[num1]);
                cout << u->data.first << endl;
                erase(u);
            }
        }
    }
}