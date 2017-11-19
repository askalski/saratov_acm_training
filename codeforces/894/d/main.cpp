#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

#define ull unsigned long long

using namespace std;

#define maxN (1000*1000+2)

struct Vertex {
    vector<ull> dist_below;
    vector<ull> partial_sums;
    ull dist_to_father;
} V[maxN];

int N, M;

size_t how_many_below(int n, ull H) {
    vector<ull>::iterator it = lower_bound(V[n].dist_below.begin(), V[n].dist_below.end(), H);
    return distance(V[n].dist_below.begin(), it);
}

ull sum_below(int n, ull H) {
    size_t how_many = how_many_below(n, H);
    ull summ = V[n].partial_sums[how_many-1];
    summ = H*how_many - summ;
    return summ;
}

ull sum_above(int n, ull H/*, int &how_many*/) {
    if(n == 1) {
        return 0;
    }


    int parent = n/2;
    int other_child = parent*2 == n ? parent*2+1 : parent*2;

    if(V[n].dist_to_father <= H) {
        ull res = 0;

        res += H - V[n].dist_to_father;
        res += sum_above(n/2, H-V[n].dist_to_father);

        ull sum_dist = V[n].dist_to_father + V[other_child].dist_to_father;

        if(sum_dist <= H) {
            res += sum_below(other_child, H-sum_dist);
        }

        return res;

    } else {
        return 0ull;
    }

}

int main() {

    scanf("%d %d", &N, &M);

    for(int i = 1 ; i < N; ++i) {
        int len;
        scanf("%d", &len);
        V[i+1].dist_to_father = len;
    }

    for(int n = N; n >= 1; n--) {
        V[n].dist_below.push_back(0); //myself

        int c1 = n*2;
        int c2 = n*2+1;

        //I should merge sort but there aint no time for that

        if(c1 <= N) {
            for(int i = 0 ; i < V[c1].dist_below.size(); ++i) {
                V[n].dist_below.push_back(V[c1].dist_to_father + V[c1].dist_below[i]);
            }
        }

        if(c2 <= N) {
            for(int i = 0 ; i < V[c2].dist_below.size(); ++i) {
                V[n].dist_below.push_back(V[c2].dist_to_father + V[c2].dist_below[i]);
            }
        }

        sort(V[n].dist_below.begin(), V[n].dist_below.end());

        ull part_sum = 0;
        for(int i = 0 ; i < V[n].dist_below.size(); ++i) {
            part_sum += V[n].dist_below[i];
            V[n].partial_sums.push_back(part_sum);
        }
    }

    for(int i = 0; i < M; ++i) {
        int v;
        ull h;
        scanf("%d %llu", &v, &h);

        ull res = sum_below(v, h);
//        printf("[%ull,\t", res);

        res += sum_above(v, h);
//        printf("%ull]\n", res);

        printf("%llu\n", res);
    }

    return 0;
}

