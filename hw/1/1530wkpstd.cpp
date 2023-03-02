#include <cstdio>
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }
int const maxn = 10003;

int tr[maxn][26], id[maxn], cid = 0, cnode = 0;
void insert(char *s) {
	int p = 0;
	while (*s) {
		int c = *s++ - 'a';
		if (!tr[p][c]) tr[p][c] = ++cnode;
		p = tr[p][c];
	}
	if (!id[p]) id[p] = ++cid;
}
int query(char *s) {
	int p = 0;
	while (*s) {
		int c = *s++ - 'a';
		p = tr[p][c];
		if (!p) return 0;
	}
	return id[p];
}

int n = 0;
int a[100003];
char buff[20];
int nxt[100003], at[100003];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", buff);
		insert(buff);
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", buff);
		a[i] = query(buff);
	}
	int rmax = 0, sum = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 0) continue;
		if (at[a[i]])
			nxt[at[a[i]]] = i;
		else {
			++sum;
			rmax = i;
		}
		at[a[i]] = i;
	}
	int min_len = rmax;
	for (int l = 1; l <= n; ++l) {
		if (!a[l]) {
			min_len = min(min_len, rmax - l);
			continue;
		}
		if (nxt[l]) {
			rmax = max(rmax, nxt[l]);
			min_len = min(min_len, rmax - l);
		}
		else break;
	}
	if (min_len < 0) min_len = 0;
	printf("%d\n%d\n", sum, min_len);
	return 0;
}