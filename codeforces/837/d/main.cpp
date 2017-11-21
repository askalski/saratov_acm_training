#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

//const int maxT = 200*64 + 1;
//int T[maxT][maxT];

struct pairhash {
public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &x) const
    {
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
    }
};

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    vector<pair<int, int> > v;

    for(int i = 0 ; i < N; ++i) {
        long long tmp;
        scanf("%lld", &tmp);
        int twos = 0, fives = 0;
        while(tmp % 2 == 0 && tmp > 0) {
            twos++;
            tmp /= 2;
        }

        while(tmp % 5 == 0 && tmp > 0) {
            fives++;
            tmp /= 5;
        }

        v.push_back(make_pair(twos,fives));
    }


    //I could use an array here, but I like maps.
//    for(int i = 0 ; i < maxT; ++i)
//        for(int j = 0 ; j < maxT; ++j) T[i][j] = -1;

    unordered_map<pair<int, int>, int, pairhash> M, newM; //coordinates -> minimal number of numbers used to reach these coordinates.

    M[make_pair(0,0)] = 0;

    for(const auto &c : v) {
        for(const auto &p : M) {
            if(p.second >= K) continue;
            newM[make_pair(c.first + p.first.first, c.second + p.first.second)] = p.second + 1;
        }

        for(const auto &np : newM) {
            const auto old = M.find(np.first);
            if(old == M.end() || old->second > np.second) {
                M[np.first] = np.second;
            }
        }
    }

    int best = 0;

    for(const auto &p : M) {
        best = max(best, min(p.first.first, p.first.second));
    }

    printf("%d\n", best);

    return 0;
}