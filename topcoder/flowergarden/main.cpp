//the problem is listed in DP tutorial but it begs for greedy solution. I write one to see if it goes through tests.

#include <vector>
#include <cassert>
#include <tuple>
#include <algorithm>
#include <set>

using namespace std;

bool collide(const tuple<int, int,int> &a, const tuple<int, int, int>&b) {
    if(get<1>(b) <= get<1>(a) && get<1>(a) <= get<2>(b)) return true;
    if(get<1>(b) <= get<2>(a) && get<2>(a) <= get<2>(b)) return true;
    if(get<1>(a) <= get<1>(b) && get<1>(b) <= get<2>(a)) return true;
    if(get<1>(a) <= get<2>(b) && get<2>(b) <= get<2>(a)) return true;
    return false;
}

//in brut force I use indices in ordering, not heights

bool isOrderingGood(const vector<int>& ordering, const vector<tuple<int, int, int> >& flowers) {
    for(int i = 1; i < ordering.size(); ++i) {
        for(int j = 0; j < i; ++j) {
            if(get<0>(flowers[ordering[j]]) > get<0>(flowers[ordering[i]])) {
                if(collide(flowers[ordering[i]], flowers[ordering[j]])) return false;
            }
        }
    }
    return true;
}

//does not check correctness!
static bool isBetter(const vector<int>& old_ordering, const vector<int>& new_ordering, const vector<tuple<int, int, int> >& flowers) {
    if(old_ordering.size() == 0) return true;

    assert(old_ordering.size() == new_ordering.size());
    for(int i = 0; i < old_ordering.size() ; ++i) {
        if(get<0>(flowers[new_ordering[i]]) > get<0>(flowers[old_ordering[i]])) {
            return true;
        }
    }
    return false;
}

class IFlowerGarden {
public:
    virtual vector <int> getOrdering(vector <int> height, vector <int> bloom, vector <int> wilt) = 0;
};

class FlowerGardenBrut : public IFlowerGarden {

    void brut(const vector<tuple<int, int, int> >& flowers, vector<bool> &used, vector<int>& curr_ordering, vector<int>& best_ordering) {
        if(curr_ordering.size() == flowers.size()) {
            if(isOrderingGood(curr_ordering, flowers) && isBetter(best_ordering, curr_ordering, flowers)) best_ordering = curr_ordering;
        } else {
            for(int i = 0 ; i < flowers.size(); ++i) {
                if(used[i] == false) {
                    used[i] = true;
                    curr_ordering.push_back(i);
                    brut(flowers, used, curr_ordering, best_ordering);
                    curr_ordering.pop_back();
                    used[i] = false;
                }
            }
        }
    }

public:
    vector <int> getOrdering(vector <int> height, vector <int> bloom, vector <int> wilt) {
        vector<tuple<int, int, int>> flowers;
        for(int i = 0 ; i < height.size(); ++i) {
            flowers.push_back(make_tuple(height[i], bloom[i], wilt[i]));
        }

        sort(flowers.begin(), flowers.end());

        vector<bool> used(flowers.size());
        vector<int> best_ordering, curr_ordering;
        brut(flowers, used, curr_ordering, best_ordering);

        vector<int> res;

        for(int i = 0 ; i < best_ordering.size(); ++i) {
            res.push_back(get<0>(flowers[best_ordering[i]]));
        }

        return res;
    }
};

class FlowerGarden : public IFlowerGarden {
public:
    vector <int> getOrdering(vector <int> height, vector <int> bloom, vector <int> wilt) {

        vector<int> res;
        vector<bool> used(height.size(), false);

        while(res.size() < height.size()) {
            int h = -1;
            int idx = -1;
            for (int i = 0; i < height.size(); ++i) {
                if(!used[i]) {

                    bool freeToUse = true;

                    for(int j = 0 ; j < height.size(); ++j) {
                        if(!used[j] && height[j] < height[i] &&
                           collide(make_tuple(0, bloom[j], wilt[j]), make_tuple(0, bloom[i], wilt[i]))) {
                            freeToUse = false; break;
                        }
                    }

                    if(freeToUse && h < height[i]) {
                        h = height[i];
                        idx = i;
                    }

                }
            }

            used[idx] = true;
            res.push_back(height[idx]);
        }

        return res;
    }
};


int main() {

    int sample = 6;
    srand(7);

    bool done = false;
    while(!done) {
        vector<int> a,b,c;

        for(int i = 0 ; i < sample; ++i) {
            int ai = i+1;
            int bi = rand() % (3*sample);
            int ci = rand() % (3*sample);
            if(bi < 0) bi *= -1;
            if(ci < 0) ci *= -1;
            if(bi > ci) swap(bi,ci);
            a.push_back(ai);
            b.push_back(bi);
            c.push_back(ci);
        }

        FlowerGarden f;
        FlowerGardenBrut fb;

        vector<int> resa = f.getOrdering(a,b,c);
        vector<int> resb = fb.getOrdering(a,b,c);

        if(resa != resb) {
            done = true;

            printf("h:\t");
            for(int i = 0 ; i < sample; ++i) printf("%d\t", a[i]);
            printf("\n");

            printf("b:\t");
            for(int i = 0 ; i < sample; ++i) printf("%d\t", b[i]);
            printf("\n");

            printf("t:\t");
            for(int i = 0 ; i < sample; ++i) printf("%d\t", c[i]);
            printf("\n");

            vector<tuple<int, int, int>> flowers;
            for(int i = 0 ; i < a.size(); ++i) {
                flowers.push_back(make_tuple(a[i], b[i], c[i]));
            }

            sort(flowers.begin(), flowers.end());

            for(int i = 1 ; i < sample; ++i) {
                for(int j = 0 ; j < i; ++j) {
                    if(collide(flowers[i], flowers[j])) {
                        printf("%d<->%d\t", j+1, i+1);
                    }
                }
            }
            printf("\n");


            printf("\n");
            printf("f:\t");
            for(int i = 0 ; i < sample; ++i) printf("%d\t", resa[i]);
            printf("\n");
            printf("fb:\t");
            for(int i = 0 ; i < sample; ++i) printf("%d\t", resb[i]);
            printf("\n");
        }

    }

/*
    {
        FlowerGarden f;
        vector<int> res = f.getOrdering({5, 4, 3, 2, 1},
                                        {1, 1, 1, 1, 1},
                                        {365, 365, 365, 365, 365});
        assert(res == vector<int>({1, 2, 3, 4, 5}));
    }

    {
        FlowerGarden f;
        vector<int> res = f.getOrdering({5, 4, 3, 2, 1},
                                        {1, 5, 10, 15, 20},
                                        {4, 9, 14, 19, 24});
        assert(res == vector<int>({5, 4, 3, 2, 1}));
    }

    {
        FlowerGarden f;
        vector<int> res = f.getOrdering({5, 4, 3, 2, 1},
                                        {1, 5, 10, 15, 20},
                                        {5, 10, 15, 20, 25});
        assert(res == vector<int>({1, 2, 3, 4, 5}));
    }

    {
        FlowerGarden f;
        vector<int> res = f.getOrdering({5, 4, 3, 2, 1},
                                        {1, 5, 10, 15, 20},
                                        {5, 10, 14, 20, 25});
        assert(res == vector<int>({3, 4, 5, 1, 2}));
    }
    {
        FlowerGarden f;
        vector<int> res = f.getOrdering({1, 2, 3, 4, 5, 6},
                                        {1, 3, 1, 3, 1, 3},
                                        {2, 4, 2, 4, 2, 4});
        assert(res == vector<int>({2, 4, 6, 1, 3, 5}));
    }

    {
        FlowerGarden f;
        vector<int> res = f.getOrdering({3, 2, 5, 4},
                                        {1, 2, 11, 10},
                                        {4, 3, 12, 13});
        assert(res == vector<int>({4, 5, 2, 3}));
    }

    {
        FlowerGarden f;
        vector<int> res = f.getOrdering(
            {401, 267, 259, 760, 846, 105, 126, 717, 669, 864, 449, 87, 276, 670, 861, 60, 660, 28, 94, 788, 111, 305, 580, 848, 163, 112, 355},
            {219, 345, 30, 234, 14, 338, 301, 69, 50, 204, 33, 85, 137, 293, 50, 304, 227, 330, 309, 286, 349, 185, 291, 339, 339, 157, 290},
            {343, 358, 365, 336, 295, 350, 351, 84, 52, 324, 363, 356, 183, 350, 222, 329, 362, 342, 358, 305, 356, 363, 365, 343, 350, 311, 353});
        assert(res == vector<int>({60, 28, 87, 94, 112, 105, 111, 126, 163, 259, 276, 267, 305, 355, 401, 449, 717, 669, 580, 660, 670, 848, 760, 788, 846, 861, 864}));
    }*/

    return 0;
}