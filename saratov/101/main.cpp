#include <cstdio>
#include <list>
#include <set>
#include <cassert>
#include <vector>

using namespace std;

struct edge {
    int a,b;
//    bool used;
};

set<int> V[7];

edge e[102];

#ifdef ONLINE_JUDGE
bool debug = false;
#else
bool debug = true;
#endif

int fake_edge = -1;

void dfs(int v, list<pair<int, bool> > &result) {
    bool got_edge = false;
    int idx;
    {
        while(!got_edge && !V[v].empty()) {
            idx = *V[v].begin();

            V[e[idx].a].erase(idx);
            V[e[idx].b].erase(idx);
            got_edge = true;
//            e[idx].used = true;
        }
    }

    if(!got_edge) return;

    bool rotated = e[idx].a != v;
    result.push_back(make_pair(idx, rotated));

    dfs(e[idx].a == v ? e[idx].b : e[idx].a, result);
}

int main() {
    int N;
    list<pair<int, bool> > global_result;

    int evs[7];
    for(int i = 0 ; i < 7; ++i) evs[i] = 0;

    scanf("%d", &N);
    for(int i = 0 ; i < N; ++i) {
        int A,B;
        scanf("%d %d", &A, &B);
        e[i].a = A;
        e[i].b = B;
//        e[i].used = false;
        V[A].insert(i);
        V[B].insert(i);
        evs[A]++;
        evs[B]++;
    }

    int start_point = -1;

    {
        vector<int> even;

        for (int i = 0; i < 7; ++i) {
            if(evs[i] % 2) {
                even.push_back(i);
            }
            if(!V[i].empty() && start_point == -1) {
                start_point = i;
            }
        }

        if(!(even.empty() || even.size() == 2)) {
            printf("No solution\n");
            return 0;
        }

        if(!even.empty()) { //adding fake edge for Hierholzer algorithm to work
            if(debug) printf("adding fake edge %d %d (%d)\n", even[0], even[1], N);
            fake_edge = N;
            e[fake_edge].a = even[0];
            e[fake_edge].b = even[1];

            V[even[0]].insert(fake_edge);
            V[even[1]].insert(fake_edge);
            N++;
        }
    }

    if(start_point != -1) {
        dfs(start_point, global_result);
    }

    if(debug) {
        for (auto it = global_result.begin(); it != global_result.end(); ++it) {
            auto v1 = it->second ? e[it->first].b : e[it->first].a;
            auto v2 = it->second ? e[it->first].a : e[it->first].b;
            printf("%d %d %1c (%d)\n", v1, v2, it->second ? '-' : '+', it->first);
        }
        printf("--\n");
    }

    while(global_result.size() != N) {

        int begin_vert;
        auto it = global_result.begin();
        bool done = false;
        for(; !done && it != global_result.end() ; ++it) {
            auto &oe = e[it->first];
            auto v1 = it->second ? oe.a : oe.b;
            if(!V[v1].empty()) {
                begin_vert = v1;
                done = true;
            }
        }

        /*
         * it's sufficient to check only oe.a. Because oe.b == (oe+1).a, and last V[(last).b] cannot be empty,
         * cause first dfs would not have ended in such case
         */

        if(done == false) { //this basically means that graph is disconnected
            printf("No solution\n");
            return 0;
        }

        list<pair<int, bool> > sub_result;
        dfs(begin_vert, sub_result);

        if(it != global_result.begin()) {
//            it--;
            global_result.insert(it, sub_result.begin(), sub_result.end());
        } else {
            sub_result.insert(sub_result.end(), global_result.begin(), global_result.end());
            swap(global_result, sub_result);
        }

        if(debug) {
            for (auto it = global_result.begin(); it != global_result.end(); ++it) {
                auto v1 = it->second ? e[it->first].b : e[it->first].a;
                auto v2 = it->second ? e[it->first].a : e[it->first].b;
                printf("%d %d %1c (%d)\n", v1, v2, it->second ? '-' : '+', it->first);
            }
            printf("--\n");
        }
    }

    if(fake_edge != -1) { //we used a fake edge

        if(debug) printf("removing fake edge (%d)\n", fake_edge);

        auto it = global_result.begin();
        for(;it != global_result.end(); ++it) {
            if(it->first == fake_edge) break;
        }

        list<pair<int, bool> > newresult;
        auto it2 = it;
        it2++;
        newresult.insert(newresult.end(), it2, global_result.end());
        newresult.insert(newresult.end(), global_result.begin(), it);
        swap(global_result, newresult);

        if(debug) {
            for (auto it = global_result.begin(); it != global_result.end(); ++it) {
                auto v1 = it->second ? e[it->first].b : e[it->first].a;
                auto v2 = it->second ? e[it->first].a : e[it->first].b;
                printf("%d %d %1c (%d)\n", v1, v2, it->second ? '-' : '+', it->first);
            }
            printf("--\n");
        }
    }

    //a check

    for(auto it = global_result.begin(); it != global_result.end(); ++it) {
        auto it2 = it;
        it2++;
        if(it2 != global_result.end()) {
            auto &e1 = e[it->first];
            auto &e2 = e[it2->first];

            int v1 = it->second ? e1.a : e1.b;
            int v2 = it2->second ? e2.b : e2.a; //because that's the secondary
            assert(v1 == v2);
        }
    }

    //print res

    for(auto it = global_result.begin(); it != global_result.end(); ++it) {
        printf("%d %1c\n", it->first+1, it->second ? '-' : '+');
    }

    return 0;
}