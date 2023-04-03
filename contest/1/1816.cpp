#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 3e3 + 5;

int n, m, a, b, c, d, ans;
int x[MAXN][MAXN], s[MAXN][MAXN];
int head[MAXN], tail[MAXN];
int que[MAXN][MAXN];

int get_area(int end_x, int end_y, int scope_x, int scope_y) {
    int start_x = end_x - scope_x;
    int start_y = end_y - scope_y;
    return s[end_x][end_y] - s[start_x][end_y] - s[end_x][start_y] + s[start_x][start_y];
}

void push(int posx, int posy) {
    int ar = get_area(posx, posy, c, d);
    while (head[posy] <= tail[posy] && ar <= get_area(que[posy][tail[posy]], posy, c, d))
        tail[posy]--;
    que[posy][++tail[posy]] = posx;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> a >> b >> c >> d;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> x[i][j];
            s[i][j] = s[i][j - 1] + x[i][j];
        }
        for (int j = 1; j <= m; j++)
            s[i][j] += s[i - 1][j];
    }
    // Here we need to find the minimum elements of row [i - a + c + 1, i - 1], column [j - b + d + 1, j - 1]
    // We may maintain m - 2 monotonic queues for column [2, m - 1], respectively
    // Then, from row [2, a - 1], insert the elements first
    for (int j = 2; j < m; j++)
        head[j] = 1, tail[j] = 0;
    for (int i = c + 1; i < a; i++) {
        for (int j = d + 1; j < m; j++)
            push(i, j);
    }
    // Then, when scanning each row, we can do such operations: 1. pop the invalid elements; 2. calculate the result; 3. push
    // the new elements
    for (int i = a; i <= n; i++) {
        int headr = 1, tailr = 0;
        pair<int, int> qr[MAXN];
        for (int j = d + 1; j < m; j++) {
            while (head[j] <= tail[j] && que[j][head[j]] <= i - a + c)
                head[j]++;
            if (j < b) {
                int ar = get_area(que[j][head[j]], j, c, d);
                while (headr <= tailr && ar <= get_area(qr[tailr].first, qr[tailr].second, c, d))
                    tailr--;
                qr[++tailr] = {que[j][head[j]], j};
            }
        }
        for (int j = b; j <= m; j++) {
            while (headr <= tailr && qr[headr].second <= j - b + d)
                headr++;
            ans = max(ans, get_area(i, j, a, b) - get_area(qr[headr].first, qr[headr].second, c, d));
            int ar = get_area(que[j][head[j]], j, c, d);
            while (headr <= tailr && ar <= get_area(qr[tailr].first, qr[tailr].second, c, d))
                tailr--;
            qr[++tailr] = {que[j][head[j]], j};
        }
        for (int j = d + 1; j < m; j++)
            push(i, j);
    }
    cout << ans << endl;
    return 0;
}