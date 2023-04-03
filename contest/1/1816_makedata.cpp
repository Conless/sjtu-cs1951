#include <iostream>
#include <cstdio>

using namespace std;

const int N = 10;

int main() {
    time_t t;
    srand(time(&t));
    int n = rand() % N + N, m = rand() % N + N;
    int a = rand() % (n / 3) + (n / 3), b = rand() % (m / 3) + (m / 3);
    int c = rand() % (a / 3) + (a / 3), d = rand() % (b / 3) + (b / 3);
    printf("%d %d %d %d %d %d\n", n, m, a, b, c, d);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            printf("%d ", rand() % N + 1);
        printf("\n");
    }
    return 0;
}