#include "our_referee.h"
#include "generation.h"

using namespace std;

int main() {
	int n, m, c;
	cin >> n >> m >> c;
	int fitness, crossover, mutation, selection;
	cin >> fitness >> crossover >> mutation >> selection;
	// defino la poblacion inicial
	vector<vector<int>> v;
	v.push_back({33, 1, 6, 6, 3, 1});
	v.push_back({34, 2, 4, 14, 2, 1});
	v.push_back({82, 3, 3, 17, 1, 1});
	v.push_back({73, 1, 6, 5, 5, 1});
	v.push_back({66, 2, 14, 10, 1, 3});
	v.push_back({63, 2, 10, 5, 3, 8});
	v.push_back({61, 2, 10, 5, 3, 8});
	v.push_back({41, 2, 9, 4, 2, 8});
	v.push_back({54, 2, 11, 5, 3, 9});
	v.push_back({1, 2, 11, 6, 1, 8});
	v.push_back({3, 2, 10, 10, 8, 9});
	v.push_back({61, 3, 8, 2, 10, 5});
	v.push_back({11, 2, 8, 5, 3, 6});
	v.push_back({1, 2, 12, 9, 6, 7});
	v.push_back({1, 1, 0, 10, 3, 1});
	v.push_back({1, 1, 0, 1, 0, 7});
	/*for (int i = 0; i < 8; ++i) {
		vector<int> tmp;
		for (int j = 0; j < AMOUNT_PARAMETERS; ++j) {
			tmp.push_back(random_value_for_parameter(j));
		}
		v.push_back(tmp);
	}*/
	// creo una nueva generacion
	Generation gen(v, n, m, c, fitness, crossover, mutation, selection);
	cout << "Generacion,k,e,aa,da,af,df,puntos" << endl;
	for (int i = 0; i < AMOUNT_GENETIC; ++i) {
		vector<vector<int>> newbies = gen.get_new_generation();
		for (int j = 0; j < gen.size(); ++j) {
			cout << i <<",";
			for (int k = 0; k < AMOUNT_PARAMETERS; ++k) {
				cout << gen.citizen(j)[k] << ",";
			}
			cout << gen.points(j) << endl;
		}
		gen.set_new_generation(newbies);
	}

	return 0;
}