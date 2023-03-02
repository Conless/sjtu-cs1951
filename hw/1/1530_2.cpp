#include <iostream>
#include <cstring>

constexpr int base_1 = 233;
constexpr int mod_1 = 1e6 + 7;
constexpr int base_2 = 223;
constexpr int mod_2 = 2464547;

int Hash1(const std::string &s);
int Hash2(const std::string &s);
int index_1[mod_1 +5] = {-1};
int index_2[mod_2 +5] = {-1};

int main() {
    int n;
    std::cin >> n;
    memset(index_1, -1, sizeof(index_1));
    memset(index_2, -1, sizeof(index_2));
    std::string tmp;
    for (int i = 0; i < n; ++i) {
        std::cin >> tmp;
        index_1[Hash1(tmp)] = i;
        index_2[Hash2(tmp)] = i;
    }

    int m;
    std::cin >> m;
    int max_words = 0;
    int flag[1005] = {0};
    int match[100005] = {-1};
    memset(match, -1, sizeof(match));
    for (int i = 0; i < m; ++i) {
        std::cin >> tmp;
        int num = index_1[Hash1(tmp)];
        if (num >= 0 && num == index_2[Hash2(tmp)]) {
            if (!flag[num]) {
                ++max_words;
                flag[num] = 1;
            }
            match[i] = num;
        }
    }
    std::cout << max_words << std::endl;
    if (max_words == 0 || max_words == 1) {
        std::cout << max_words << std::endl;
        return 0;
    }

    int cnt[1005] = {0};
    int st = 0;
    while (match[st] == -1) ++st;
    int ed = st;
    ++cnt[match[st]];
    int count = 1;
    while (count < max_words && ed < m) {
        ++ed;
        if (match[ed] == -1) continue;
        if (++cnt[match[ed]] == 1) ++count;
    }
    while (match[st] == -1 || cnt[match[st]] > 1) {
        if (match[st] != -1) --cnt[match[st]];
        ++st;
    }
    int ans = ed - st + 1;
    while (ed < m - 1) {
        ++ed;
        if (match[ed] == match[st]) {
            ++st;
            while (match[st] == -1 || cnt[match[st]] > 1) {
                if (match[st] != -1) --cnt[match[st]];
                ++st;
            }
            if (ans > ed - st + 1) ans = ed - st + 1;
        }
        else if (match[ed] > -1) ++cnt[match[ed]];
    }
    std::cout << ans << std::endl;

    return 0;
}

int Hash1(const std::string &s) {
    int hash = 0;
    for (char i : s) {
        hash = ((long long)hash * base_1 + i) % mod_1;
    }
    return hash;
}

int Hash2(const std::string &s) {
    int hash = 0;
    for (char i : s) {
        hash = ((long long)hash * base_2 + i) % mod_2;
    }
    return hash;
}