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
		if (a->childRight == nullptr && a->childLeft == nullptr) {
			jump++;
			if (a->counted == false) {
				int b = 0;
				if (drzewo[start].moves[jump-1] != a->value) {
					b = drzewo[start].moves[jump-1];
					drzewo[start].moves[jump] = b + a->value;
				}
				
				a->counted = true;
			}
			//drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->value;
			break;
		}
		if (a->childLeft == nullptr) {
			//jump++;
			if (a->counted == false) {
				int b = 0;
				if (drzewo[start].moves[jump] != a->value) {
					b = drzewo[start].moves[jump];
					drzewo[start].moves[jump + 1] = b + a->value;
				}
				else {
					drzewo[start].moves[jump] = a->value;
				}
				a->counted = true;
			}
			a = nullptr;
			break;
		}
		if (a->childRight == nullptr) {
			if (a->childLeft->counted == false){
			jump++;
			drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_l;
			a = a->childLeft;
			}
			//h = 0;
			//jump++;
			continue;
		}
		if (a->childRight != nullptr && a->childLeft != nullptr) {
			//drzewo[start].moves[0] = a->value;
			jump++;
			if (a->down_value_l < a->down_value_r){
				if (a->childRight->counted == false) {
					drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_r;
					a->counted = true;
					a = a->childLeft;
				}
				else {
					a = a->childLeft;
							}
				continue;
				//jump++;
			}
			if (a->down_value_l >= a->down_value_r){
				if (a->childLeft->counted == false) {
					drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_l;
					a->counted = true;
					a = a->childRight;
				}
				else {
					a = a->childRight;
					}
				continue;
				//jump++;
			}
		}
		
		//jump++;
	}
	drzewo[start].max_moves = jump;
	return ret;
}

Sciezka *first;
int* count(int i, int moves_left) {
	Sciezka *sciezka = first;
	int ilosc = 0;
	int val = 0;
	while (sciezka->childLeft != nullptr&&ilosc <= moves_left) {
		if (sciezka->childRight != nullptr) {
			if (sciezka->childLeft->moves[moves_left - ilosc] >= sciezka->childRight->moves[moves_left - ilosc]) {
				sciezka->childLeft->moves[moves_left] = 0;
				if (sciezka->childLeft->taken == false) {
					sciezka = sciezka->childLeft;
					val += sciezka->value;
					ilosc++;
					sciezka->taken = true;
					//sciezka = sciezka->childLeft;
					//continue;
				}
				else {
					sciezka = sciezka->childRight;
					val += sciezka->value;
					ilosc++;
					sciezka->taken = true;
				}

				continue;
			}
			if (sciezka->childLeft->moves[moves_left - ilosc] < sciezka->childRight->moves[moves_left - ilosc]) {
				sciezka->childRight->moves[moves_left] = 0;
				sciezka = sciezka->childRight;
				sciezka->moves[moves_left] = 0;
				if (sciezka->taken == false) {
					val += sciezka->value;
					ilosc++;
					sciezka->taken = true;
					//continue;
				}
				else {
					sciezka = sciezka->childLeft;
					val += sciezka->value;
					ilosc++;
					sciezka->taken = true;
				}
				continue;
			}
		}
	}

	if	(sciezka->childLeft == nullptr&&sciezka->childRight == nullptr&&sciezka->taken == false) {
		val += sciezka->value;
		ilosc++;
		sciezka->taken = true;
		//sciezka = first;
	}
	int a[2];
	a[0] = ilosc;
	a[1] = val;
	return a;
}

int main()
{
	int n, m;
	cin >> n >> m;
	drzewo = new Sciezka[n];
	tablica_num = new long int[n];
	sasiady = new Sciezka**[n + 2];
	for (int i = 0; i < n + 2; i++) {
		sasiady[i] = new Sciezka*[n + 2];
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
			first = &drzewo[i];
		}
		sasiady[n2][n1] = &drzewo[i];
	}
	for (int i = 0; i < n + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			if (sasiady[i][j] == nullptr) {
				//cout << "_ ";
			}
			else {
				drzewo[tablica_num[i]].parent = &drzewo[tablica_num[j]];
				//cout << "1" << " ";
			}
		}
		//cout << endl;
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
	/*	cout << &drzewo[i] << endl;
		cout << drzewo[i].number << endl;
		cout << drzewo[i].value << endl;
		cout << drzewo[i].parent << endl;

		cout << drzewo[i].childLeft << endl;
		cout << drzewo[i].childRight << endl;
		for (int h = 0; h < m; h++) {
			cout << "moves:" << endl << h << ":" << drzewo[i].moves[h] << endl;
		}
		cout << drzewo[i].down_value_l << endl;
		cout << drzewo[i].down_value_r << endl << endl;*/
	}


	int cn = 0;
	int max_val =first->value;
	first->taken = true;
	int moves = m;
	int moves_done = 0;
	Sciezka *cnx = &drzewo[0];
	while (moves_done < moves) {
		int* x = count(0, moves - moves_done-1);
		moves_done += x[0];
		max_val += x[1];
	}
	
	cout << max_val << endl;
	return 0;
}
