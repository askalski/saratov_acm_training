#include <cstdio>

int main() {
    unsigned int N;
    scanf("%u", &N);
    unsigned int res = N - (N+2)/3;
    printf("%u\n", res);
    return 0;
}