#include <cstdio>

int main() {
    int N;
    scanf("%d", &N);

    char buf[10];
    sprintf(buf, "%d", N);

    if((buf[0] == buf[1] && buf[1] == buf[2]
       || (buf[1] == buf[2] && buf[2] == buf[3]))) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}