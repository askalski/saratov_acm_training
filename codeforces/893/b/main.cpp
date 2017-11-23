#include <cstdio>

int power(int i) {
    if(i == 0) return 1;
    if(i == 1) return 2;
    int tmp = power(i/2);
    tmp *= tmp;
    if(i % 2) tmp *= 2;
    return tmp;
}

int main() {
    int N;
    int best = 1;

    scanf("%d", &N);

    for(int i = 2;; i++) {
        int candidate = power(2*i-1) - power(i - 1);
        if(candidate > N) break;
        if(N % candidate == 0) {
            best = candidate;
        }
    }

    printf("%d\n", best);

    return 0;
}