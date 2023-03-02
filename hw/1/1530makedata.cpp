#include <bits/stdc++.h>
#include <ostream>

using namespace std;

int n = 800, m = 30000, batch_size = 2000;

vector<string> s;

void make_string() {
    s.resize(batch_size);
    for (int o = 0; o < batch_size; o++) {
        for (int i = 1; i <= 10; i++) {
            char ch = rand() % 26 + 'a';
            s[o] = s[o] + ch;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    freopen("1530.in", "w", stdout);
    time_t t;
    srand(time(&t));
    cout << n << endl;
    make_string();
    for (int i = 1; i <= n; i++)
        cout << s[i] << endl;
    cout << m << endl;
    while (m--) {
        int pos = rand() % batch_size;
        cout << s[pos] << endl;
    }
    return 0;
}