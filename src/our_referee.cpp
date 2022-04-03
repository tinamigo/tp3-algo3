#include "our_referee.h"

using namespace std;

int n, m, c, p;
matrix board;
vector<int> lasts;
int chips_played;

void update(int nextMove, int colour) {
	board[lasts[nextMove]][nextMove] = colour;
	lasts[nextMove] --;
	chips_played ++;
}

int no_place_left() {
	return chips_played == n * m;
}

bool updateColourAndChain(int& chain_size, int& actual_color, int i, int j) {
	if (board[i][j] == actual_color and actual_color != EMPTY) {
		chain_size++;
	} else if (board[i][j] != actual_color and board[i][j] != EMPTY) {
		if (chain_size >= c) return true;
		actual_color = board[i][j];
		chain_size = 1;
	} else if (board[i][j] == EMPTY) {
		if (chain_size >= c) return true;
		actual_color = EMPTY;
		chain_size = 0;
	}
	return false;
}

bool someoneWonInRows() {
	int chain_size = 0;
	int actual_color = EMPTY;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (updateColourAndChain(chain_size, actual_color, i, j)) return true;
		}
		if (chain_size >= c) return true;
		chain_size = 0;
	}
	return false;
}

bool someoneWonInColumns() {
	int chain_size = 0;
	int actual_color = EMPTY;

	for (int j = 0; j < n; ++j) {
		for (int i = 0; i < m; ++i) {	
			if (updateColourAndChain(chain_size, actual_color, i, j)) return true;
		}
		if (chain_size >= c) return true;
		chain_size = 0;
	}
	return false;
}

bool someoneWonInDiagonalsCresc() {
	int chain_size = 0;
	int actual_color = EMPTY;

	for (int i = c - 1; i < m; ++i) {
		for (int k = 0; k < min(i+1,n); ++k) {
			if (updateColourAndChain(chain_size, actual_color, i - k, k)) return true;
		}
		if (chain_size >= c) return true;
		chain_size = 0;
	}
	
	for (int j = 1; j < n-c+1; ++j) {
		for (int k = 0; k < min(n-j,m); k++) {
			if (updateColourAndChain(chain_size, actual_color, m - 1 - k, j + k)) return true;
		}
		if (chain_size >= c) return true;
		chain_size = 0;	
	}
	
	return false;
}

bool someoneWonInDiagonalsDecresc() {
	int chain_size = 0;
	int actual_color = EMPTY;
	
	for (int i = c - 1; i < m; ++i) {
		for (int k = 0; k < min(i+1,n); ++k) {
			if (updateColourAndChain(chain_size, actual_color, i - k, n - 1 - k)) return true;			
		}
		if (chain_size >= c) return true;
		chain_size = 0;
	}
	
	for (int j = n-2; j > c-2; --j) {
		for (int k = 0; k < min(j+1,m); k++) {
			if (updateColourAndChain(chain_size, actual_color, m - 1 - k, j - k)) return true;
		}
		if (chain_size >= c) return true;
		chain_size = 0;	
	}

	return false;
}

bool someoneWonInDiagonals() {
	return someoneWonInDiagonalsCresc() or someoneWonInDiagonalsDecresc();
}

bool someone_won() {
	return someoneWonInRows() or someoneWonInColumns() or someoneWonInDiagonals();
}

int referee(int n1, int m1, int c1, int p1, vector<int> params1, vector<int> params2) {
	n = n1;
	m = m1;
	c = c1;
	p = 2 * p1;
	chips_played = 0;

	vector<vector<int>> mat(m,vector<int>(n, EMPTY));
	board = mat;
	vector<float> costs1;
	vector<float> costs2;
	vector<int> l(n, m-1);
	lasts = l;

	for (int i = 0; i < c - 1; ++i)	{
		costs1.push_back(params1[0] * pow(i,params1[1])); // 
	}
	costs1.push_back(1000000); // cadenas de c - 1 	
	costs1.push_back(params1[2]); // ataque	
	costs1.push_back(params1[3]); // defensa	
	costs1.push_back(params1[4]); // ataque futuro	
	costs1.push_back(params1[5]); // defensa futura

	for (int i = 0; i < c - 1; ++i)	{
		costs2.push_back(params2[0] * pow(i,params2[1])); // 
	}
	costs2.push_back(1000000); // cadenas de c - 1 	
	costs2.push_back(params2[2]); // ataque	
	costs2.push_back(params2[3]); // defensa	
	costs2.push_back(params2[4]); // ataque futuro	
	costs2.push_back(params2[5]); // defensa futura

	// empieza red siempre, en el medio
	update((int) n/2, RED);
	update(nextPlay(BLUE, costs2, n, m, c, board, lasts), BLUE);
//	printBoardChips(board, n, m);

	while (chips_played < p) {
		update(nextPlay(RED, costs1, n, m, c, board, lasts), RED);
	//	printBoardChips(board, n, m);
		if (someone_won()) return RED;
		if (no_place_left()) return TIE;
		update(nextPlay(BLUE, costs2, n, m, c, board, lasts), BLUE);
	//	printBoardChips(board, n, m);
		if (someone_won()) return BLUE;
		if (no_place_left()) return TIE;
	}

	return TIE;
}
/*
int main () {
	int n1; int m1; int c1; int p1;
	vector<int> params1(6,0);
	vector<int> params2(6,0);
	cin >> n1 >> m1 >> c1 >> p1;
	for (int i = 0; i < 6; ++i) {
		cin >> params1[i];
	}
	for (int i = 0; i < 6; ++i) {
		cin >> params2[i];
	}

	int winner = referee(n1, m1, c1, p1, params1, params2);

	if (winner == TIE) {
		cout << "Empataron" << endl;
	} else if (winner == RED) {
		cout << "Gano el jugador 1" << endl;
	} else {
		cout << "Gano el jugador 2" << endl;
	}

	return 0;
}
*/


int referee_vs_random(int n1, int m1, int c1, int p1, vector<int> params) {
	n = n1;
	m = m1;
	c = c1;
	p = 2 * p1;
	chips_played = 0;

	vector<vector<int>> mat(m,vector<int>(n, EMPTY));
	board = mat;
	vector<float> costs1;
	//vector<float> costs2;
	vector<int> l(n, m-1);
	lasts = l;

	for (int i = 0; i < c - 1; ++i)	{
		costs1.push_back(params[0] * pow(i,params[1])); // 
	}
	costs1.push_back(1000000); // cadenas de c - 1 	
	costs1.push_back(params[2]); // ataque	
	costs1.push_back(params[3]); // defensa	
	costs1.push_back(params[4]); // ataque futuro	
	costs1.push_back(params[5]); // defensa futura
/*
	for (int i = 0; i < c - 1; ++i)	{
		costs2.push_back(params2[0] * pow(i,params2[1])); // 
	}
	costs2.push_back(1000000); // cadenas de c - 1 	
	costs2.push_back(params2[2]); // ataque	
	costs2.push_back(params2[3]); // defensa	
	costs2.push_back(params2[4]); // ataque futuro	
	costs2.push_back(params2[5]); // defensa futura
*/
	// empieza red siempre, en el medio
	srand(time(NULL));
	update(random_play(), BLUE);
	update(nextPlay(RED, costs1, n, m, c, board, lasts), RED);
//	printBoardChips(board, n, m);

	while (chips_played < p) {
		update(random_play(), BLUE);
	//	printBoardChips(board, n, m);
		if (someone_won()) return BLUE;
		if (no_place_left()) return TIE;
		update(nextPlay(RED, costs1, n, m, c, board, lasts), RED);
	//	printBoardChips(board, n, m);
		if (someone_won()) return RED;
		if (no_place_left()) return TIE;
	}

	return TIE;
}

int random_play(){
	int random = rand() % n;
	while(lasts[random] <= 0){
		random = rand() % n;
	}
	return random;
}