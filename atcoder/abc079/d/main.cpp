#include <cstdio>

//using namespace std;

int T[11][11];

int main() {

    int R, C;

    scanf("%d %d", &R, &C);

    for(int i = 0 ; i <= 9; ++i) {
        for(int j = 0 ; j <= 9; ++j) {
            scanf("%d", &T[i][j]);
        }
    }
    for(int k = 0 ; k <= 9; ++k) {
        for(int i = 0 ; i <= 9; ++i) {
            for(int j = 0 ; j <= 9; ++j) {

                if(T[i][j] > T[i][k] + T[k][j]) {
                    T[i][j] = T[i][k] + T[k][j];
                }
            }
        }
    }

    unsigned long long res = 0;

    for(int i = 0 ; i < R; ++i) {
        for(int j = 0 ; j < C; ++j) {
            int d;
            scanf("%d", &d);
            if(d != -1) {
                res += T[d][1];
            }
        }
    }

    printf("%llu\n", res);

    return 0;
}