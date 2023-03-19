#include <iostream>
#include <cstring>

const int N = 2003;
int f[N][N];
int ap,bp,as,bs;

struct deque {
    int data[N];
    int head,tail;

    bool size() noexcept { return head != tail; }
    void push_back(int x) noexcept { data[++tail] = x; }
    void pop_front()  noexcept { ++head; }
    void pop_back()   noexcept { --tail; }
    int front()  noexcept { return data[head + 1]; }
    int back()   noexcept { return data[tail]; }
    void reset() noexcept { head = tail = 0; }
};

inline void update(int &x,int y) { if(y > x) x = y; }

inline int value(int x,int y) { return f[x][y] + y * ap; }

signed main() {
    // std::ios::sync_with_stdio(false);
    int t,p,w;
    memset(f[0],180,sizeof(f[0]));
    std::cin >> t >> p >> w;
    ++w;
    deque q;
    f[0][0] = 0;
    for(int i = 1 ; i <= t ; ++i) {
        std::cin >> ap >> bp >> as >> bs;
        int x = i - w > 0 ? i - w : 0;
        for(int j = 0 ; j <= p ; ++j) f[i][j] = f[i - 1][j];

        q.reset();
        for(int j = 0 ; j <= p ; ++j) {
            while(q.size() && q.front() < j - as) 
                q.pop_front();
            while(q.size() && value(x,q.back()) <= value(x,j))
                q.pop_back();
            q.push_back(j);
            update(f[i][j],value(x,q.front()) - j * ap);
        }

        ap = bp;
        q.reset();
        for(int j = p ; j >= 0 ; --j) {
            while(q.size() && q.front() > j + bs) 
                q.pop_front();
            while(q.size() && value(x,q.back()) <= value(x,j))
                q.pop_back();
            q.push_back(j);
            update(f[i][j],value(x,q.front()) - j * ap);
        }
    }
    printf("%d\n",f[t][0]);
    return 0;
}