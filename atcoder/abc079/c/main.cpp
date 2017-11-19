#include <cstdio>
#include <vector>

using namespace std;
char I[4];

vector<char> result;

bool go(int p, vector<char> &a) {
    if(p == 3) {
        int res = I[0] - '0';

        for(int i = 1 ; i <= 3; ++i) {
            if(a[i-1] == '+') {
                res += I[i] - '0';
            } else {
                res -= I[i] - '0';
            }
        }

        if(res == 7) {
            result = a;
            return true;
        } else return false;
    } else {
        a[p] = '+';
        if(go(p+1, a)) {
            return true;
        }
        a[p] = '-';
        return go(p+1, a);
    }
}

int main() {


    scanf("%4c", I);

    vector<char> a(4);
    go(0,a);

    for(int i = 0 ; i < 3; ++i) {
        printf("%c%c", I[i], result[i]);
    }

    printf("%c=7\n", I[3]);

    return 0;

}