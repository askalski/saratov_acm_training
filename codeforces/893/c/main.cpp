#include <cstdio>
#include <vector>
#include <climits>

using namespace std;

constexpr int maxV = (500*1000+1);

vector<vector<int> > G(maxV);
vector<bool> Visited(maxV);
vector<long> Cost(maxV);

long dfs(int v) {
    long c1 = Cost[v];

    Visited[v] = true;

    for(auto t : G[v]) {
        if(!Visited[t]) {
            long tmp = dfs(t);
            c1 = min(tmp, c1);
        }
    }

    return c1;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    for(int i = 1 ; i <= V ; ++i) scanf("%ld", &Cost[i]);

    for(int i = 0 ; i < E; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    long long res = 0;
    for(int i = 1; i <= V; ++i) {
        if(!Visited[i]) {
            long tmp = dfs(i);
            res += tmp;
        }
    }

    printf("%lld\n", res);


    return 0;
}