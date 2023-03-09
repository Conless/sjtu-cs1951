#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

enum color { RED, BLACK };

struct tnode {
    color col;
    int key, data, siz;
    int lson, rson, parent;
    tnode() { col = BLACK, key = data = lson = rson = parent = 0; }
} node[MAXN];

int n, cnt, rt = 1;

void fixup(int u);

void insert(int u, int key, int data) {
    if (!cnt) {
        cnt++;
        node[rt].col = RED;
        node[rt].key = key;
        node[rt].data = data;
        return;
    }
    int &tmp = node[u].key < key ? node[u].rson : node[u].lson;
    if (!tmp) {
        tmp = ++cnt;
        node[tmp].col = RED;
        node[tmp].key = key;
        node[tmp].data = data;
        node[tmp].parent = u;
        fixup(tmp);
    } else {
        insert(tmp, key, data);
    }
}

void LeftRotate(int u) {
    if (u != rt) {
        int ltag = node[node[u].parent].lson == u;
        if (ltag)
            node[node[u].parent].lson = node[u].rson;
        else
            node[node[u].parent].rson = node[u].rson;
    }
    int rson = node[u].rson;
    node[rson].parent = node[u].parent;

    node[u].rson = node[rson].lson;
    if (node[rson].lson)
        node[node[rson].lson].parent = u;

    node[rson].lson = u;
    node[u].parent = rson;
}

void RightRotate(int u) {
    if (u != rt) {
        int ltag = node[node[u].parent].lson == u;
        if (ltag)
            node[node[u].parent].lson = node[u].lson;
        else
            node[node[u].parent].rson = node[u].lson;
    }
    int lson = node[u].lson;
    node[lson].parent = node[u].parent;

    node[u].lson = node[lson].rson;
    if (node[lson].rson)
        node[node[lson].rson].parent = u;

    node[lson].rson = u;
    node[u].parent = lson;
}

void fixup(int u) {
    if (u == rt)
        return;
    int pr = node[u].parent;
    if (node[pr].col == BLACK)
        return;
    if (pr == rt) {
        node[pr].col = BLACK;
        return;
    }
    int gpr = node[pr].parent;
    int ltag = node[pr].lson == u, gltag = node[gpr].lson == pr;
    int unc = gltag ? node[gpr].rson : node[gpr].lson;
    if (node[unc].col == RED) {
        node[gpr].col = RED;
        node[pr].col = node[unc].col = BLACK;
        fixup(gpr);
    } else {
        if (gltag) {
            if (!ltag)
                LeftRotate(pr);
            RightRotate(gpr);
        } else {
            if (ltag)
                RightRotate(pr);
            LeftRotate(gpr);
        }
        swap(node[gpr].col, node[node[gpr].parent].col);
    }
}

void output() {
    for (int i = 1; i <= cnt; i++) {
        cout << i << ' ';
        cout << (node[i].col == RED ? 'R' : 'B') << ' ';
        printf("%d %d %d %d\n", node[i].lson, node[i].rson, node[i].parent, node[i].key);
    }
}

int main() {
    while (true) {
        int key, data = 0;
        cin >> key;
        insert(rt, key, data);
        output();
    }
}