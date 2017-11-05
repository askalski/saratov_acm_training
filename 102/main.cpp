#include <cstdio>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    if(a < b) swap(a,b);
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int N;
    scanf("%d", &N);

    int res = 0;

    for(int i = 1; i <= N; ++i) {
        if(gcd(N, i) == 1) res++;
    }

    printf("%d\n", res);
}