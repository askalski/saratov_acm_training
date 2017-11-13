#ifdef ONLINE_JUDGE
const bool debug = false;
#else
const bool debug = true;
#endif

#include <cstdio>
#include <vector>
#include <algorithm>
#include <list>
#include <tuple>
#include <map>
#include <set>
#include <cassert>

using namespace std;

int main() {

    int N;
    scanf("%d", &N);
    vector<tuple<int, int, int> > people;
    set<pair<int,int> > coords; //just to remove duplicates.

    int maxx = -1, maxy = -1;

    for(int i = 1 ; i <= N; ++i) {
        int s,b;
        scanf("%d %d", &s, &b);

        auto c = make_pair(s,b);
        if(coords.find(c) != coords.end()) continue; //ignore duplicate guy.
        coords.insert(c);

        people.push_back(make_tuple(s,-b, i));//trust me, I am an engineer.

        maxx = max(maxx, s);
        maxy = max(maxy, b);
    }
    sort(people.begin(), people.end());
    for(auto &p : people) get<1>(p) *= -1; //because we want to consider them in decreasing y order.

    /*
     * this will simulate one way linked list.
     * I store predecessor INDEX in people array, not club member id! -1 stands for empty list.
     */
    vector<pair<int, int> > queue(people.size());
    for(int i = 0 ; i < queue.size(); ++i) {
        queue[i] = make_pair(-1, 1); //initially each one forms a single element queue with no predecessor
    }

    map<int, int> compressed_row; //key - y (column index), value - index in queue/people array

    int row = 1;

    for(int i = 0 ; i < people.size(); ++i) {
        auto &p = people[i];

        if(compressed_row.empty()) { //empty
            compressed_row.insert(make_pair(get<1>(p), i));
        } else {
            auto it = compressed_row.upper_bound(get<1>(p)); //it points first to the element that has a strictly higher y

            if (it != compressed_row.begin()) {
                auto pred = it;
                pred--; //exists since !empty and it != begin()
                //pred points to element that has lower or equal y

                if(get<1>(people[pred->second]) == get<1>(p)) {
                    //they have the same y coordinate. In such case, I always choose the one with lower x and discard
                    //the latter. the lower x has been processed first, so noop.
                } else {
                    //now we know, that     people[pred->second].y < p.y
                    //also we know, that    people[pred->second].x < p.x,
                    //because all elements with equal x in compressed_row have HIGHER y (clever sorting!)
                    //and elements with higher x haven't been introduced yet!
                    assert(get<1>(people[pred->second]) < get<1>(p));
                    assert(get<0>(people[pred->second]) < get<0>(p));
                    //"know" :)

                    //so we introduce it
                    auto new_it = compressed_row.insert(make_pair(get<1>(p), i)).first;
                    queue[i].first = pred->second;
                    queue[i].second = queue[pred->second].second + 1;

                    //however! we might need to remove it's successor (if it exists)
                    auto succ = new_it;
                    succ++;
                    if(succ != compressed_row.end()) {
                        compressed_row.erase(succ);
                    }
                }
            } else {
                // The y coordinate is lowest witnessed so far. This guy will be the new beginning of 1 in the row. Also,
                // we know that the compressed_row is not empty, so it has a successor, the previous beginning of '1'.
                // We can replace it.
                compressed_row.erase(it);
                compressed_row.insert(make_pair(get<1>(p), i));
            }
        }

        if(debug && max(maxx, maxy) + 1 <= 20) {
            row = get<0>(p);

            int curr_column = 1;
            int curr_val = 0;
            int last_guy = -1;
            printf("%d:\t", row);

            for(auto it = compressed_row.begin(); it != compressed_row.end() ; ++it) {
                for(;curr_column < it->first; curr_column++) {
                    printf("[%3d, %3d]\t", curr_val, last_guy);
                }
                last_guy = get<2>(people[it->second]);
                curr_val++;
            }

            for(;curr_column <= maxy; curr_column++) {
                printf("[%3d, %3d]\t", curr_val, last_guy);
            }
            printf("\n");
        }
    }

    //the result corresponds to the last value in the row.
    int last = compressed_row.rbegin()->second;
    printf("%d\n", queue[last].second);

    vector<int> res;
    while(last != -1) {
        res.push_back(get<2>(people[last]));
        last = queue[last].first;
    }

    for(int i = res.size() - 1; i >= 0; --i) {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}