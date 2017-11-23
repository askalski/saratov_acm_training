//the problem is listed in DP tutorial but it begs for greedy solution. I write one to see if it goes through tests.

#include <vector>
#include <cassert>
#include <tuple>
#include <algorithm>
#include <set>

using namespace std;

class FlowerGarden {
private:
    static bool collide(tuple<int, int,int> &a, tuple<int, int, int>&b) {
        if(get<1>(b) <= get<1>(a) && get<1>(a) <= get<2>(b)) return true;
        if(get<1>(b) <= get<2>(a) && get<2>(a) <= get<2>(b)) return true;
        if(get<1>(a) <= get<1>(b) && get<1>(b) <= get<2>(a)) return true;
        if(get<1>(a) <= get<2>(b) && get<2>(b) <= get<2>(a)) return true;
        return false;
    }

public:

    void position_itself(vector<int>& result, int idx, vector<tuple<int, int, int> >& flowers, set<int>& done) {
        if(done.find(get<0>(flowers[idx])) != done.end()) return;

        for(int j = idx-1; j >= 0; j--) {
            if(collide(flowers[j], flowers[idx])) {
                position_itself(result, j, flowers, done);
            }
        }

        result.push_back(get<0>(flowers[idx]));
        done.insert(get<0>(flowers[idx]));
    }

    vector <int> getOrdering(vector <int> height, vector <int> bloom, vector <int> wilt) {

        vector<tuple<int, int, int>> flowers;
        for(int i = 0 ; i < height.size(); ++i) {
            flowers.push_back(make_tuple(height[i], bloom[i], wilt[i]));
        }

        sort(flowers.begin(), flowers.end());

        vector<int> res;
        set<int> done;
        for(int i = flowers.size()-1; i >= 0; --i) position_itself(res, i, flowers, done);

        return res;
    }
};


int main() {

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
    }

    return 0;
}