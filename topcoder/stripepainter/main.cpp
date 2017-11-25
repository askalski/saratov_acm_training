#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class StripePainter {
public:
    int minStrokes(string old_s) {
        string s;
        //remove duplicates, move one ahead
        s.push_back('.');
        s.push_back(old_s[0]);
        for(int i = 1; i < old_s.size(); ++i) {
            if(old_s[i] != *s.rbegin()) s.push_back(old_s[i]);
        }

        int n = s.size() - 1;

        vector<int> pol(s.size()+1, -1);

        for(int i = 1; i <= n; ++i) {
            for(int j = i+2; j <= n; ++j) {
                if(s[i] == s[j]) {
                    pol[i] = j;
                    break;
                }
            }
        }

        for(int i = 1; i <= n; ++i) printf("%d\t", pol[i]);
        printf("\n");

        //T stands for number of "connetions" T[i][j] = max number of non-intersecting connections from s[i..j]
        int T[52][52];


        for(int i = 1 ; i <= n; ++i) T[i][1] = 0; //no single element connections
        for(int i = 1 ; i+1 <= n; ++i) T[i][2] = 0; //no two element connections, since removed duplicates

        for(int len = 3; len <= n; ++len) {
            for(int pos = 1; pos + len - 1 <= n; ++pos) {
                T[pos][len] = 0;
                int cand = 0; //candidate for # of connections
                //we divide [pos, pos+len-1] to two parts: [pos,d] and [d, pos+len-1]
                //the i'th element can be shared by both connections.
                for(int d = pos+1; d < pos+len-1; ++d) {
                    cand = std::max(cand, T[pos][d-pos+1] + T[d][pos+len-1-d+1]);
                }

                //if we have connection and it is within our range
                if(pol[pos] != -1 && pol[pos] <= pos+len-1) {
                    int new_cand = 1; //this connection

                    int d = pol[pos];

                    //d-pos >= 2.
                    new_cand += T[pos+1][(d-1)-(pos+1)+1];
                    /*
                    if(pos+len-1 > d) { //there is a tail behind d!
                        new_cand += T[d][len+pos-1-d+1];
                    }*/

                    cand = std::max(cand, new_cand);
                }

                T[pos][len] = cand;
            }
        }

        /*
        printf("l:\t");
        for(int i = 1 ; i <= n ; ++i) printf("%d\t", i);
        printf("\n");

        for(int i = 1 ; i <= n ; ++i) {
            printf("%d: \t", i);
            for(int j = 1; j <= n; ++j) {
                printf("%d\t", T[j][i]);
            }
            printf("\n");
        }*/

        return n - T[1][n];
    }
};

int main() {

    {
        StripePainter s;
        int res = s.minStrokes("RGBGR");
        printf("%d\t", res);
        if(res == 3) printf("true\n"); else printf("false\n");
    }

    {
        StripePainter s;
        int res = s.minStrokes("RGRG");
        printf("%d\t", res);
        if(res == 3) printf("true\n"); else printf("false\n");
    }

    {
        StripePainter s;
        int res = s.minStrokes("ABACADA");
        printf("%d\t", res);
        if(res == 4) printf("true\n"); else printf("false\n");
    }

    {
        StripePainter s;
        int res = s.minStrokes("AABBCCDDCCBBAABBCCDD");
        printf("%d\t", res);
        if(res == 7) printf("true\n"); else printf("false\n");
    }

    {
        StripePainter s;
        int res = s.minStrokes("BECBBDDEEBABDCADEAAEABCACBDBEECDEDEACACCBEDABEDADD");
        printf("%d\t", res);
        if(res == 26) printf("true\n"); else printf("false\n");
    }

    return 0;

}