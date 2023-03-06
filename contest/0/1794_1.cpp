#include <iostream>

using namespace std;

const int MAXN = 2e5 + 5;

int cnt[2];
int tr[2][MAXN][26], fail[2][MAXN << 3];
int ed[MAXN], st[MAXN];

void insert(const string &p) {
    int u[2] = {0};
    for (auto ch : p) {
        for (int i : {0, 1}) {
            if (!tr[i][u[i]][ch - 'a'])
                tr[i][u[i]][ch - 'a'] = ++cnt[i];
            u[i] = tr[i][u[i]][ch - 'a'];
        }
    }
    ed[u[0]]++;
    st[u[1]]++;
}

void build(int opt) {
    int head = 0, tail = 0;
    int que[MAXN];
    for (int i = 0; i < 26; i++)
        if (tr[opt][0][i])
            que[++tail] = tr[opt][0][i];
    while (head != tail) {
        int u = que[++head];
        
    }
    
}

int main() { return 0; }