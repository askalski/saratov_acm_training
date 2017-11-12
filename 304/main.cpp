#ifdef ONLINE_JUDGE
const bool debug = false;
#else
const bool debug = true;
#endif

#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>
#include <climits>
#include <cassert>

using namespace std;

int N, K, P;

struct {
    int cost;
} gum[601];

struct {
    int cost;
    int gum_id;
} tooth[601];

/*
 * H[a][b][c]
 * cost of curing exactly 'a' teeth in exactly 'b' gums such that all gum id's belong to {1..c} set.
 * Probably changing the order of indices could lead to cache optimisation.
 */

struct {
   int cost;
   tuple<int, int, int> predecessor;
   int number_of_teeth_used_in_last_gum;
} H[601][601][601];

/*
 * T[g][i]
 * cost of i teeth in gum g
 */
int T[601][601];

/*
 * pairs <tooth cost, tooth id> in gum-indexed buckets. For building T.
 */
vector<pair<int, int> > gum_bucket[601];

int main() {

    scanf("%d %d %d", &N, &K, &P);

    for(int i = 1 ; i <= K; ++i) scanf("%d", &gum[i].cost);
    for(int i = 1 ; i <= N; ++i){
        scanf("%d %d", &tooth[i].cost, &tooth[i].gum_id);
        gum_bucket[tooth[i].gum_id].push_back(make_pair(tooth[i].cost, i));
    }

//TODO fix that
//    for(int g = 0; g <= K; ++g) { //no mistake, H[][][0] corresponds to empty set of allowed gums
//        H[0][0][g].cost = 0;
//    }

    for(int g = 1; g <= K; ++g) {
        sort(gum_bucket[g].begin(), gum_bucket[g].end());
    }

    for(int g = 1; g <= K; ++g) {
        T[g][0] = gum[g].cost;
        for(int i = 1; i <= gum_bucket[g].size(); ++i) {
            T[g][i] = T[g][i-1] + gum_bucket[g][i].first;
        }
    }

    for(int b = 1; b <= K; ++b) {
        for(int a = 1; a <= N; ++a) {
            for(int c = 1; c <= K; ++c) {
                int best_i = 0;
                int best_val_for_i = c > 1 ? H[a][b][c-1].cost : INT_MAX;

                for(int i = 1 ; i <= gum_bucket->size(); ++i) {
                    if(a - i >= 0) {
                        int candidate = H[a-i][b-1][c-1].cost + T[c][i];
                        if(candidate < best_val_for_i) {
                            best_i = i;
                            best_val_for_i = candidate;
                        }
                    }
                }

                H[a][b][c].cost = best_val_for_i;
                H[a][b][c].number_of_teeth_used_in_last_gum = best_i;
                H[a][b][c].predecessor = best_i > 0 ? make_tuple(a-best_i,b-1,c-1) : make_tuple(a,b,c-1);
            }
        }
    }

    int result = 0;
    for(int a = 1; a <= N; ++a) {
        for(int b = 1; b <= K; ++b) {
            if(H[a][b][K].cost <= P && a > result) {
                result = a;
            }
        }
    }

    printf("%d\n", result);

    return 0;
}