#include <vector>
#include <string>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;

class AvoidRoads {
public:
    long numWays(int width, int height, vector<string> bad) {

        set<tuple<int, int, int, int> > forbidden;

        for(auto &A : bad) {
            int a,b,c,d;
            tuple<int, int, int, int> x;
            sscanf(A.c_str(), "%d %d %d %d", &a,&b,&c,&d);
            vector<pair<int, int> > v;
            v.push_back(make_pair(a,b));
            v.push_back(make_pair(c,d));
            sort(v.begin(), v.end());

            get<0>(x) = v[0].first;
            get<1>(x) = v[0].second;
            get<2>(x) = v[1].first;
            get<3>(x) = v[1].second;

            forbidden.insert(x);
        }

        long T[101][101];

        T[0][0] = 1;

        for(int i = 0; i <= width; ++i) {
            for(int j = 0; j <= height; ++j) {

                if(i == 0 && j == 0) continue;

                tuple<int, int, int, int> from_left(i-1, j, i, j), from_above(i, j-1, i, j);
                if(forbidden.find(from_left) != forbidden.end() && forbidden.find(from_above) != forbidden.end()) {
                    T[i][j] = 0;
                    continue;
                }
                if(forbidden.find(from_left) != forbidden.end()) {
                    T[i][j] = j > 0 ? T[i][j-1] : 0;
                    continue;
                }
                if(forbidden.find(from_above) != forbidden.end()) {
                    T[i][j] = i > 0 ? T[i-1][j] : 0;
                    continue;
                }

                T[i][j] = (j > 0 ? T[i][j-1] : 0) + (i > 0 ? T[i-1][j] : 0);
            }
        }

        /*
        for(int i = 0; i <= width; ++i) {
            for (int j = 0; j <= height; ++j) {
                printf("%ld\t", T[i][j]);
            }
            printf("\n");
        }*/

        return T[width][height];
    }
};

int main() {
    AvoidRoads ar;
    ar.numWays(6, 6, {"0 0 0 1","6 6 5 6"});
    return 0;
}