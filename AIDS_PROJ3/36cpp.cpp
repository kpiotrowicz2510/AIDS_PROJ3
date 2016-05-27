// AIDS_PROJ3.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

using namespace std;

struct Sciezka {
	int value;
	int number;
	Sciezka* parent;
	Sciezka* childLeft;
	Sciezka* childRight;
	int down_value_l;
	int p_number;
	int down_value_r;
	int *moves;
	bool taken;
	bool counted;
	int max_moves;
};
Sciezka*** sasiady; Sciezka* drzewo; long int * tablica_num;
int check(int start, int n) {
	int ret = 0;
	int jump = 0;
	drzewo[start].moves[0] = drzewo[start].value;
	//for (int h = start; h > 0; h=drzewo[h].parent->number-1) {
	Sciezka *a = &drzewo[start];
	/*if (a->childLeft != nullptr) {
	if (a->childRight != nullptr) {
	if (a->down_value_l < a->down_value_r) {
	a = a->childRight;
	}else{
	a = a->childLeft;
	}
	}else{
	a = a->childLeft;
	}
	}*/
	while (a != nullptr) {
		if (a->childLeft == nullptr) {
			if (a->counted == false) {
				drzewo[start].moves[jump] = a->value;
				drzewo[start].counted = true;
			}
			a = nullptr;
			continue;
		}
		if (a->childRight == nullptr) {
			jump++;
			drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_l;
			a = a->childLeft;
			//h = 0;
			//jump++;
			continue;
		}
		if (a->childRight != nullptr && a->childLeft != nullptr) {
			//drzewo[start].moves[0] = a->value;
			jump++;
			if (a->down_value_l < a->down_value_r&&a->childRight->counted==false) {
				drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_r;
				a->childRight->counted = true;
				a = a->childRight;
				//jump++;
			}
			if (a->down_value_l >= a->down_value_r&&a->childLeft->counted == false) {
				drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_l;
				a = a->childLeft;
				//jump++;
			}
		}
		//jump++;
	}
	drzewo[start].max_moves = jump;
	return ret;
}

Sciezka *first;


int main()
{
	int n, m;
	cin >> n >> m;
	drzewo = new Sciezka[n];
	tablica_num = new long int[n];
	sasiady = new Sciezka**[n+2];
	for (int i = 0; i < n+2; i++) {
		sasiady[i] = new Sciezka*[n+2];
		for (int j = 0; j < n + 2; j++) {
			sasiady[i][j] = nullptr;
		}
	}
	for (int i = 0; i < n; i++) {
		int n1, n2, val;
		cin >> n1 >> n2 >> val;
		drzewo[i].counted = false;
		drzewo[i].parent = nullptr;
		drzewo[i].number = n2;
		drzewo[i].p_number = n1;
		tablica_num[n2] = i;
		drzewo[i].value = val;
		drzewo[i].childLeft = nullptr;
		drzewo[i].childRight = nullptr;
		drzewo[i].down_value_l = 0;
		drzewo[i].down_value_r = 0;
		drzewo[i].taken = false;
		drzewo[i].moves = new int[m + 1];
		for (int ia = 0; ia < m + 1; ia++) {
			drzewo[i].moves[ia] = 0;
		}
		if (n1 == 1) {
			first = drzewo;
		}
		sasiady[n2][n1] = drzewo;
	}
	for (int i = 0; i < n+2; i++) {
		for (int j = 0; j < n+2; j++) {
			if (sasiady[i][j] == nullptr) {
				cout << "_ ";
			}else{
				drzewo[tablica_num[i]].parent = &drzewo[tablica_num[j]];
				cout << "1" << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		Sciezka a = drzewo[i];
		for (int j = i; j < n; j++) {
			if (drzewo[j].parent == &drzewo[i]) {
				if (drzewo[i].childLeft == nullptr) {
					drzewo[i].childLeft = &drzewo[j];
					drzewo[i].down_value_l = drzewo[j].value;
				}
				else {
					drzewo[i].childRight = &drzewo[j];
					drzewo[i].down_value_r = drzewo[j].value;
				}
			}
		}
	}





	for (int i = 0; i < n; i++) {
		if (i > 0) {
			check(i, n);
		}
		cout << &drzewo[i] << endl;
		cout << drzewo[i].number << endl;
		cout << drzewo[i].value << endl;
		cout << drzewo[i].parent << endl;

		cout << drzewo[i].childLeft << endl;
		cout << drzewo[i].childRight << endl;
		for (int h = 0; h < m; h++) {
		cout << "moves:" << endl << h << ":" << drzewo[i].moves[h] << endl;
		}
		cout << drzewo[i].down_value_l << endl;
		cout << drzewo[i].down_value_r << endl	<< endl;
	}


	int cn = 0;
	int max_val = first->value;
	drzewo[0].taken = true;
	int moves = m;
	Sciezka *cnx = first;

	while (moves-- > 0) {
		if (cnx == nullptr) {
			//continue;
		}

		//max_val += (*cnx).value;
		//(*cnx).taken = true;

		if ((*cnx).childLeft == nullptr && (*cnx).childRight == nullptr) {
			max_val += (*cnx).value;
			(*cnx).taken = true;
			cout << max_val << " " << cnx->value;
			if (moves == 0) {
				break;
			}
			int mx = 0;
			int id = 0;
			int h = n - 1;
			if ((*cnx).parent != nullptr) {
				//h = tablica_num[(*(*cnx).parent).number-1];
			}
			for (int i = 0; i < n; i++) {
				if ((drzewo[i]).p_number == 1) {
					cnx = &drzewo[i];
				}
			}
			//(drzewo[id]).taken = true;
			//cnx = &drzewo[id];
			//max_val += (*cnx).value;
			continue;
		}

		if ((*cnx).childLeft == nullptr) {
			if (cnx->taken == false) {
				max_val += (*cnx).value;
				(*cnx).taken = true;
				cout << max_val << " " << cnx->value;
			}
			for (int i = 0; i < n; i++) {
				if ((drzewo[i]).number == 1) {
					cnx = &drzewo[i];
				}
			}
			//cnx = cnx->parent;
			//cnx = nullptr;
			continue;
		}
		int* a = (*(*cnx).childLeft).moves;
		int  s;
		if (cnx->childLeft->max_moves <= moves) {
			s = cnx->childLeft->max_moves;
		}
		else {
			s = moves;
		}
		int left = a[s];
		int right = -1;
		int* b;
		if ((*cnx).childRight != nullptr) {
			b = (*(*cnx).childRight).moves;
			int g = 0;
			if (cnx->childRight->max_moves <= moves) {
				g = cnx->childRight->max_moves;
			}
			else {
				g = moves;
			}

			right = b[g];
		}

		if (left >= right) {
			if (cnx->taken == false) {
				max_val += (*cnx).value;
				cout << max_val << " " << cnx->value;
				(*cnx).taken = true;
			}
			//moves++;
			cnx = (*cnx).childLeft;
		}
		if (left < right) {
			if (cnx->taken == false) {
				max_val += (*cnx).value;
				cout << max_val << " " << cnx->value;
				(*cnx).taken = true;
			}
			//moves++;
			cnx = (*cnx).childRight;
		}
		//max_val += (*cnx).value;
		//(*cnx).taken = true;

	}
	cout << max_val << endl;
	return 0;
}
