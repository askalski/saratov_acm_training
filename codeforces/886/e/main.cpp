#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>

int n, k;

const unsigned long long int p = 1000*1000*1000 + 7;

using namespace std;

#define MAX_FACTOR_PLUS_ONE 1000001
int divisor[MAX_FACTOR_PLUS_ONE];

void build_divisors() {
    int root = sqrt(MAX_FACTOR_PLUS_ONE);
    for(int i = 1; i <= 100; ++i) {
        bool done = false;
        for(int d = 2; d <= root; ++d) {
            if(i % d == 0) {
                divisor[i] = d;
                done = true;
            }
        }
        if(!done) {
            divisor[i] = i;
        }
    }
}

class mult_number : public map<int, int> {
public:
    void operator*=(const map<int, int> &b) {
        for(const auto i : b) {
            (*this)[i.first] += i.second;
        }
    }

    void operator*=(int number) {
        assert(number > 0); //zero or negative numbers are not supported by this representation.
        if(number == 1) return;
        while(number != 1) {
            (*this)[divisor[number]]++;
            number /= divisor[number];
        }
    }

    void operator=(const int &number) {
        assert(number < MAX_FACTOR_PLUS_ONE);
        assert(number > 0); //zero is not supported by this representation.
        if(!this->empty()) this->clear();
        (*this)*=number;
    }

    unsigned long long to_ull_mod(const unsigned long long modulo) {
        assert(modulo > 0);
        unsigned long long res = 1;
        for(const auto it : *this) {
            for(int i = 0 ; i < it.second; ++i) {
                res *= it.first;
                res %= modulo;
            }
        }
        return res;
    }
};

/*
 * returns r(a,b) = b! / (b-a)! (notation from Feller's book on probability)
 */

map<tuple<int, int>, mult_number> get_r_cache;
const mult_number& get_r(int a, int b) {
    assert(0 <= a);
    assert(a <= b);

    auto it = get_r_cache.find(make_tuple(a,b));
    if(it != get_r_cache.end()) return it->second;

    mult_number res;
    for (int i = b; i > b-a; i--) {
        res *= i;
    }

    get_r_cache[make_tuple(a,b)] = move(res);
    return get_r_cache[make_tuple(a,b)];
}

map<int, mult_number> get_factorial_cache;
const mult_number& get_factorial(int a) {
    assert(a >= 0);

    auto it = get_factorial_cache.find(a);
    if(it != get_factorial_cache.end()) return it->second;

    mult_number res;
    for(;a>0;a--) {
        res *= a;
    }

    get_factorial_cache[a] = res;
    return get_factorial_cache[a];
}

int main() {
    build_divisors();
    scanf("%d %d", &n, &k);

    if(n <= k+1) {
        printf("0\n");
        return 0;
    }

    unsigned long long res = 0;

    for(int a = k+1; a < n; ++a) {
        //condition below simply says "there have to be enough numbers 1..(a-1) to form both prefix of length i and k following numbers.
        for(int i = 0; a - 1 >= k + i; ++i) {
            //number a will be on i+1th index.
            mult_number local_num = get_r(i, a-1);
            local_num *= get_r(min(k, n-i-1), a-1-i);
            if(n-k-i-1 > 0) {
                local_num *= get_factorial(n-k-i-1);
            }

            unsigned long long tmp = local_num.to_ull_mod(p);
            printf("a = %d i = %d : tmp = %llu\n", a, i, tmp);
            res += tmp;
            res %= p;
        }
    }

    printf("%llu\n", res);

    return 0;
}