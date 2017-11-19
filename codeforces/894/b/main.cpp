#include <cstdio>
#include <cassert>

using namespace std;

#define ull unsigned long long

unsigned int N,K;
int I;

const ull P = 1000000007;
const ull two_to_minus_one_mod_p = 500000004;


ull number_of_subsets_mod_p(ull n) {
    ull res = number_of_subsets_mod_p(n/2);
    res *= res;
    if(n %= 2) {
        res *= 2;
    }
    res %= P;
    return res;
}

ull number_of_subsets_div_2_mod_p(ull n) {
    ull res = number_of_subsets_mod_p(n);
    res *= two_to_minus_one_mod_p;
    res %= P;
    return res;
}


int main() {
    scanf("%u %u %d", &N, &K, &I);





    return 0;
}