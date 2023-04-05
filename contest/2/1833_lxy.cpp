#include <iostream>
#include <cstring>
#include <algorithm>

constexpr int MAXN = 3 * 1e5;

int n, v;
int x_tmp, t_tmp, w_tmp;
int w[MAXN + 5];
long long ans;
long long t[MAXN + 5];
std::pair<int, int> x[MAXN + 5];
int x_save[MAXN + 5];
std::pair<int, int> y_tmp[MAXN + 5];
int y[MAXN + 5];

void add(int index, long long val);
long long find(int index);

bool Comparex(const std::pair<int, int> &l, const std::pair<int, int> &r) {
    if (l.first < r.first) return true;
    if (l.first > r.first) return false;
    return y_tmp[l.second].first < y_tmp[r.second].first;
}
bool Comparey(const std::pair<int, int> &l, const std::pair<int, int> &r) {
    if (l.first < r.first) return true;
    if (l.first > r.first) return false;
    return x_save[l.second] < x_save[r.second];
}

int main() {
    scanf("%d %d", &n, &v);

    if (v == 0) {
        while (n--) {
            scanf("%d %d %d", &x_tmp, &t_tmp, &w_tmp);
            if (w_tmp > ans) ans = w_tmp;
        }
        std::cout << ans;
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        scanf("%d %d %d", &x_tmp, &t_tmp, &w[i]);
        x[i].first = x_tmp + v * t_tmp;
        x_save[i] = x_tmp + v * t_tmp;
        x[i].second = i;
        y_tmp[i].first = v * t_tmp - x_tmp;
        y_tmp[i].second = i;
    }

    std::sort(x + 1, x + n + 1, Comparex);
    std::sort(y_tmp + 1, y_tmp + n + 1, Comparey);

    for (int j = 1; j <= n; ++j) {
        y[y_tmp[j].second] = j;
    }

    for (int k = 1; k <= n; ++k) {
        int i = x[k].second;
        long long tmp_ans = w[i] + find(y[i]);
        // std::cout << y[i] << ' ' << tmp_ans << '\n';
        if (tmp_ans > ans) ans = tmp_ans;
        add(y[i], tmp_ans);
    }

    std::cout << ans;

    return 0;
}

long long find(int index) {
    long long tmp = 0;
    while (index > 0) {
        if (t[index] > tmp) tmp = t[index];
        index -= index & (-index);
    }
    return tmp;
}

void add(int index, long long val) {
    while (index <= n) {
        if (val > t[index]) t[index] = val;
        index += index & (-index);
    }
}