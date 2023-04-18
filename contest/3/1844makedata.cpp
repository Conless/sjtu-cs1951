#include <bits/stdc++.h>

using namespace std;

int main() {
    time_t t;
    srand(time(&t));
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 3; j++)
            cout << rand() << ' ';
        cout << '\n';
    }
}