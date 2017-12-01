#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

int T[11][101];
int V[11][101]; //represents best cost;
int D[11][101]; //represents a row diff that took us to this place.
vector<int> P[11][101];


void process(int N, int M)
{
    for(int i = 0 ; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            scanf("%d", &T[i][j]);
        }
    }

    for(int i = 0; i < N; ++i) {
        V[i][0] = T[i][0];
        D[i][0] = 1;
        P[i][0].clear();
        P[i][0].push_back(i);
    }

    {
        vector<tuple<int, vector<int>, int> > candidates;
        for(int j = 1; j < M; ++j) {
            for(int i = 0 ; i < N; ++i) {
                candidates.clear();

                for(int k = -1; k <= 1; ++k) {
                    int other_row = (N + i + k) % N;
                    vector<int> path(P[other_row][j-1]);
                    path.push_back(i);
                    candidates.push_back(make_tuple(V[other_row][j-1] + T[i][j], path, k));
                }

                sort(candidates.begin(), candidates.end());

                V[i][j] = get<0>(candidates[0]);
                P[i][j] = get<1>(candidates[0]);
                D[i][j] = get<2>(candidates[0]);
            }
        }
    }

    {
        vector<tuple<int, vector<int>, int> > candidates;
        for (int i = 0; i < N; ++i) {
            candidates.push_back(make_tuple(V[i][M-1], P[i][M-1], i));
        }

        sort(candidates.begin(), candidates.end());

        vector<vector<int> > paths;
        int min_d = get<0>(candidates[0]);

        for(int i = 0; get<0>(candidates[i]) == min_d && i < candidates.size(); ++i) {
            paths.push_back(move(get<1>(candidates[i])));
        }

        sort(paths.begin(), paths.end());

//    for(int i = 0; i < N; ++i) {
//        for(int j = 0 ; j < M; ++j) {
//            printf("%d\t", T[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n\n");
//
//    for(int i = 0; i < N; ++i) {
//        for(int j = 0 ; j < M; ++j) {
//            printf("%d\t", V[i][j]);
//        }
//        printf("\n");
//    }

        //output
        for(int i = 0 ; i < paths[0].size(); ++i) printf("%d ", paths[0][i]+1);
        printf("\n%d\n", min_d);
    }
}


int main() {

    int N, M;
    while(scanf("%d %d", &N, &M) != EOF) process(N,M);
    return 0;
}