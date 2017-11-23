#include <vector>
#include <cassert>

using namespace std;

class ZigZag {
public:
    int longestZigZag(vector <int> A) {

        int T[51][2];

        T[0][0] = 1;
        T[0][1] = 1;

        for(int i = 1; i < A.size(); ++i) {
            T[i][0] = T[i-1][0];
            T[i][1] = T[i-1][1];

            for(int j = 0; j < i; ++j) {
                if(A[j] < A[i]) T[i][0] = max(T[i][0], 1 + T[j][1]);
                if(A[j] > A[i]) T[i][1] = max(T[i][1], 1 + T[j][0]);
            }
        }

        return max(T[A.size()-1][0], T[A.size()-1][1]);
    }
};

int main() {

    ZigZag z;
    assert(z.longestZigZag({ 1, 7, 4, 9, 2, 5 }) == 6);
    assert(z.longestZigZag({ 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 }) == 7);
    assert(z.longestZigZag({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }) == 2);
    assert(z.longestZigZag({ 70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32 }) == 8);

    return 0;
}