#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 1e6 + 3;
double sqr[N];
int h[N];
double ans1[N],ans2[N];
/// @brief 需求高度最小值 \n
/// 注意 x < y
double height(int x,int y) {
    return sqr[y-x] + h[x] - h[y];
}
/// @brief 找出l,r决策单调点 \n
/// 范围已经被确定在L,R内
void calc(double *ans,int l,int r,int L,int R) {
    if(l > r) return;
    int mid = (l+r) >> 1;
    int loc = L; // 最优决策
    // 找出 mid 的决策点
    for(int i = L + 1 ; i <= min(mid,R) ; ++i) // i > loc 且更优,更新最优决策
        if(height(loc,mid) < height(i,mid)) loc = i;
    ans[mid] = height(loc,mid);
    calc(ans,l,mid-1,L,loc);
    calc(ans,mid+1,r,loc,R);
}
void print(double h) {
    const static double epsilon = /*1e-1*/0;
    cout << int((h > epsilon) ? ceil(h) : 0) << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    sqr[0] = 0;
    for(int i = 1 ; i <= n ; ++i) cin >> h[i],sqr[i] = sqrt(i);
    calc(ans1,1,n,1,n);
    for(int i = 1 ; i < n + 1 - i ; ++i) swap(h[i],h[n+1-i]);
    calc(ans2,1,n,1,n);
    // cout << "FUCK\n";
    for(int i = 1 ; i <= n ; ++i) print(max(ans1[i],ans2[n+1-i]));
    return 0;
}