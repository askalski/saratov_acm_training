#include <cstdio>
#include <algorithm>

const int K = 100*1000;
int D[2*K + 1];

/*
 * let S[i] = -1*(#0) + (#1) in series [1..N].
 * let D[s + K] = earliest index i such that S[i] = s, or -1 if no such index exist.
 */

int main() {

    int N;
    int best = 0;

    scanf("%d\n", &N);
    for(int i = -N; i <= N; ++i) {
        D[i + K] = -1;
    }

    int s = 0;
    D[0 + K] = 0;

    for(int i = 1 ; i <= N; ++i) {
        char c;
        scanf("%1c", &c);
        if(c == '0') s--; else s++;

        if(D[s+K] != -1) {
            int candidate = i - D[s+K];
            best = std::max(best, candidate);
        } else {
            D[s+K] = i;
        }
    }

    printf("%d\n", best);
    return 0;
}