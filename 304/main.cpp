#ifdef ONLINE_JUDGE
const bool debug = false;
#else
const bool debug = true;
#endif

#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>

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
 * H[a][c]
 * cost of curing exactly 'a' teeth using gums 1..c .
 * Probably changing the order of indices could lead to cache optimisation.
 */

struct {
   int cost;
   tuple<int, int> predecessor;
   int number_of_teeth_used_in_last_gum;
} H[601][601];

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

    for(int g = 1; g <= K; ++g) {
        sort(gum_bucket[g].begin(), gum_bucket[g].end());
    }

    for(int g = 1; g <= K; ++g) {
        T[g][0] = gum[g].cost;
        if(debug) printf("G: [%d]\t", T[g][0]);
        for(int i = 1; i <= gum_bucket[g].size(); ++i) {
            T[g][i] = T[g][i-1] + gum_bucket[g][i-1].first;
            if(debug) printf("%d\t", T[g][i]);
        }
        if(debug) printf("\n");
    }

    H[0][0].cost = 0;

    for(int c = 1; c <= K; ++c) {
        for(int a = 0; a <= N; ++a) {
            if(a == 0) {
                H[a][c].cost = 0;
                H[a][c].number_of_teeth_used_in_last_gum = 0;
            } else {
                //a > 0
                int best_i = 0; //i == number of teeth from gum c used.
                int best_cost = (c == 1 ? -1 : H[a][c - 1].cost);

                for (int i = 1; a >= i // no point in using more teeth than needed for this cell
                                && i <= gum_bucket[c].size(); ++i) {

                    int candidate = T[c][i]; //cost of getting i teeth from gum c

                    if(a > i) { //but i teeth is not enough, we need a-i teeth from previous gums
                        if(c == 1) { //but there are no earlier gums!
                            continue; //not an option.
                        }

                        if(H[a-i][c-1].cost == -1) { //but with previous gums it was not possible to get (a-i) teeth!
                            continue; //not an option.
                        }

                        candidate += H[a-i][c-1].cost;
                    }

                    if (best_cost == -1 || candidate < best_cost) {
                        best_i = i;
                        best_cost = candidate;
                    }
                }

                H[a][c].cost = best_cost;
                H[a][c].number_of_teeth_used_in_last_gum = best_i;
                H[a][c].predecessor = make_tuple(a-best_i, c-1);
            }

            if(debug) printf("[%d, %d]\t", H[a][c].cost, H[a][c].number_of_teeth_used_in_last_gum);
        }
        if(debug) printf("\n");
    }

    int res = 0;
    for(int n = 1; n <= N; ++n) {
        if(H[n][K].cost <= P) {
            res = n;
        }
    }

    printf("%d\n", res);

    vector<int> used_teeth;

    int curr_n = res, curr_k = K;
    while(curr_n > 0) {
        for(int i = 0; i < H[curr_n][curr_k].number_of_teeth_used_in_last_gum; ++i) {
            used_teeth.push_back(gum_bucket[curr_k][i].second);
        }

        curr_n = get<0>(H[curr_n][curr_k].predecessor);
        curr_k = get<1>(H[curr_n][curr_k].predecessor);
    }

    sort(used_teeth.begin(), used_teeth.end());
    for(int i : used_teeth) printf("%d ", i);
    if(used_teeth.size()) printf("\n");

    return 0;
}