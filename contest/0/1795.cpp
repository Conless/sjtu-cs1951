#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 3e5 + 5;

int cnt;
int tr[MAXN][26], tg[MAXN], fail[MAXN << 3];

void insert(const string &p) {
	int u = 0;
	for (auto ch : p) {
		if (!tr[u][ch - 'a'])
			tr[u][ch - 'a'] = ++cnt;
		u = tr[u][ch - 'a'];
	}
	tg[u]++;
}

void build() {
	int head = 0, tail = 0;
	int que[MAXN];
	memset(fail, 0, sizeof(fail));
	for (int i = 0; i < 26; i++)
		if (tr[0][i])
			que[++tail] = tr[0][i];
	while (head != tail) {
		head++;
		int u = que[head];
		for (int i = 0; i < 26; i++) {
			if (tr[u][i]) {
				fail[tr[u][i]] = tr[fail[u]][i];
				que[++tail] = tr[u][i];
			} else {
				tr[u][i] = tr[fail[u]][i];
			}
		}
	}
}

int query(const string &s) {
	int u = 0, res = 0;
	for (auto ch : s) {
		u = tr[u][ch - 'a'];
		int v = u;
		while (v) {
			res += tg[v];
			v = fail[v];
		}
	}
	return res;
} 

int tot = 0;
string str[MAXN];

int main() {
	ios::sync_with_stdio(false);
	int n, m, las = 0;
	cin >> n >> m;
	int bdtag = 0;
	while (n--) {
		int opt;
		string s;
		cin >> opt >> s;
		if (m)
			opt ^= las;
		if (opt == 1) {
			str[++tot] = s, bdtag = 0;
		} else if (opt == 2) {
			for (int i = 1; i <= tot; i++) {
				if (str[i] == s) {
					str[i] = "";
					break;
				}
			}
			bdtag = 0;
		} else {
			if (!bdtag) {
				memset(tr, 0, sizeof(tr));
				memset(tg, 0, sizeof(tg));
				cnt = 0;
				for (int i = 1; i <= tot; i++) {
					if (str[i] != "")
						insert(str[i]);
				}
				build();
				bdtag = 1;
			}
			int ans = query(s);
			las = ans;
			cout << ans << endl;
		}
	}
}
