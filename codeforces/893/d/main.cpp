#include <cstdio>
#include <vector>

using namespace std;

constexpr int maxN = 100*1000+1;

int T[maxN];
int S[maxN];
int maxLoc[maxN];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for(int i = 0 ; i < N; ++i) {
        scanf("%d", &T[i]);
    }

    int maxS = T[0];

    S[0] = T[0];
    for(int i = 1 ; i < N; ++i) {
        S[i] = S[i-1] + T[i];
        maxS = max(maxS, S[i]);
    }

    if(maxS > M) {
        printf("-1\n");
        return 0;
    }

    vector<int> zeros;
    for(int i = 0; i < N; ++i) if(!T[i]) zeros.push_back(i);

    maxLoc[N-1] = S[N-1];
    for(int i = N-2; i>=0 ; --i) {
        maxLoc[i] = max(maxLoc[i+1], S[i]);
    }

    int modifier = 0;
    int res = 0;
    bool possible = true;
    for(int i = 0; possible && i < N; ++i) {
        if(T[i] == 0) {
            if(S[i] + modifier < 0) {
                res++;
                modifier += M - maxLoc[i]; //we put as much as we can.
                if(S[i] + modifier < 0) {
                    possible = false; //impossible.
                }
            }
        }
    }

    if(!possible) {
        printf("-1\n");
    } else {
        printf("%d\n", res);
    }


    return 0;
}