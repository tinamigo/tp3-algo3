#include "generation.h"

using namespace std;

Generation::Generation(vector<vector<int>> v, int n, int m, int c, int fitness, int crossover, int mutation, int selection): _population(v),
			_n(n), _m(m), _c(c), _fitness(fitness), _crossover(crossover), _mutation(mutation), _selection(selection), _points(v.size(), 0) {
	_size = v.size();
}

int Generation::size() {
	return _size;
}

vector<vector<int>> Generation::get_new_generation() {
	vector<vector<int>> new_gen;
	fitness(); // actualizo puntos
	selection(new_gen);
	return new_gen;
}

void Generation::set_new_generation(vector<vector<int>> n) {
	_population = n;
	vector<int> reseter(size(),0);
	_points = reseter;
}

void Generation::selection(vector<vector<int>>& new_gen) {
	sort_by_points(); 
	if (_selection == 0) {
		feudal_monogamic_selection(new_gen);
	} else if (_selection == 1) {
		feudal_roman_selection(new_gen);
	} else {
		elite_selection(new_gen);
	}
}

void Generation::feudal_monogamic_selection(vector<vector<int>>& new_gen) { // cada uno de los mejores 7 tiene equal possibility
	new_gen.push_back(citizen(0));	// elijo primero dejar los dos mejores
	new_gen.push_back(citizen(1));

	vector<int> bestest;
	for (int i = 0; i < (size()-2)/2; ++i) {
		bestest.push_back(i);
	}

	random_shuffle(bestest.begin(), bestest.end());	// los mezclo randomly

	for (int i = 0; i < (size()-2)/2; ++i) {
		generate_offspring(i, bestest[i], new_gen);
	}
}

void Generation::feudal_roman_selection(vector<vector<int>>& new_gen) { // los romanos eran poliamorosos como este selection
	new_gen.push_back(citizen(0));	// elijo primero dejar los dos mejores
	new_gen.push_back(citizen(1));

	// para cada uno de los mejores elijo randomly su pareja que puedo ser yo mismo
	for (int i = 0; i < (size()-2)/2; ++i) {
		int partner = rand() % ((size()-2)/2);
		generate_offspring(i, partner, new_gen);
	}
}

void Generation::elite_selection(vector<vector<int>>& new_gen) {	// DISCLAIMER: funciona para size = 16
	new_gen.push_back(citizen(0));
	new_gen.push_back(citizen(1));
	new_gen.push_back(citizen(2));
	new_gen.push_back(citizen(3));

	for (int i = 0; i < 4; ++i) {
		for (int j = i+1; j < 4; ++j) {
			generate_offspring(i, j, new_gen);
		}
	}
}

void Generation::generate_offspring(int i, int j, vector<vector<int>>& new_gen) {
	// Genero dos hijos distintos y los agrego a new_gen
	vector<int> first_born = crossover(i,j);
	mutate_child(first_born);
	new_gen.push_back(first_born);
	vector<int> spoiled_child = crossover(j,i);
	mutate_child(spoiled_child);
	new_gen.push_back(spoiled_child);
}

void Generation::mutate_child(vector<int>& child) {
	for (int i = 0; i < child.size(); ++i) {
		if (rand() % 100 <= mutation()) {
			child[i] = random_value_for_parameter(i);
		}
	}
}

vector<int> Generation::crossover(int i, int j) {
	vector<int> res;
	if (_crossover == 0) {
		equal_crossover(i, j, res);
	} else if (_crossover == 1) {
		mean_crossover(i, j, res);
	} else if (_crossover == 2) {
		favourite_parent_crossover(i, j, res);
	}
	return res;
}

void Generation::equal_crossover(int i, int j, vector<int>& child) {
	for (int k = 0; k < AMOUNT_PARAMETERS; ++k) {
		int which_parent = i;
		if (rand() % 2 == 1) which_parent = j; // con un 50% de probabilidad elijo uno u otro parent
		// introduzco mutation
		child.push_back(_population[which_parent][k]);
	}
}

void Generation::mean_crossover(int i, int j, vector<int>& child) { // calculo un promedio con un peso random
	int random = 25 + rand() % 50; // entre 25 y 75
	for (int k = 0; k < AMOUNT_PARAMETERS; ++k) {
		child.push_back((_population[i][k] * random + _population[j][k] * (100 - random)) / 100); // la div es entera
	}
}

void Generation::favourite_parent_crossover(int i, int j, vector<int>& child) {
	int random = rand() % 100; // posibilidad de que cambie mi gen al de j
	for (int k = 0; k < AMOUNT_PARAMETERS; ++k) {
		int which_parent = i;
		if (rand() % 100 <= random) which_parent = j;
		child.push_back(_population[which_parent][k]);
	}
}




int Generation::mutation() { // devuelve el porcentaje de probabilidad de que mute
	if (_mutation == 0) {
		return 5; 
	} else if (_mutation == 1) {
		return 10;
	}
}

vector<int> Generation::citizen(int i) {
	assert(i < size());
	return _population[i];
}

int Generation::points(int i) {
	assert(i < size());
	return _points[i];
}

void Generation::fitness() {
	if (_fitness == 0) {
		free_for_all();
	} else if (_fitness == 1) {
		tournament();
	}
}

// metodos fitness
void Generation::free_for_all(int start, int finish, vector<int> v) {
	if (v.size() == 0) {
		for (int i = start; i < finish - 1; ++i) {
			for (int j = i+1; j < finish; ++j) {
				match(i,j);
				match(j,i);
			}
		}
	} else {
		for (int i = start; i < finish - 1; ++i) {
			for (int j = i+1; j < finish; ++j) {
				match(v[i],v[j]);
				match(v[j],v[i]);	
			}
		}
	}
}

void Generation::match(int i, int j) {
	int result = referee(_n, _m, _c, _n * _m, citizen(i), citizen(j));
	if (result == TIE) {
		_points[i] += TIE_POINTS;
		_points[j] += TIE_POINTS;
	} else if (result == 1) {
		_points[i] += WIN_POINTS;
	} else {
		_points[j] += WIN_POINTS;
	}
}

void Generation::tournament() {
	random_shuffle(_population.begin(), _population.end()); // no quiero que me determine el orden de creacion el torneo
	// divido en grupos de a cuatro que van a competir entre si
	vector<int> winners;
	for (int i = 0; i < size()/GROUP_SIZE; ++i) {
		int start = i * GROUP_SIZE;
		free_for_all(start, start + GROUP_SIZE);
		int max = start;
		for (int j = start; j < start + GROUP_SIZE; ++j) {
			if (_points[j] > _points[max]) max = j;
		}
		winners.push_back(max);
	}
	free_for_all(0,winners.size(),winners);
}

void Generation::sort_by_points() {  // como son dieciseis elementos me puedo permitir hacerlo en O(n^2)
	for (int i = 0; i < size(); ++i) {
		int max = i;
		for (int j = i+1; j < size(); ++j) {
			if (_points[j] > _points[max]) max = j;
		}
		swap(_population[i], _population[max]);
		swap(_points[i], _points[max]);
	}
}

int random_value_for_parameter(int parameter) {
	return inferior_limit(parameter) + (rand() % (superior_limit(parameter) - inferior_limit(parameter) + 1));
}
