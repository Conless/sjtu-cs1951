#include <iostream>
#include <bits/stl_pair.h>
#include <stack>

using namespace std;

const int MAXN = 8e4 + 5;

int n;
long long ans;
int h[MAXN];
stack<pair<int, int> > st;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    for (int i = n; i >= 1; i--) {
        int cnt = 1;
        while (!st.empty()) {
            if (st.top().first >= h[i])
                break;
            cnt += st.top().second;
            ans += st.top().second - 1;
            st.pop();
        }
        st.push(make_pair(h[i], cnt));
    }
    while (!st.empty()) {
        ans += st.top().second - 1;
        st.pop();
    }
    cout << ans << endl;
    return 0;
}