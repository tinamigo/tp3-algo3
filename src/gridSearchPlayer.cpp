#include "defines.h"

int c, m, n, p;

matrix board;
vector<float> costs;
vector<int> lasts; 

using namespace std;

void update(int nextMove, int colour) {
	board[lasts[nextMove]][nextMove] = colour;
	lasts[nextMove] --;
}

int main() {
	bool endgame = false;
	while(true) {
		string starter;
		string col = read_str();
		string our = read_str();
		n = read_int();
		m = read_int();
		c = read_int();
		p = read_int();
		starter = read_str();

		// 11, 3, 11, 3, 3, 7

		int param_0 = 11;	// k = constante de la funcion de crecimiento
		int param_1 = 3;	// e = exponente de la funcion de crecimiento
		int param_2 = 11;	// ataque
		int param_3 = 3;	// defensa
		int param_4 = 3;	// ataque futuro
		int param_5 = 7;	// defensa futura

		for (int i = 0; i < c - 1; ++i)	{
			costs.push_back(param_0 * pow(i,param_1)); // 
		}
		costs.push_back(1000000); // cadenas de c - 1 
		costs.push_back(param_2); // ataque
		costs.push_back(param_3); // defensa
		costs.push_back(param_4); // ataque futuro
		costs.push_back(param_5); // defensa futura
		
		vector<vector<int>> mat(m,vector<int>(n, EMPTY));
		board = mat;
		vector<int> l (n, m-1);
		lasts = l;

		if (starter == "vos") {
			send((int)n/2);
			update((int)n/2, RED);
		}

		bool finished = false;
		while(!finished) {
			string mssg = read_str();
			if (mssg == "ganaste" || mssg == "perdiste" || mssg == "empataron") {
				finished = true;
			} else {
				int enemyMove = stoi(mssg);
				update(enemyMove, BLUE);
				int nextMove = nextPlay(RED, costs, n, m, c, board, lasts);
				send(nextMove);
				update(nextMove, RED);		
			}
		}
	}
	// cout << "listo" << endl;

	return 0;
}