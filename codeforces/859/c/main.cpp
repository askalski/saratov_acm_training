#include <cstdio>
#include <algorithm>
using namespace std;

int main() {

    int n;
    int T[50];
    scanf("%d", &n);
    for(int i = 0 ; i < n; ++i) scanf("%d", &T[i]);

    int S[50];
    S[n-1] = T[n-1];
    for(int i = n-2; i>= 0 ;--i) S[i] = S[i+1] + T[i];

    int O[50];
    O[n-1] = S[n-1];
    for(int i = n-2; i>= 0; --i) {
        int option1 = O[i+1];
        int option2 = T[i] + S[i+1] - O[i+1];
        O[i] = max(option1, option2);
    }

    printf("%d %d\n", S[0] - O[0], O[0]);

    return 0;
}