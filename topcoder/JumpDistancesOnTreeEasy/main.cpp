#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class JumpDistancesOnTreeEasy {
public:

    string isPossible(vector<int> p, vector<int> S) {

        vector<int> better_s;
        for(int i = 0 ; i < S.size(); ++i) if(S[i] != 0) better_s.push_back(S[i]);
        if(better_s.empty()) return "Possible";

        int n = p.size() + 1;

        map<int, set<pair<int, int>>> d_to_road;

        int D[101][101];

        for(int i = 0 ; i < n; ++i) {
            for(int j = 0 ; j < n; ++j) {
                D[i][j] = -1;
            }
        }

        for(int i = 0 ; i < p.size(); ++i) {
            int a = i+1;
            int b = p[i];

            D[a][b] = 1;
            D[b][a] = 1;
        }

        for(int k = 0 ; k < n; ++k) {
            for(int i = 0 ; i < n; ++i) {
                for(int j = 0 ; j < n; ++j) {
                    if(D[i][k] == -1 || D[k][j] == -1) continue;
                    int cand = D[i][k] + D[k][j];
                    if(D[i][j] == -1 || D[i][j] > cand) D[i][j] = cand;
                }
            }
        }


        for(int i = 0 ; i < n; ++i) {
            for(int j = 0 ; j < n; ++j) {
                if(D[i][j] != -1) {
                    d_to_road[D[i][j]].insert(make_pair(i, j));
                    d_to_road[D[i][j]].insert(make_pair(j, i));
                    printf("%d: %d %d\n", D[i][j], i, j);
                }
            }
        }

        set<int> pvl, pvn;

        pvn.insert(0);

        for(int i = 0 ; i < better_s.size(); ++i) {
            if(pvn.empty()) {
                return "Impossible";
            }

            pvl.clear();
            for(auto p : d_to_road[better_s[i]]) {
                if(pvn.find(p.first) != pvn.end()) {
                    pvl.insert(p.second);
                }
                if(pvn.find(p.second) != pvn.end()) {
                    pvl.insert(p.first);
                }
            }
            pvn = pvl;
        }

        if(!pvn.empty()) return "Possible"; else return "Impossible";


    }
};

int main() {
    {
        JumpDistancesOnTreeEasy s;
        auto res = s.isPossible({0, 0, 2, 1, 1, 3, 4, 6, 7, 9, 8, 11, 10, 11, 14, 14, 13, 15, 17, 19, 19, 18, 21, 21, 22, 23, 25, 25, 26, 29, 27, 29, 31, 30, 33, 33, 34, 34, 35, 37, 38, 39, 42, 43, 41, 43, 43, 47, 46, 49}, {20, 21, 22, 24, 32, 37});
        printf("%s\t", res.c_str());
        if (res == "Possible") printf("true\n"); else printf("false\n");
    }

    {
        JumpDistancesOnTreeEasy s;
        auto res = s.isPossible({0, 1, 1, 0, 4, 4}, {2, 4});
        printf("%s\t", res.c_str());
        if (res == "Possible") printf("true\n"); else printf("false\n");
    }
    {
        JumpDistancesOnTreeEasy s;
        auto res = s.isPossible({0,1,1,0,4,4}, {1,2,3,4,5});
        printf("%s\t", res.c_str());
        if (res == "Impossible") printf("true\n"); else printf("false\n");
    }
    {
        JumpDistancesOnTreeEasy s;
        auto res = s.isPossible({0,1,1,0,4,4}, {3,4});
        printf("%s\t", res.c_str());
        if (res == "Impossible") printf("true\n"); else printf("false\n");
    }
    {
        JumpDistancesOnTreeEasy s;
        auto res = s.isPossible({0,1,2,3,4,0,6,7,8,9}, {2,4,6,8,10});
        printf("%s\t", res.c_str());
        if (res == "Impossible") printf("true\n"); else printf("false\n");
    }
    {
        JumpDistancesOnTreeEasy s;
        auto res = s.isPossible({0}, {1});
        printf("%s\t", res.c_str());
        if (res == "Possible") printf("true\n"); else printf("false\n");
    }
    return 0;
}