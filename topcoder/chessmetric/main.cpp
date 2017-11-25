#include <vector>
#include <cstdio>
using namespace std;

class ChessMetric {
public:
	long long howMany(int size, vector <int> start, vector <int> end, int numMoves) {
		
		vector<pair<int, int> > valid_moves;
		for(int i = -1; i <= 1; ++i)
		for(int j = -1; j <= 1; ++j) {
			if(i != 0 || j != 0)
			valid_moves.push_back(make_pair(i,j));
			
			if(i != 0 && j != 0) {
				valid_moves.push_back(make_pair(i, j*2));
				valid_moves.push_back(make_pair(i*2, j));
			}
		}	
		
		for(auto &m : valid_moves) {
			printf("%d %d\n", m.first, m.second);
		}
		
		long long T[101][101][52];
		for(int i = 0; i < size; ++i)
		for(int j = 0; j < size; ++j)
		for(int n = 0; n <= numMoves; ++n) T[i][j][n] = 0;
		
		T[start[0]][start[1]][0] = 1;
		
		for(int n = 0; n <= numMoves; ++n) {
		for(int i = 0; i < size; ++i)
		for(int j = 0; j < size; ++j)
		if(T[i][j][n] > 0)
		for(const auto &m : valid_moves) {
			int ni = i + m.first;
			int nj = j + m.second;
			if(ni >= 0 &&  ni < size && nj >= 0 && nj < size) {
				T[ni][nj][n+1] += T[i][j][n];
			}
		}

			/*for(int i = 0; i < size; ++i) {
				for(int j = 0; j < size; ++j) {
					printf("%lld\t", T[i][j][n]);
				}
				printf("\n");
			}	
			printf("\n");*/
		}
		
		return T[end[0]][end[1]][numMoves];
	
	}
};
