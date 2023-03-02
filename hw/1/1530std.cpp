#include <iostream>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;
int m,n,val;
string a[100005];
unordered_map<string,int> book,flag,vis;
int check(int x){
    int c0=1,cnt=0,ans=0;
    vis.clear();
    for(int i=1;i<=x;i++) {
        if(book[a[i]] && !vis[a[i]]) cnt++;
        if(book[a[i]]) vis[a[i]]++;
    }
    for(int i=x+1;i<=n;i++){
        ans=max(cnt,ans);
        if(book[a[i]] && !vis[a[i]])
            cnt++;
        if(book[a[c0]] && vis[a[c0]]-1==0) 
            cnt--;
        vis[a[i]]++,vis[a[c0]]--;
        c0++;
    } 
    return max(cnt,ans);
}
int search(){
    int L=-1,R=n,mid;
    while(L<R-1){
        mid=(L+R)/2;
        if(check(mid)==val) R=mid;
        else L=mid;
    }
    return R;
}
int main()
{
    ios::sync_with_stdio(false);
    string str;
    cin>>m;
    for(int i=1;i<=m;i++) cin>>str,book[str]=1;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) if(book[a[i]] && !flag[a[i]]) val++,flag[a[i]]=1;
    cout<<val<<'\n'<<search()<<endl;
    return 0;
}