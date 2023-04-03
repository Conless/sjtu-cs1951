#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 3e3 + 5;

int n, m, a, b, c, d, ans, head, tail;
int x[MAXN][MAXN], s[MAXN][MAXN];
pair<int, int> que[MAXN * MAXN];

int get_area(int end_x, int end_y, int scope_x, int scope_y) {
    int start_x = end_x - scope_x;
    int start_y = end_y - scope_y;
    return s[end_x][end_y] - s[start_x][end_y] - s[end_x][start_y] + s[start_x][start_y];
}

void push(int posx, int posy) {
    int ar = get_area(posx, posy, c, d);
    while (head <= tail && ar <= get_area(que[tail].first, que[tail].second, c, d))
        tail--;
    que[++tail] = {posx, posy};
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
    for (int i = a; i <= n; i++) {
        head = 1, tail = 0;
        for (int l = d + 1; l < b - 1; l++)
            for (int k = i - a + c + 1; k < i; k++)
                push(k, l);
        for (int j = b; j <= m; j++) {
            while (head <= tail && que[head].second < j - b + d + 1)
                head++;
            for (int k = i - a + c + 1; k < i; k++)
                push(k, j - 1);
            int s1 = get_area(i, j, a, b), s2 = get_area(que[head].first, que[head].second, c, d);
            //			cout << s1 - s2 << ' ';
            ans = max(ans, s1 - s2);
            ans = ans;
        }
        //		cout << endl;
    }
    cout << ans << endl;
    return 0;
}
