#include <cstdio>
#include <algorithm>

int main() {

    int N;
    long long a;
    long long A[3];
    long long Best[3];

    scanf("%d %lld %lld %lld", &N, &A[0], &A[1], &A[2]);

    scanf("%lld", &a);

    Best[0] = A[0]*a;
    Best[1] = Best[0] + A[1]*a;
    Best[2] = Best[1] + A[2]*a;


    for(int i = 1 ; i < N; ++i) {
        scanf("%lld", &a);
        Best[0] = std::max(Best[0], A[0]*a);
        Best[1] = std::max(Best[1], Best[0] + A[1]*a);
        Best[2] = std::max(Best[2], Best[1] + A[2]*a);
    }

    printf("%lld\n", Best[2]);

    return 0;
}