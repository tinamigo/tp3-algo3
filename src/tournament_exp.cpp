#include "generation.h"
#include <string>

using namespace std;

int find(vector<vector<int>>& v, vector<int>& elem);

int main(int argc, char const *argv[]) {
	vector<vector<int>> v;
	int n,m,c;
	cin >> n >> m >> c;
	//recibir los jugadores
	for (int i = 0; i < 36; ++i) {
		string param;
		cin >> param;
		vector<int> tmp;
		int desde = 0;
		int hasta;
		bool first = true;
		for (hasta = 0; hasta < param.size(); ++hasta) {
			if(param[hasta] == ',' and first) {
				first = false;
				desde = hasta+1;
			} else if(param[hasta] == ',') {
				tmp.push_back(stoi((string)param.substr(desde,(hasta-desde))));
				desde = hasta+1;
			}
		}
		v.push_back(tmp);
	}

	Generation 	gen(v, n, m, c, 0, 0, 0, 0);
	gen.free_for_all( 0, v.size());
	gen.sort_by_points();
	/*
	vector<int> ganador = gen.citizen(0);
	vector<int> segundo = gen.citizen(1);
	vector<int> tercero = gen.citizen(2);
	cout << find(v, ganador) << " " << gen.points(0) << " ";
	printVector(ganador);
	cout << find(v, segundo) << " " << gen.points(1) << " ";
	printVector(segundo);
	cout << find(v, tercero) << " " << gen.points(2) << " ";
	printVector(tercero);
	*/

	for (int i = 0; i < 36; ++i){
		vector<int> player = gen.citizen(i);
		cout << find(v, player) << " " << gen.points(i) << " ";
		printVector(player);	
	}

	return 0;
}

int find(vector<vector<int>>& v, vector<int>& elem) {
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] == elem) {
			return i;
		}
	}
	return 0;
}

