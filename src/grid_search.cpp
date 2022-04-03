#include "neighbourhood.h"

using namespace std;

void addPoints(int i, int j, vector<int>& points, vector<vector<int>>& originals, int n, int m, int c) {
	int result = referee(n,m,c,n*m, originals[i], originals[j]);
	if (result == TIE) {
		points[i] += TIE_POINTS;
		points[j] += TIE_POINTS;
	} else if (result == 1) {
		points[i] += WIN_POINTS;
	} else {
		points[j] += WIN_POINTS;
	}
}

vector<int> maximum(vector<int>& points, vector<vector<int>>& originals) {
	int max = points[0];
	int index = 0;
	for (int i = 0; i < points.size(); ++i) {
		if(points[i] > max) {
			max = points[i];
			index = i;
		}
	}

	return originals[index];
}

void tournament(vector<vector<int>> &originals, int n, int m, int c) {
	vector<int> points(originals.size(),0);
	
	for (int i = 0; i < originals.size(); ++i) {
		for (int j = i+1; j < originals.size(); ++j) {
			addPoints(i, j, points, originals, n, m, c);
			addPoints(j, i, points, originals, n, m, c);
		}
	}

	printVector(maximum(points, originals));
}

int random_value_for_parameter(int parameter) {
	return inferior_limit(parameter) + (rand() % ((superior_limit(parameter) - inferior_limit(parameter) + 1)/ delta(parameter))) * delta(parameter);
}


int main() {
	int n,m,c;
	cin >> n >> m >> c;
	vector<vector<int>> originals;
	srand(time(NULL));
	for (int i = 0; i < 2; ++i) {
		vector<int> tmp;
		for (int j = 0; j < AMOUNT_PARAMETERS; ++j) {
			tmp.push_back(random_value_for_parameter(j));
		}
		originals.push_back(tmp);
	}
	

	/*originals.push_back({20,1,16,8,5,5});
	originals.push_back({90,3,8,16,5,5});
	originals.push_back({20,4,11,6,4,3});
	originals.push_back({1,3,5,4,2,1});
	originals.push_back({10,1,9,13,5,4});
	originals.push_back({10,3,9,8,3,3});
	originals.push_back({30,2,7,12,0,6});
	originals.push_back({60,1,13,5,8,8});
	*/
	for (int i = 0; i < originals.size(); ++i) {
		bool finished = false;
		for (int j = 0; j < AMOUNT_GRID_SEARCH and not finished; ++j) {
			Neighbourhood neigh(originals[i], n, m ,c);
			vector<int> best = neigh.get_best();
			cout << "Original:";
			printVector(originals[i]);
			cout << "Best:";
			printVector(best);
			cerr << "i:" << i << " j:" << j << endl;
			if(originals[i] == best) {
				finished = true;
			} else {
				originals[i] = best;
			}
		}
	}
	//free 4 all
	cout << "Finalistas:" << endl;
	for (int i = 0; i < originals.size(); ++i) {
		printVector(originals[i]);
	}
	cout << "Ganador: ";
	tournament(originals, n, m, c);
	return 0;
}