#ifndef OUR_REFEREE_H
#define OUR_REFEREE_H

#include "defines.h"

void update(int nextMove, int colour);
int no_place_left();
bool updateColourAndChain(int& chain_size, int& actual_color, int i, int j);
bool someoneWonInRows();
bool someoneWonInColumns();
bool someoneWonInDiagonalsCresc();
bool someoneWonInDiagonalsDecresc();
bool someoneWonInDiagonals();
bool someone_won();
int referee(int n1, int m1, int c1, int p1, vector<int> params1, vector<int> params2);

int random_play();
int referee_vs_random(int n1, int m1, int c1, int p1, vector<int> params);
#endif //OUR_REFEREE_H