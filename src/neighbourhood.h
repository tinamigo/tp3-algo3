#ifndef NEIGHBOURHOOD_H
#define NEIGHBOURHOOD_H

#include <map>
#include "our_referee.h"

using namespace std;

#define ID_ORIGINAL "111111"

class Neighbourhood {
public:
	Neighbourhood(vector<int>& original, int n, int m, int c);
	vector<int> get_best();

private:
	bool get_next(string& actual);
	string initial();
	vector<int> player(string id);
	void addPointsMatch(string& id1, string& id2);
	bool possibleDecrement(int i);
	bool possibleIncrement(int i);
	bool increment(string& actual);
	bool valid(string& id);

	int _n,_m,_c;
	vector<int> _original;
	map<string,int> _points;
	map<string,bool> _presence;
};

#endif //DEFINES_H
