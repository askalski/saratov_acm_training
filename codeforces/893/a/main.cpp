#include <cstdio>

int main() {
    int N;
    scanf("%d", &N);

    int players[2];
    players[0] = 1;
    players[1] = 2;

    for(int i = 0 ; i < N; ++i) {
        int c;
        scanf("%d",&c);

        if(c != players[0] && c != players[1]) {
            printf("NO\n");
            return 0;
        } else {

            int who = 1;
            if(who == players[0] || who == players[1]) who++;
            if(who == players[0] || who == players[1]) who++;

            if(c == players[0]) {
                players[1] = who;
            } else if(c == players[1]) {
                players[0] = who;
            }
        }
    }
    printf("YES\n");

    return 0;
};