#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1e6 + 5;

int pi[MAXN], ans[MAXN];

int get_ans(int pos) {
	if (ans[pos])
		return ans[pos];
	if (!pi[pos - 1])
		return pos;
	return ans[pos] = get_ans(pi[pos - 1]);
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		string s;
		cin >> s;
		int n = s.size();
		memset(pi, 0, sizeof(pi));
		memset(ans, 0, sizeof(ans));
		long long ans = 0;
		for (int i = 1, j = 0; i < n; i++) {
			while (j && s[i] != s[j])
				j = pi[j - 1];
			if (s[i] == s[j])
				j++;
			pi[i] = j;
			int res = get_ans(j);
			if (res)
				ans += i - res + 1;
		}
		cout << ans << endl;
	}
	return 0;
}
