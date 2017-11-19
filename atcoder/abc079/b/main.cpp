#include <cstdio>

unsigned long long T[100];

int main() {
    int N;

    scanf("%d", &N);

    T[0] = 2;
    T[1] = 1;

    for(int i = 2; i <= N; ++i) {
        T[i] = T[i-1] + T[i-2];
    }

    printf("%llu\n", T[N]);

    return 0;
}
