#ifndef DEFINES_H
#define DEFINES_H

#include <tuple>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <stdio.h>
#include <sys/stat.h>
#include <limits>
#include <cmath>
#include <assert.h>
#include <cstdlib>
#include <algorithm>
#include <utility>

#define NORTH_WEST 0
#define NORTH 1
#define NORTH_EAST 2
#define WEST 3
#define EAST 4
#define SOUTH_WEST 5
#define SOUTH 6
#define SOUTH_EAST 7

#define BEST true
#define POSSIBLE false 

#define EMPTY 0
#define RED 1
#define BLUE 2

#define TIE 0

#define TRUE 1
#define FALSE 0

#define HORIZONTAL 0
#define VERTICAL 1
#define DIAG_CRESCENT 2
#define DIAG_DECRESCENT 3

#define INFINITY_FLOAT std::numeric_limits<float>::infinity()
#define MAX_FLOAT std::numeric_limits<float>::max()
#define MIN_FLOAT -MAX_FLOAT

//genetic_search
#define AMOUNT_GENETIC 10000
#define GROUP_SIZE 4
#define POPULATION_SIZE 16 // MAYOR A 7!!!

//grid_search
#define AMOUNT_GRID_SEARCH 50
#define DELTA_0 10
#define DELTA_1 1
#define DELTA_2 1
#define DELTA_3 1
#define DELTA_4 1
#define DELTA_5 1
#define INF_LIMIT_0 1
#define INF_LIMIT_1 1
#define INF_LIMIT_2 0
#define INF_LIMIT_3 0
#define INF_LIMIT_4 0
#define INF_LIMIT_5 0
#define SUP_LIMIT_0 101
#define SUP_LIMIT_1 4
#define SUP_LIMIT_2	20
#define SUP_LIMIT_3 20
#define SUP_LIMIT_4 10
#define SUP_LIMIT_5 10

#define TIE_POINTS 1
#define WIN_POINTS 3

#define AMOUNT_PARAMETERS 6

using namespace std;

class cell;

typedef vector < vector <int> > matrix;
typedef vector < vector <cell> > cellsMatrix;

class cell {
public:
	cell():_N(0,0,0,0), _S(0,0,0,0), _W(0,0,0,0), _E(0,0,0,0), _NE(0,0,0,0), _NW(0,0,0,0), _SE(0,0,0,0), _SW(0,0,0,0){};

	tuple <int,int,int,int> n();
	tuple <int,int,int,int> s();
	tuple <int,int,int,int> w();
	tuple <int,int,int,int> e();
	tuple <int,int,int,int> ne();
	tuple <int,int,int,int> nw();
	tuple <int,int,int,int> se();
	tuple <int,int,int,int> sw();
	tuple <int,int,int,int> dir(int dir);

	void setCell(int dir, int red, int red_blanks, int blue, int blue_blanks);
private:
	tuple <int,int,int,int> _N;
	tuple <int,int,int,int> _S;
	tuple <int,int,int,int> _W;
	tuple <int,int,int,int> _E;
	tuple <int,int,int,int> _NE;
	tuple <int,int,int,int> _NW;
	tuple <int,int,int,int> _SE;
	tuple <int,int,int,int> _SW;
};

int reds(tuple<int,int,int,int> t);
int blues(tuple<int,int,int,int> t);
int red_blanks(tuple<int,int,int,int> t);
int blue_blanks(tuple<int,int,int,int> t);

void setCellInDirection (int i, int j, int dir, matrix& board, cellsMatrix& cellBoard, bool best_or_possible);
void setCellInDirectionBest (int i, int j, int dir, matrix& board, cellsMatrix& cellBoard);
void setCellInDirectionPossible (int i, int j, int dir, matrix& board, cellsMatrix& cellBoard);
bool isPossible(cell cell, int dir, int colour, int c);

int bestPlay(vector<float> &points);
int saturate(int i, int c);
void saturatedSum(float& points, float additive);
void saturatedSub(float& points, float substract);

// prints
void printBoardChips(matrix& board, int n, int m);
void printBoard(int n, int m, cellsMatrix& board, int colour);
void printVector(vector<int> v);

void send(const std::string& msg);
void send(int msg);
int read_int();
std::string read_str();

void calculateBoard(cellsMatrix& cellBoard, bool best_or_possible, int n, int m, matrix& board);
void calculateBestBoard(cellsMatrix& cellBoard, int n, int m, matrix& board);
void calculatePossibleBoard(cellsMatrix& cellBoard, int n, int m, matrix& board);
float calculateCellValue(cell cell, int dir, int colour, vector<float>& costs, int c);
int nextPlay(int my_colour, vector<float>& costs, int n, int m, int c, matrix& board, vector<int>& lasts);

// limites y saltos de parametros
int inferior_limit(int i);
int superior_limit(int i);
int delta(int i);

#endif //DEFINES_H
