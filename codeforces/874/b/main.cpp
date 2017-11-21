#include <cstdio>
#include <vector>
using namespace std;

struct Cell {
    enum {
        Type_Unit,
        Type_Substr
    } Type;

    int Param;
};

inline void reduce(vector<Cell> &stack, int &best) {
    bool done = false;
    while(!done) {
        done = true;
        if(stack.size() > 1 &&
           stack[stack.size()-1].Type == Cell::Type_Substr &&
           stack[stack.size()-2].Type == Cell::Type_Substr)
        {
            stack[stack.size()-2].Param += stack[stack.size()-1].Param;
            best = max(best, stack[stack.size()-2].Param);
            stack.pop_back();
            done = false;
        }

        if(stack.size() > 1 &&
           stack[stack.size()-1].Type == Cell::Type_Unit &&
           stack[stack.size()-2].Type == Cell::Type_Unit &&
           stack[stack.size()-1].Param + stack[stack.size()-2].Param == 0) {
            stack[stack.size()-2].Type = Cell::Type_Substr;
            stack[stack.size()-2].Param = 2;
            best = max(best, stack[stack.size()-2].Param);
            stack.pop_back();
            done = false;
        }

        if(stack.size() > 2 &&
           stack[stack.size()-1].Type == Cell::Type_Unit &&
           stack[stack.size()-2].Type == Cell::Type_Substr &&
           stack[stack.size()-3].Type == Cell::Type_Unit &&
           stack[stack.size()-1].Param + stack[stack.size()-3].Param == 0) {
            stack[stack.size()-3].Type = Cell::Type_Substr;
            stack[stack.size()-3].Param = stack[stack.size()-2].Param + 2;
            best = max(best, stack[stack.size()-3].Param);
            stack.pop_back();
            stack.pop_back();
            done = false;
        }
    }
}

int main() {
    vector<Cell> stack;

    int N;
    int best = 0;
    scanf("%d\n", &N);

    for(int i = 0 ; i < N; ++i) {
        char c;
        scanf("%1c", &c);
        Cell cell;
        cell.Type = Cell::Type_Unit;
        cell.Param = c - '0';
        if(cell.Param == 0) cell.Param = -1;
        stack.push_back(cell);
        reduce(stack, best);
    }

    printf("%d\n", best);
    return 0;
}