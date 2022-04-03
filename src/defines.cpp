#include "defines.h"

tuple <int,int,int,int> cell::n() { return _N; }
tuple <int,int,int,int> cell::s() { return _S; }
tuple <int,int,int,int> cell::w() { return _W; }
tuple <int,int,int,int> cell::e() { return _E; }
tuple <int,int,int,int> cell::ne() { return _NE; }
tuple <int,int,int,int> cell::nw() { return _NW; }
tuple <int,int,int,int> cell::se() { return _SE; }
tuple <int,int,int,int> cell::sw() { return _SW; }

tuple <int,int,int,int> cell::dir(int dir) {
	switch(dir) {
		case NORTH:
			return _N;
		break;
		case SOUTH:
			return _S;
		break;
		case EAST:
			return _E;
		break;
		case WEST:
			return _W;
		break;
		case NORTH_WEST:
			return _NW;
		break;
		case NORTH_EAST:
			return _NE;
		break;
		case SOUTH_WEST:
			return _SW;
		break;
		case SOUTH_EAST:
			return _SE;
		break;
	}
}

int nextPlay(int my_colour, vector<float>& costs, int n, int m, int c, matrix& board, vector<int>& lasts) {
	// defino quien es mi enemigo
	int enemy;
	if (my_colour == RED) {
		enemy = BLUE;
	} else {
		enemy = RED;
	}

	// inicializo estructuras y calculo cadenas posibles
	cellsMatrix possible(m, vector<cell>(n));
	cellsMatrix best(m, vector<cell>(n));
	calculatePossibleBoard(possible, n, m, board);
	calculateBestBoard(best, n, m, board);

	// recolecto info de best move sobre mi color
	vector<float> points(n,0);

	for (int i = 0; i < n; ++i) {
		if (lasts[i] != -1) {
			for (int dir = HORIZONTAL; dir <= DIAG_DECRESCENT; ++dir) {
				if (isPossible(possible[lasts[i]][i], dir, my_colour, c)) {
					//para mi color
					saturatedSum(points[i], calculateCellValue(best[lasts[i]][i], dir, my_colour, costs, c) * costs[c]);					
				}
				
				if (isPossible(possible[lasts[i]][i], dir, enemy, c)) {
					//para el enemigo
					saturatedSum(points[i], calculateCellValue(best[lasts[i]][i], dir, enemy, costs, c) * costs[c+1]);
				}
				
				if (lasts[i] != 0) {
					//beneficio para el casillero arriba mio para mi (resta porque es malo porque quiero q el enemigo me ponga primero)
					if (isPossible(possible[lasts[i]-1][i], dir, my_colour, c)) {
						saturatedSub(points[i], calculateCellValue(best[lasts[i]-1][i], dir, my_colour, costs, c) * costs[c+2]);
					}
					//beneficio para el casillero arriba mio para el enemigo(resta porque es "malo" y asi los parametros son +)
					if (isPossible(possible[lasts[i]-1][i], dir, enemy, c)) {
						saturatedSub(points[i], calculateCellValue(best[lasts[i]-1][i], dir, enemy, costs, c) * costs[c+3]);
					}
				}				
			}
		} else {
			points[i] = - INFINITY_FLOAT;

		}
	}

	return bestPlay(points);
}


float calculateCellValue(cell cell, int dir, int colour, vector<float>& costs, int c) {
	if (dir == HORIZONTAL) {
		if (colour == RED) {
			return costs[saturate(reds(cell.e())  + reds(cell.w()), c)];
		} else if (colour == BLUE) {
			return costs[saturate(blues(cell.e()) + blues(cell.w()), c)];
		}
	} else if (dir == VERTICAL) {
		if (colour == RED) {
			return costs[saturate(reds(cell.n()) + reds(cell.s()), c)];
		} else if (colour == BLUE) {
			return costs[saturate(blues(cell.n()) + blues(cell.s()), c)];
		}
	} else if (dir == DIAG_CRESCENT) {
		if (colour == RED) {
			return costs[saturate(reds(cell.ne()) + reds(cell.sw()), c)];
		} else if (colour == BLUE) {
			return costs[saturate(blues(cell.ne()) + blues(cell.sw()), c)];
		}
	} else if (dir == DIAG_DECRESCENT) {
		if (colour == RED) {
			return costs[saturate(reds(cell.nw()) + reds(cell.se()), c)];
		} else if (colour == BLUE) {
			return costs[saturate(blues(cell.nw()) + blues(cell.se()), c)];
		}
	}
}

void calculateBoard(cellsMatrix& cellBoard, bool best_or_possible, int n, int m, matrix& board) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != m-1) {
				setCellInDirection(i,j, NORTH, board, cellBoard, best_or_possible);
			}
			if (j != n-1) {
				setCellInDirection(i,j, WEST, board, cellBoard, best_or_possible);
			}
			if (i != m-1 and j != n-1) {
				setCellInDirection(i,j, NORTH_WEST, board, cellBoard, best_or_possible);
			}
			if (j != 0 and i != m-1){
				setCellInDirection(i,j, NORTH_EAST, board, cellBoard, best_or_possible);
			}
		}
	}
	// recorrer para la izquierda
	for (int i = m - 1; i >= 0; --i) {
		for (int j = n - 1; j >= 0; --j) {
			if (i != 0) {
				setCellInDirection(i,j, SOUTH, board, cellBoard, best_or_possible);
			}
			if (j != 0) {
				setCellInDirection(i,j, EAST, board, cellBoard, best_or_possible);				
			}
			if (i != 0 and j != n-1) {
				setCellInDirection(i,j, SOUTH_WEST, board, cellBoard, best_or_possible);
			}
			if (i != 0 and j != 0) {
				setCellInDirection(i,j, SOUTH_EAST, board, cellBoard, best_or_possible);				
			}
		}
	}
}

void calculatePossibleBoard(cellsMatrix& cellBoard, int n, int m, matrix& board) {
	calculateBoard(cellBoard, POSSIBLE, n, m, board);
}

void calculateBestBoard(cellsMatrix& cellBoard, int n, int m, matrix& board) {
	calculateBoard(cellBoard, BEST, n, m, board);
}

bool isPossible(cell cell, int dir, int colour, int c) {
	if (dir == HORIZONTAL) {
		if (colour == RED) {
			return reds(cell.e()) + red_blanks(cell.e()) + reds(cell.w()) + red_blanks(cell.w()) + 1 >= c;
		} else if (colour == BLUE) {
			return blues(cell.e()) + blue_blanks(cell.e()) + blues(cell.w()) + blue_blanks(cell.w()) + 1 >= c;
		}
	} else if (dir == VERTICAL) {
		if (colour == RED) {
			return reds(cell.n()) + red_blanks(cell.n()) + reds(cell.s()) + red_blanks(cell.s()) + 1 >= c;
		} else if (colour == BLUE) {
			return blues(cell.n()) + blue_blanks(cell.n()) + blues(cell.s()) + blue_blanks(cell.s()) + 1 >= c;
		}
	} else if (dir == DIAG_CRESCENT) {
		if (colour == RED) {
			return reds(cell.ne()) + red_blanks(cell.ne()) + reds(cell.sw()) + red_blanks(cell.sw()) + 1 >= c;
		} else if (colour == BLUE) {
			return blues(cell.ne()) + blue_blanks(cell.ne()) + blues(cell.sw()) + blue_blanks(cell.sw()) + 1 >= c;
		}
	} else if (dir == DIAG_DECRESCENT) {
		if (colour == RED) {
			return reds(cell.nw()) + red_blanks(cell.nw()) + reds(cell.se()) + red_blanks(cell.se()) + 1 >= c;
		} else if (colour == BLUE) {
			return blues(cell.nw()) + blue_blanks(cell.nw()) + blues(cell.se()) + blue_blanks(cell.se()) + 1 >= c;
		}
	}
	cout << "Que carajo le pasaron a is possible" << endl;
	return false;
}

void setPositions(int& def_i, int& def_j, int i, int j, int dir) {
	switch (dir) {
		case NORTH:
			def_i = i + 1;
			def_j = j;
		break;

		case SOUTH:
			def_i = i - 1;
			def_j = j;
		break;

		case EAST:
			def_i = i;
			def_j = j - 1;
		break;		

		case WEST:
			def_i = i;
			def_j = j + 1;
		break;		

		case NORTH_WEST:
			def_i = i + 1;
			def_j = j + 1;
		break;		

		case SOUTH_EAST:
			def_i = i - 1;
			def_j = j - 1;
		break;

		case NORTH_EAST:
			def_i = i + 1;
			def_j = j - 1;
		break;

		case SOUTH_WEST:
			def_i = i - 1;
			def_j = j + 1;
		break;
	}
}

void setCellInDirectionPossible (int i, int j, int dir, matrix& board, cellsMatrix& cellBoard) {
	cell cell = cellBoard[i][j];
	int def_i;
	int def_j;
	int def_reds = 0;
	int def_red_blanks = 0;
	int def_blues = 0;
	int def_blue_blanks = 0;

	setPositions(def_i, def_j, i, j, dir);

	if (board[i][j] == RED) {
		if (board[def_i][def_j] != BLUE) {
			def_reds = reds(cell.dir(dir)) + 1;
			def_red_blanks = red_blanks(cell.dir(dir));
		}
	} else if (board[i][j] == BLUE) {
		if (board[def_i][def_j] != RED) {
			def_blues = blues(cell.dir(dir)) + 1;
			def_blue_blanks = blue_blanks(cell.dir(dir));
		}
	} else if (board[i][j] == EMPTY) {
		if (board[def_i][def_j] == RED) {
			def_reds = reds(cell.dir(dir));
			def_red_blanks = red_blanks(cell.dir(dir)) + 1;
		} else if (board[def_i][def_j] == BLUE) {
			def_blues = blues(cell.dir(dir));
			def_blue_blanks = blue_blanks(cell.dir(dir)) + 1;
		} else {
			def_reds = reds(cell.dir(dir));
			def_red_blanks = red_blanks(cell.dir(dir)) + 1;
			def_blues = blues(cell.dir(dir));
			def_blue_blanks = blue_blanks(cell.dir(dir)) + 1;
		}
	}

	cellBoard[def_i][def_j].setCell(dir, def_reds, def_red_blanks, def_blues, def_blue_blanks);
}

void setCellInDirectionBest (int i, int j, int dir, matrix& board, cellsMatrix& cellBoard) {
	cell cell = cellBoard[i][j];
	int def_i;
	int def_j;
	int def_reds = 0;
	int def_red_blanks = 0;
	int def_blues = 0;
	int def_blue_blanks = 0;

	setPositions(def_i, def_j, i, j, dir);

	if (board[i][j] == RED) {
		if (board[def_i][def_j] == RED) {
			def_reds = reds(cell.dir(dir)) + 1;
			def_red_blanks = red_blanks(cell.dir(dir));
		} else if (board[def_i][def_j] == EMPTY) {
			def_reds = reds(cell.dir(dir)) + 1;
		}
	} else if (board[i][j] == BLUE) {
		if (board[def_i][def_j] == BLUE) {
			def_blues = blues(cell.dir(dir)) + 1;
			def_blue_blanks = blue_blanks(cell.dir(dir));
		} else if (board[def_i][def_j] == EMPTY) {
			def_blues = blues(cell.dir(dir)) + 1;
		}
	} else if (board[i][j] == EMPTY) {
		/*if (board[def_i][def_j] == RED) {
			def_red_blanks = red_blanks(cell.dir(dir)) + 1;
		} else if (board[def_i][def_j] == BLUE) {
			def_blue_blanks = blue_blanks(cell.dir(dir)) + 1;
		} else {
			def_red_blanks = red_blanks(cell.dir(dir)) + 1;
			def_blue_blanks = blue_blanks(cell.dir(dir)) + 1;
		}*/
	}

	cellBoard[def_i][def_j].setCell(dir, def_reds, def_red_blanks, def_blues, def_blue_blanks);
}


void setCellInDirection (int i, int j, int dir, matrix& board, cellsMatrix& cellBoard, bool best_or_possible) {
	if (best_or_possible == POSSIBLE) {
		setCellInDirectionPossible(i,j,dir,board,cellBoard);
	} else if (best_or_possible == BEST) {
		setCellInDirectionBest(i,j,dir,board,cellBoard);
	}
}

void cell::setCell(int dir, int red, int red_blanks, int blue, int blue_blanks) {
	switch (dir) {
		case NORTH_WEST: 
			_NW = {red, red_blanks, blue, blue_blanks};
		break;

		case NORTH: 
			_N = {red, red_blanks, blue, blue_blanks};
		break;
		
		case NORTH_EAST: 
			_NE = {red, red_blanks, blue, blue_blanks};
		break;
		
		case WEST: 
			_W = {red, red_blanks, blue, blue_blanks};
		break;
		
		case EAST: 
			_E = {red, red_blanks, blue, blue_blanks};
		break;
		
		case SOUTH_WEST: 
			_SW = {red, red_blanks, blue, blue_blanks};
		break;
		
		case SOUTH: 
			_S = {red, red_blanks, blue, blue_blanks};
		break;
		
		case SOUTH_EAST: 
			_SE = {red, red_blanks, blue, blue_blanks};
		break;

		default:
			cout << "################ seteamos cell en dir invalida ################" << endl;

	} 
}

int bestPlay(vector<float> &points) {
	float max = points[0];
	int pos = 0;
	for (int i = 1; i < points.size(); ++i) {
		if (points[i] > max) {
			max = points[i];
			pos = i;
		}
	}
	return pos;
}

int reds(tuple<int,int,int,int> t) { return get<0>(t); }
int red_blanks(tuple<int,int,int,int> t) { return get<1>(t); }
int blues(tuple<int,int,int,int> t) { return get<2>(t); }
int blue_blanks(tuple<int,int,int,int> t) { return get<3>(t); }

void printBoard(int n, int m, cellsMatrix& board, int colour) {
	cerr << endl;
	if (colour == RED) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				cerr << "(";
					cerr << reds(board[i][j].n()) << " " << reds(board[i][j].s()) << " " << reds(board[i][j].w()) << " " << reds(board[i][j].e());
				cerr << ") ";
			}
			cerr << endl;
		}
		cerr << endl;
	}
	if (colour == BLUE) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				cerr << "(";
					cerr << blues(board[i][j].n()) << " " << blues(board[i][j].s()) << " " << blues(board[i][j].w()) << " " << blues(board[i][j].e());
				cerr << ") ";
			}
			cerr << endl;
		}
		cerr << endl;
	}
}

int saturate(int i, int c) {
	if (i < c) {
		return i;
	}
	return c - 1;
}

void saturatedSum(float& points, float additive) {
	if (points >= 0 and MAX_FLOAT - points < additive) {
		points = MAX_FLOAT;
	} else {
		points += additive;
	}
}

void saturatedSub(float& points, float substract) {
	if (points <= 0 and (-1) * (MIN_FLOAT - points) < substract) {
		points = MIN_FLOAT;
		cerr << MIN_FLOAT << endl;
	} else {
		points -= substract;
	}
}

void printBoardChips(matrix& board, int n, int m) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << board[i][j] << " " ;
		}
		cout << endl;
	}
	cout << endl << endl;
}

void printVector(vector<int> v) {
	cout << "[";

	for (int i = 0; i < v.size() - 1; ++i) {
		cout << v[i] << ", ";
	}

	cout << v[v.size() - 1] << "]" << endl;
}

void send(const std::string& msg) {
    std::cout << msg << std::endl;
}

void send(int msg) {
    std::cout << msg << std::endl;
}

int read_int() {
    std::string msg;
    std::cin >> msg;
    if (msg == "salir") {
        send("listo");
        std::exit(0);
    }
    return std::stoi(msg);
}

std::string read_str() {
    std::string msg;
    std::cin >> msg;
    if (msg == "salir") {
        send("listo");
        std::exit(0);
    }
    return msg;
}

int delta(int i) {
	switch(i) {
		case 0:
			return DELTA_0;
		break;
		case 1:
			return DELTA_1;
		break;
		case 2:
			return DELTA_2;
		break;
		case 3:
			return DELTA_3;
		break;
		case 4:
			return DELTA_4;
		break;
		case 5:
			return DELTA_5;
		break;
	}
}

int inferior_limit(int i) {
	switch(i) {
		case 0:
			return INF_LIMIT_0;
		break;
		case 1:
			return INF_LIMIT_1;
		break;
		case 2:
			return INF_LIMIT_2;
		break;
		case 3:
			return INF_LIMIT_3;
		break;
		case 4:
			return INF_LIMIT_4;
		break;
		case 5:
			return INF_LIMIT_5;
		break;
	}
}

int superior_limit(int i) {
	switch(i) {
		case 0:
			return SUP_LIMIT_0;
		break;
		case 1:
			return SUP_LIMIT_1;
		break;
		case 2:
			return SUP_LIMIT_2;
		break;
		case 3:
			return SUP_LIMIT_3;
		break;
		case 4:
			return SUP_LIMIT_4;
		break;
		case 5:
			return SUP_LIMIT_5;
		break;
	}
}
