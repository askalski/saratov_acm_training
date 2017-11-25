//this one work!
#include <string>
#include <vector>
using namespace std;

class QuickSums {
public:
static long long get_val(const vector<int> x, int i, int j) {
		long long val = x[i];
		for(int d = i+1; d<=j; ++d) {
			val *= 10;
			val += x[d];
		}
		return val;
}

int minSums(string numbers, int sum) {
	vector<int> x;
	for(int i = 0 ; i < numbers.size(); ++i) x.push_back(numbers[i] - '0');

	//printf("x.size() = %lu\n", x.size());

	int T[11][11][101];
	for(int i = 0 ; i < 11; ++i)
	for(int j = 0 ; j < 11; ++j)
	for(int k = 0 ; k <= sum; ++k) T[i][j][k] = -1;

	for(int l = 1; l <= x.size(); ++l) 
	for(int i = 0; i < x.size(); ++i)
	{
		int j = i+l-1;
		if(j >= x.size()) continue;
		//printf(".");
		//see if we can do zero
		long long val = get_val(x, i, j);
		//printf("val = %lld\n", val);
		
		if(val <= sum){
			T[i][j][val] = 0;
			//printf("T[%d][%d][%lld] = 0\n", i, j, val);
		}
		
		for(int d = i+1; d <= j; d++) {
			for(int s1 = 0; s1 <= sum; ++s1)
			for(int s2 = 0; s1+s2 <= sum; ++s2)
			{
				if(T[i][d-1][s1] != -1 && T[d][j][s2] != -1) {
					int cand = T[i][d-1][s1] + T[d][j][s2] + 1;
					if(T[i][j][s1+s2] == -1 || T[i][j][s1+s2] > cand){
						T[i][j][s1+s2] = cand;
						//printf("T[%d][%d][%d+%d] = %d\n", i, j, s1, s2, cand);
					}
				}
			}
		}
		
	}
	
	return T[0][x.size()-1][sum];

}
};
