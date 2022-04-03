#include "neighbourhood.h"

using namespace std;

Neighbourhood::Neighbourhood(vector<int>& original, int n, int m, int c): _original(original), _n(n), _m(m), _c(c){
	string neigh = initial();
	_points[neigh] = 0;
	_presence[neigh] = (rand() % 100) <= 20;
	while(get_next(neigh)) {
		_points[neigh] = 0;
		_presence[neigh] = (rand() % 100) <= 20;
	}

}

vector<int> Neighbourhood::get_best() {
	string neigh = initial();
	do {
		string actual = neigh;
		while (get_next(actual)) {
			addPointsMatch(neigh, actual);
			addPointsMatch(actual, neigh);
		}
	} while (get_next(neigh));

	string iterator = initial();
	string id_max = iterator;

	while(get_next(iterator)) {
		if (_points[iterator] > _points[id_max]) id_max = iterator;
	}

	return player(id_max);
}

bool Neighbourhood::get_next(string& actual) {
	if (actual == "222222") { // si ya no puedo aumentar, devuelvo falso
		return false;
	}

	string initial = actual;
	while(increment(actual) and not valid(actual)) {}
	if (not valid(actual)) { // quiere decir que aumente hasta 222222 y no encontre valido
		actual = initial;
		return false;
	}
	return true;
}

string Neighbourhood::initial() {
	string res(ID_ORIGINAL);
	for (int i = 0; i < res.size(); ++i) {
		if (possibleDecrement(i)) res[i] = '0';
	}

	return res;
}

// Pre: me pasan un id válido
vector<int> Neighbourhood::player(string id) {
	vector<int> res(_original);
	assert(res.size() == id.size());
	for (int i = 0; i < res.size(); ++i) {
		if (id[i] == '0') {
			res[i] -= delta(i);
		} else if(id[i] == '2') {
			res[i] += delta(i);
		}
	}

	return res;
}

void Neighbourhood::addPointsMatch(string& id1, string& id2) {
	if (_presence[id1] and _presence[id2]) {
		int result1 = referee(_n,_m,_c,_n*_m, player(id1), player(id2));
		if (result1 == TIE) {
			_points[id1] += TIE_POINTS;
			_points[id2] += TIE_POINTS;
		} else if (result1 == 1) {
			_points[id1] += WIN_POINTS;
		} else {
			_points[id2] += WIN_POINTS;
		}
	}
}

bool Neighbourhood::possibleDecrement(int i) {
	return _original[i] - delta(i) >= inferior_limit(i);
}

bool Neighbourhood::possibleIncrement(int i) {
	return _original[i] + delta(i) <= superior_limit(i);
}

bool Neighbourhood::increment(string& actual) { // incrementa el string id con logica ternaria
	if (actual == "222222") {
		return false;
	}

	bool finished = false;
	for (int i = actual.size() - 1; i >= 0 and not finished; --i) {
		if(actual[i] == '0') {
			actual[i] = '1';
			finished = true;
		} else if (actual[i] == '1') {
			actual[i] = '2';
			finished = true;
		} else {
			actual[i] = '0';
		}
	}

	return true;
}

bool Neighbourhood::valid(string& id) {
	bool valid = true;
	for (int i = 0; i < id.size(); ++i)	{
		if (id[i] == '0' and not possibleDecrement(i)) return false;
		if (id[i] == '2' and not possibleIncrement(i)) return false;
	}

	return true;
}