#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int main() {

    char buf[103];
    unsigned long long re[103][3];

    scanf("%s", buf);
    string s(buf);

    re[0][0] = 0;
    re[0][1] = 0;
    re[0][2] = 0;

    for(int i = 0 ; i < s.size() ; ++i) {
        re[i+1][0] = re[i][0];
        re[i+1][1] = re[i][1];
        re[i+1][2] = re[i][2];

        if(s[i] == 'Q') {
            re[i+1][0] += 1;
            re[i+1][2] += re[i][1];
        }

        if(s[i] == 'A') {
            re[i+1][1] += re[i][0];
        }

//        printf("%d: [%llu][%llu][%llu]\n", i+1, re[i+1][0], re[i+1][1], re[i+1][2]);
    }

//    unsigned long long int res = 0;
//    for(int i = 1 ; i <= s.size(); ++i) {
//        res += re[i][2];
//    }

    printf("%llu\n", re[s.size()][2]);

    return 0;
}