#include <bits/stdc++.h>

using namespace std;

inline int read() {                 // read in a int and return
    int ch = getchar();
    if (ch == -1)
        exit(0);
    int x = 0, f = 1;
    while(ch < '0' || ch > '9') 
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9') 
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    } 
    return x * f;
}

int main() {
    int x;
    while ((x = read())) {
        cout << x << endl;
    }
}