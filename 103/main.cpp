#include <cstdio>
#include <vector>
#include <cassert>
#include <map>

using namespace std;

struct Edge {
    short target;
    char len;
};

char op[2] = {1, 0};

struct Vertex {
    vector<Edge> e;
    char init_color;
    char len[2];
    char len_init;

    multimap<int, int>::iterator priority_it;
    int arrival_from;
    bool is_set;

    char get_color_and_next_change_for_time(const int t0, int &out_t1) const {
        if(t0 < len_init) {
            out_t1 = len_init;
            return init_color;
        } else if(t0 == len_init) {
            out_t1 = len_init;
            return op[init_color];
        }

        int deltat = (t0 - len_init) % (len[0] + len[1]);

        if(deltat < len[op[init_color]]) {
            int change = len[op[init_color]] - deltat;
            out_t1 = t0 + change;
            return op[init_color];
        } else {
            int change = len[0] + len[1] - deltat;
            out_t1 = t0 + change;
            return init_color;
        }
    }
};

bool earliest_depart(const vector<Vertex *> v, int t0, int &out_res) {
    assert(v.size() == 2);
    char cc[2]; //current color
    int t[2];
    cc[0] = v[0]->get_color_and_next_change_for_time(t0, t[0]);
    cc[1] = v[1]->get_color_and_next_change_for_time(t0, t[1]);
    if(cc[0] == cc[1]) {
        out_res = t0;
        return true;
    }
    if(t[0] != t[1]) {
        size_t cv = t[0] < t[1] ? 0 : 1;
        out_res = t[cv];
        return true;
    }

    //no intersection ever
    if(v[0]->len_init == v[1]->len_init &&
       v[0]->len[0] == v[1]->len[1] &&
       v[0]->len[1] == v[1]->len[0] &&
       v[0]->init_color != v[1]->init_color) {
        out_res = -1;
        return false;
    }

    //if we got here, we have cc[0] != cc[1] && t[0] == t[1]

    while(cc[0] != cc[1] && t[0] == t[1]) {
        //cv - current vertex
        size_t cv = t[0] < t[1] ? 0 : 1;
        int prevt = t[cv];

        t[cv] += v[cv]->len[cc[cv]];
        cc[cv] = op[cc[cv]];

        if(t[op[cv]] == prevt) {
            cv = op[cv];
            t[cv] += v[cv]->len[cc[cv]];
            cc[cv] = op[cc[cv]];
        }
    }

    out_res = min(t[0], t[1]);
    return true;
}

void test_earliest_depart() {
//    {
//        Vertex v1, v2;
//        v1.init_color = 1;
//        v2.init_color = 0;
//
//        v1.len[0] = 3;
//        v1.len[1] = 4;
//
//        v2.len[0] = 4;
//        v2.len[1] = 2;
//
//        v1.len_init = 1;
//        v2.len_init = 1;
//
//        int int_res;
//        bool res = earliest_depart({&v1, &v2}, 1, int_res);
//        assert(res);
//        assert(int_res == 4);
//    }

    {
        Vertex v1, v2;
        v1.init_color = 0;
        v2.init_color = 0;

        v1.len[0] = 4;
        v1.len[1] = 4;

        v2.len[0] = 4;
        v2.len[1] = 4;

        v1.len_init = 1;
        v2.len_init = 4;

        int int_res;
        bool res = earliest_depart({&v1, &v2}, 1, int_res);
        assert(res);
        assert(int_res == 1);
    }

    {
        Vertex v1, v2;
        v1.init_color = 0;
        v2.init_color = 1;

        v1.len[0] = 3;
        v1.len[1] = 4;

        v2.len[0] = 4;
        v2.len[1] = 3;

        v1.len_init = 5;
        v2.len_init = 5;

        int int_res;
        bool res = earliest_depart({&v1, &v2}, 1, int_res);
        assert(!res);
//        assert(int_res == 1);
    }
}

Vertex V[302];

int N, M;
int source, target;

multimap<int, int> priority;

int main() {
    test_earliest_depart();

    scanf("%d %d", &source, &target);
    scanf("%d %d", &N, &M);

    for(int i = 0 ; i < N ; ++i) {
        char c;
        int len_init, len_b, len_p;
        scanf("%1c %d %d %d", &c, &len_init, &len_b, &len_p);
        V[i].init_color = c == 'B' ? 0 : 1;
        V[i].len_init = len_init;
        V[i].len[0] = len_b;
        V[i].len[1] = len_p;
    }

    for(int i = 0 ; i < M; ++i) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        Edge e;
        e.len = l;
        e.target = a;
        V[b].e.push_back(e);
        e.target = b;
        V[a].e.push_back(e);
    }

    for(int i = 1 ; i <= N; ++i) {
        V[i].priority_it = priority.end();
        V[i].arrival_from = -1;
        V[i].is_set = false;
    }

    int target_dist;

    //dijkstra
    priority.insert(make_pair(0, source));
    while(!priority.empty()) {
        const auto it = priority.begin();
        const auto t = it->first;
        const auto vi = it->second;
        const auto v = &V[vi];
        assert(!v->is_set);
        v->is_set = true;
        priority.erase(it);

        if(vi == target) target_dist = t;

        for(auto &e : v->e) {
            int earliest_depart_time;
            auto vt = &V[e.target];
            if(vt->is_set) continue;
            bool depart_possible = earliest_depart({v, vt}, t, earliest_depart_time);
            if(depart_possible) {
                int arrival_time = earliest_depart_time + e.len;

                if(vt->priority_it != priority.end() && vt->priority_it->first > arrival_time) {
                    priority.erase(vt->priority_it);
                    vt->priority_it = priority.end();
                }

                if(vt->priority_it == priority.end()) {
                    vt->priority_it = priority.insert(make_pair(e.target, arrival_time));
                    vt->arrival_from = vi;
                }
            }
        }
    }

    if(!V[target].is_set) {
        printf("0\n"); // no path
    } else {
        vector<int> track;
        int it = target;
        while(true) {
            track.push_back(it);
            if(it == source) break;
            it = V[it].arrival_from;
        }

        printf("%d\n", target_dist);
        for(int i = track.size() -1 ; i >= 0; --i) {
            printf("%d ", track[i]);
        }
    }


    return 0;
}