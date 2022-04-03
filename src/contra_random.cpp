#include "our_referee.h"

int main() {
	
	int victorias = 0;
	int empates = 0;
	int derrotas = 0;
	int n1 = 7;
	int m1 = 6;
	int c1 = 4;
	int p1 = 10000000;
	vector<int> params = {11, 3, 11, 3, 3, 7};

	for (int i = 0; i < 100000; ++i) {
		int resultado = referee_vs_random(n1, m1, c1, p1, params);
		if (resultado == TIE) {
			empates++;
		} else if (resultado == RED) {
			victorias++;
		} else if (resultado == BLUE) { //blue es random
			derrotas++;
		}
		cout << i << endl;
	}

	cout << "Victorias: " << victorias << endl;
	cout << "Empates: " << empates << endl;
	cout << "Derrotas: " << derrotas << endl;
	return 0;
}
