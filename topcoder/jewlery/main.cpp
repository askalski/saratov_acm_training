#include <vector>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

class Jewelry {
public:

    long long newton(int n, int k) {
        long long res = 1;

        for(int d = n-k+1; d <= n; ++d) res *= d;
        for(int d = 1; d <= k; ++d) res /= d;

        return res;
    }

    long long howMany(vector<int> v) {

        sort(v.begin(), v.end());

        long long res = 0;

        //elements 'i' and 'd' HAS to be present in corresponding sets, and they also has to be maximum elements in these sets.

        map<int, int> occ;
        for(const auto &val : v) occ[val]++;

        for(int i = 1; i < v.size(); ++i) {
            for(int d = 0; d < i; ++d) {

                vector<long long> A(30001, 0);
                vector<long long> B(30001, 0);

                int maxa = v[d];
                int maxb = v[i];

                A[maxa] = 1;
                B[maxb] = 1;

                for(int a = 0 ; a < d; ++a) {
                    for(int j = maxa ; j >= 0; j--) {
                        if(A[j]) {
                            A[j + v[a]] += A[j];
                            maxa = max(maxa, j + v[a]);
                        }
                    }
                }

                for(int b = d+1 ; b < i; ++b) {
                    for(int j = maxb ; j >= 0; j--) {
                        if(B[j]) {
                            B[j + v[b]] += B[j];
                            maxb = max(maxb, j + v[b]);
                        }
                    }
                }

                for(int c = 0; c <= max(maxa, maxb); ++c)
                    if(A[c] && B[c]) {

                        int nums = A[c]*B[c];

                        if(occ[v[d]] == 1) {
                            res += nums;
                        } else {
                            int left = 1;
                            for(;d-left >= 0 && v[d-left] == v[d]; left++);

                            res += newton(occ[v[d]], left) * nums;
                        }

//                        res +=

//                        printf("%d\t", c);
                    }
            }
        }

        return res;
    }
};

int main() {
    Jewelry j;
    {
        long long res = j.howMany({1, 2, 5, 3, 4, 5});
        printf("%lld\n", res);
        assert(res == 9);
    }
    {
        long long res = j.howMany({1000,1000,1000,1000,1000,
                                   1000,1000,1000,1000,1000,
                                   1000,1000,1000,1000,1000,
                                   1000,1000,1000,1000,1000,
                                   1000,1000,1000,1000,1000,
                                   1000,1000,1000,1000,1000});
        printf("%lld\n", res);
        assert(res == 18252025766940LL);
    }

    return 0;
}



/*
 * wrong, counting the same combinations multiple times.
 * long long res = 0;

        for(int d = 1; d < values.size() -1 ; ++d) {

            vector<int> A(0, 30001);
            vector<int> B(0, 30001);

            int maxa = 0;
            int maxb = 0;

            A[0] = 1;
            B[0] = 1;

            for(int i = 0 ; i < d; ++i) {
                for(int j = maxa ; j >= 0; j--) {
                    if(A[j]) {
                        A[j + values[i]] += A[j];
                        maxa = max(maxa, j + values[j]);
                    }
                }
            }

            for(int i = d ; i < values.size(); ++i) {
                for(int j = maxb ; j >= 0; j--) {
                    if(A[j]) {
                        A[j + values[i]] += A[j];
                        maxb = max(maxb, j + values[j]);
                    }
                }
            }

            for(int i = 1; i < )
        }
 */