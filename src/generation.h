#ifndef GENERATION_H
#define GENERATION_H

#include "our_referee.h"

using namespace std;

class Generation {
public:
	Generation(vector<vector<int>> v, int n, int m, int c, int fitness, int crossover, int mutation, int selection);
	int size();
	vector<vector<int>> get_new_generation();
	void set_new_generation(vector<vector<int>> n);
	vector<int> citizen(int z);
	int points(int i);

	void sort_by_points(); 
	void free_for_all(int start = 0, int finish = POPULATION_SIZE, vector<int> v = vector<int>());
private:
	void fitness();
	void selection(vector<vector<int>>& new_gen);
	vector<int> crossover(int i, int j);
	int mutation();

	// auuxiliares
	void match(int i, int j);
	void generate_offspring(int i, int j, vector<vector<int>>& new_gen);
	void mutate_child(vector<int>& child);

	// metodos fitness
	void tournament();

	// metodos selection
	void feudal_monogamic_selection(vector<vector<int>>& new_gen);
	void feudal_roman_selection(vector<vector<int>>& new_gen);
	void elite_selection(vector<vector<int>>& new_gen);

	// metodos crossover
	void equal_crossover(int i, int j, vector<int>& child);
	void mean_crossover(int i, int j, vector<int>& res);
	void favourite_parent_crossover(int i, int j, vector<int>& res);

	vector<vector<int>> _population;
	vector<int> _points;
	int _size;
	int _n;
	int _m;
	int _c;
	int _fitness;
	int _crossover;
	int _mutation;
	int _selection;
};

int random_value_for_parameter(int parameter);

#endif //GENERATION_H