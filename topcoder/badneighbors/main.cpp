//fixed! took me brut force to find counterexample. Damn you TC!

#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class IBadNeighbors {
public:
    virtual int maxDonations(vector <int> A) = 0;
};

class BadNeighborsBrut : public IBadNeighbors {
public:

    void brut_try(vector<int> &A, vector<bool> &B, int idx, int &best, vector<bool> &bestB) {
        if(idx == A.size()) {
            int tmpres = 0;
            for(int i = 0 ; i < A.size(); ++i) {
                if(B[i]) tmpres += A[i];
            }
            if(tmpres > best) {
                best = tmpres;
                bestB = B;
            }
        } else {
            if(idx == 0) {
                B[idx] = false;
                brut_try(A, B, idx+1, best, bestB);
                B[idx] = true;
                brut_try(A, B, idx+1, best, bestB);
            } else if(idx >= 0 && idx < A.size() - 1) {
                if(B[idx-1] == false) {
                    B[idx] = true;
                    brut_try(A, B, idx+1, best, bestB);
                }
                B[idx] = false;
                brut_try(A, B, idx+1, best, bestB);
            } else {
                if(B[0] == false && B[idx-1] == false) {
                    B[idx] = true;
                    brut_try(A, B, idx+1, best, bestB);
                }
                B[idx] = false;
                brut_try(A, B, idx+1, best, bestB);
            }
        }
    }

    int maxDonations(vector <int> A) {
        vector<bool> B(A.size());
        vector<bool> resB(A.size());
        int best = 0;

        brut_try(A, B, 0, best, resB);

        for(int i = 0 ; i < resB.size(); ++i) {
            printf("%s", resB[i] ? "T\t" : "F\t");
        }
        printf("\n");

        return best;
    }
};

class BadNeighbors : public IBadNeighbors {
public:

    int maxDonationsNoCircle(vector<int> A) {

        if(A.size() <= 3) {
            return *std::max_element(A.begin(), A.end());
        }

        int T[45];

        T[0] = A[0];
        T[1] = A[1];
        T[2] = A[0] + A[2];

        for(int i = 3; i < A.size(); ++i) {
            T[i] = A[i] + std::max(T[i-2], T[i-3]);
        }

        for(int i = 0 ; i < A.size(); ++i) {
            printf("%d\t", T[i]);
        }
        printf("\n");

        return std::max(T[A.size()-2], T[A.size()-1]);
    }

    int maxDonations(vector <int> A) {

        vector<int> A1(A);
        A1.pop_back();
        vector<int> A2;
        for(int i = 1 ; i < A.size(); ++i) A2.push_back(A[i]);


        int res1 = maxDonationsNoCircle(A1);
        int res2 = maxDonationsNoCircle(A2);
        return std::max({res1, res2});
    }
};

int main() {
//    BadNeighborsBrut b;

//    printf("%d\n", b.maxDonations({ 10, 3, 2, 5, 7, 8 }));
//    assert(b.maxDonations({ 10, 3, 2, 5, 7, 8 }) == 19);
//    printf("%d\n", b.maxDonations({ 7, 7, 7, 7, 7, 7, 7 }));
//    assert(b.maxDonations({ 7, 7, 7, 7, 7, 7, 7 }) == 21);

    srand(7);

    IBadNeighbors * b[2] = {new BadNeighborsBrut(), new BadNeighbors()};

    bool done = false;
    while(!done) {

        vector<int> data;
        for(int i = 0; i < 7; ++i) {
            data.push_back(rand() % 10);
            if(data[i] < 0) data[i] *= -1;
        }

        int res1 = b[0]->maxDonations(data);
        int res2 = b[1]->maxDonations(data);

        if(res1 != res2) {
            done = true;

            printf("res1 = %d, res2 = %d\n", res1, res2);

            for(int i = 0 ; i < data.size(); ++i) {
                printf("%d, ", data[i]);
            }
            printf("\n");
        }

    }

    delete b[0];
    delete b[1];

    return 0;
}