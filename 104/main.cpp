#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;
int F, V;
int C[101][101];
int T[101][101];
char P[101][101];

#ifdef ONLINE_JUDGE
const bool debug = false;
#else
const bool debug = true;
#endif

int main() {
    scanf("%d %d", &F, &V);

    for(int i = 1 ; i <= F; ++i) {
        for(int j = 1 ; j <= V; ++j) {
            scanf("%d", &C[i][j]);
            T[i][j] = -1000000;
        }
    }

    for(int a = 1; a <= F; ++a) {
        /*
         * since in calculation below we use (at most) cells [a-1][b-1] and [a][b-1] (left, and upper left)
         * and result will be held in cell [F][V] there is no point in computing cells which
         * b > a + F (since they will not contribute to the result.
         *
         * From that we conclude that a portion of the array is wasted, but I keep it for the sake of clarity.
         *
         * EDIT:
         * for some reason above statement seems to be false, and removing it's conclusions leads to solution acceptation.
         * There is a bug somewhere in my thinking.
         */
        for(int b = a; b <= V /*&& b <= a + F*/; ++b) {
            if(a == b) {
                T[a][b] = C[a][b] + (a == 0 ? 0 : T[a-1][b-1]);
                P[a][b] = 'U'; //use
            } else { // b > a
                int cand1 = T[a][b-1]; //ignore the vase
                int cand2 = C[a][b] + (a > 1 ? T[a-1][b-1] : 0); //use the vase
                if(cand1 > cand2) {
                    T[a][b] = cand1;
                    P[a][b] = 'I';
                } else {
                    T[a][b] = cand2;
                    P[a][b] = 'U';
                }
            }
        }
    }

    if(debug) {
        for (int i = 1; i <= F; ++i) {
            for (int j = 1; j <= V; ++j) {
                if (T[i][j] == -1000000) {
                    printf("\t");
                } else {
                    printf("%d\t", T[i][j]);
                }
            }
            printf("\n");
        }

        for (int i = 1; i <= F; ++i) {
            for (int j = 1; j <= V; ++j) {
                if (T[i][j] == -1000000) {
                    printf("\t");
                } else {
                    printf("%1c\t", P[i][j]);
                }
            }
            printf("\n");
        }
    }

    vector<int> rev_res;
    int i = F, j = V;
    while(i >= 1) {
        if(P[i][j] == 'U') {
            rev_res.push_back(j);
            i--;
            j--;
        } else {
            j--;
        }
        assert(j >= i);
    }

    printf("%d\n", T[F][V]);
    for(int i = rev_res.size() - 1; i >= 0; i--) {
        printf("%d ", rev_res[i]);
    }
    printf("\n");
    return 0;
}