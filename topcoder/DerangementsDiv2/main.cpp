#include <cstdio>

int MAXN = 1000*1000*1000+7;

class DerangementsDiv2{
public:
    int count(int n, int m) {
        long long T[102];
        T[0] = 1;
        for(int i = 1; i <= n+m+2; ++i) {
            long long tmp = T[i-1]*i;
            tmp %= MAXN;
            T[i] = tmp;
        }

        int P[103][103];
        P[1][1] = 1;
        P[2][1] = 1; P[2][2] = 1;
        for(int i = 3; i <= n+m+1; ++i) {
            for(int j = 1; j <= i; ++j) {
                if(j > 1 && j < i) {
                    P[i][j] = (P[i-1][j] + P[i-1][j-1]) % MAXN;
                } else {
                    P[i][j] = 1;
                }
            }
        }

        long long res = 0;
        long long multiplier = 1;
        for(int i = 0; i <= m; ++i) {
            if(i == 0) multiplier = 1; else multiplier *= -1;
            long long tmp = multiplier * P[m+1][i+1] * T[n+m-i];
            tmp %= MAXN;
            res += tmp + MAXN;
            res %= MAXN;
        }

        return res;
    }
};

int main() {

    {
        DerangementsDiv2 s;
        int res = s.count(0, 2);
        printf("%d\t", res);
        if(res == 1) printf("true\n"); else printf("false\n");
    }

    {
        DerangementsDiv2 s;
        int res = s.count(2, 1);
        printf("%d\t", res);
        if(res == 4) printf("true\n"); else printf("false\n");
    }

    {
        DerangementsDiv2 s;
        int res = s.count(1, 2);
        printf("%d\t", res);
        if(res == 3) printf("true\n"); else printf("false\n");
    }

    {
        DerangementsDiv2 s;
        int res = s.count(3, 5);
        printf("%d\t", res);
        if(res == 21234) printf("true\n"); else printf("false\n");
    }

    {
        DerangementsDiv2 s;
        int res = s.count(20, 27);
        printf("%d\t", res);
        if(res == 88437461) printf("true\n"); else printf("false\n");
    }

    return 0;

}