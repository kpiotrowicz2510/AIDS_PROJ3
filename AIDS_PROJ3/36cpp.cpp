// AIDS_PROJ3.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

using namespace std;

struct Sciezka;
struct moveX {
	int value;
	Sciezka* path;
};
struct Sciezka {
	int value;
	int number;
	Sciezka* parent;
	Sciezka* childLeft;
	Sciezka* childRight;
	int down_value_l;
	int p_number;
	int down_value_r;
	moveX *moves;
	int *counts;
	bool* taken;
	bool counted;
	int max_moves;
	int max_value;
};
Sciezka *first;
Sciezka*** sasiady; Sciezka* drzewo; long int * tablica_num;
vector<Sciezka*> vec_sciezka;
void calculate_normal(Sciezka *a, int mm) {
	a->moves[0].value = a->value;
	a->moves[0].path = a;
	a->counted = true;
	if (a->down_value_l >= a->down_value_r) {
		a->moves[1].value = a->value + a->down_value_l;
		a->moves[1].path = a->childLeft;
	}
	else {
		a->moves[1].value = a->value + a->down_value_r;
		a->moves[1].path = a->childRight;
	}


	for (size_t i = 0; i < mm ; i++)
	{
		int ac = 1;

		for (size_t j = 0; j < mm ; j++)
		{
			int value = a->childLeft->moves[i].value;
			int vakue = a->childRight->moves[j].value;
			

			if (i == 0 && j == 0) {
				continue;
			}
			if (a->childLeft->taken[i] == false) {
				if (value >= vakue) {
					int vm = value + a->value;
					if (a->moves[ac + 1].value < vm) {
					a->moves[ac + 1].value = vm;
					a->moves[ac + 1].path = a->childLeft;
					//	ac++;
					}
					a->childLeft->taken[i] = true;
				}
				if (value < vakue) {
					if (value < 0) {
						if (a->childLeft->value + vakue + a->value > a->moves[ac + 1].value) {
							a->moves[ac + 1].value = a->childLeft->value + vakue + a->value;
							continue;
						}
					}
					//if (a->childRight->taken[j] == false) {
					int vm = vakue + a->value;
					if (a->moves[ac + 1].value < vm) {
					a->moves[ac + 1].value = vm;
					a->moves[ac + 1].path = a->childRight;
					//	ac++;
					}
					a->childRight->taken[j] = true;
					//}
				}
			}
			if (a->childLeft->taken[i] == true) {
				//if (value < vakue) {
				if (a->childRight->taken[j] == false) {
					int vm = vakue + a->value;
					if (a->moves[ac + 1].value < vm) {
					a->moves[ac + 1].value = vm;
					a->moves[ac + 1].path = a->childRight;
					//	ac++;
					}
					a->childRight->taken[j] = true;
				}
				//}
			}

			//if (a->childLeft->taken[i] == false) {
			//	if (value >= vakue) {
			//		int vm = value + a->value;
			//		if (a->moves[ac] < vm) {
			//			a->moves[ac] = vm;
			//			//	ac++;
			//		}
			//		a->childLeft->taken[i] = true;
			//		//ac++;
			//		//break;
			//	}						
			//}else {
			//	if (a->childRight->taken[j] == false) {
			//		//ac++;
			//		int vm = vakue + a->value;
			//		if (a->moves[ac] < vm&&vakue>0) {
			//			a->moves[ac] = vm;
			//		}
			//		a->childRight->taken[j] = true;
			//		//break;
			//		//ac++;
			//	}
			//}
			ac++;
		}
	}
}
void calculate_all(Sciezka *a, int mm) {
	a->counts[0] = a->value;
	a->moves[0].path = a;
	a->counted = true;
	if (a->down_value_l >= a->down_value_r) {
		a->counts[1] = a->value + a->down_value_l;
		a->moves[1].path = a->childLeft;
	}
	else {
		a->counts[1]= a->value + a->down_value_r;
		a->moves[1].path = a->childRight;
	}


	for (size_t i = 0; i < mm - 1; i++)
	{
		for (int ia = 0; ia < mm + 1; ia++) {
			//a->childLeft->taken[ia] = false;
			//a->childRight->taken[ia] = false;
		}
		int ac = 1;

		for (size_t j = 0; j < mm - 1; j++)
		{
			int value = a->childLeft->moves[i].value;
			int vakue = a->childRight->moves[j].value;
			if (value == 0 && vakue == 0) {
				return;
			}
			if (i == 0 && j == 0) {
				continue;
			}
			if (a->childLeft->taken[i] == false) {
				if (value >= vakue) {
					int vm = a->counts[ac] + a->childLeft->moves[i].path->value;
					if (a->counts[ac + 1] < vm) {
					a->counts[ac + 1] = vm;
					a->max_value += a->value;
					//	ac++;
					}
					a->childLeft->taken[i] = true;
				}
				if (value < vakue) {
					//if (a->childRight->taken[j] == false) {
					int vm = a->counts[ac] + a->childRight->moves[i].path->value;
					if (a->counts[ac + 1] < vm) {
						a->counts[ac + 1] = vm;
						a->max_value += a->value;
						//	ac++;
					}
					a->childRight->taken[j] = true;
					//}
				}
			}
			if (a->childLeft->taken[i] == true) {
				//if (value < vakue) {
				if (a->childRight->taken[j] == false) {
					int vm = a->counts[ac] + a->childRight->moves[i].path->value;
					if (a->counts[ac + 1] < vm) {
						a->counts[ac + 1] = vm;
						a->max_value += a->value;
						//	ac++;
					}
					a->childRight->taken[j] = true;
				}
				//}
			}

			//if (a->childLeft->taken[i] == false) {
			//	if (value >= vakue) {
			//		int vm = value + a->value;
			//		if (a->moves[ac] < vm) {
			//			a->moves[ac] = vm;
			//			//	ac++;
			//		}
			//		a->childLeft->taken[i] = true;
			//		//ac++;
			//		//break;
			//	}						
			//}else {
			//	if (a->childRight->taken[j] == false) {
			//		//ac++;
			//		int vm = vakue + a->value;
			//		if (a->moves[ac] < vm&&vakue>0) {
			//			a->moves[ac] = vm;
			//		}
			//		a->childRight->taken[j] = true;
			//		//break;
			//		//ac++;
			//	}
			//}
			ac++;
		}
	}
}
void count(Sciezka* a, int mm) {
	if (a == nullptr) {
		return;
	}
	if (a->childLeft == nullptr&&a->childRight == nullptr) {
		a->moves[0].value = a->value;
		a->moves[0].path = a;
		a->max_moves = 0;
		a->max_value = a->value;
		a->max_moves = 0;
		a->counted = true;
		if (a != nullptr) {
			count(a->parent,mm);
		}
		return;
	}
	if (a->childLeft != nullptr&&a->childRight != nullptr) {
		if (a->childLeft->counted == false && a->childRight->counted == false) {
			return;
		}
		if (a->childLeft->counted == true && a->childRight->counted == true) {
		calculate_normal(a, mm);
		if (a != nullptr) {
			count(a->parent, mm);
		}
		}
	}
}
int check(int start, int n) {
	//int ret = 0;
	//int jump = 0;
	////drzewo[start].moves[0] = drzewo[start].value;
	////for (int h = start; h > 0; h=drzewo[h].parent->number-1) {
	//Sciezka *a = &drzewo[start];
	///*if (a->childLeft != nullptr) {
	//if (a->childRight != nullptr) {
	//if (a->down_value_l < a->down_value_r) {
	//a = a->childRight;
	//}else{
	//a = a->childLeft;
	//}
	//}else{
	//a = a->childLeft;
	//}
	//}*/
	//while (a != nullptr) {
	//	if (a->childRight == nullptr && a->childLeft == nullptr) {
	//		jump++;
	//		if (a->counted == false) {
	//			int b = 0;
	//			if (drzewo[start].moves[jump-1] != a->value) {
	//				b = drzewo[start].moves[jump-1];
	//				drzewo[start].moves[jump] = b + a->value;
	//			}
	//			
	//			a->counted = true;
	//		}
	//		//drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->value;
	//		break;
	//	}
	//	if (a->childLeft == nullptr) {
	//		//jump++;
	//		if (a->counted == false) {
	//			int b = 0;
	//			if (drzewo[start].moves[jump] != a->value) {
	//				b = drzewo[start].moves[jump];
	//				drzewo[start].moves[jump + 1] = b + a->value;
	//			}
	//			else {
	//				drzewo[start].moves[jump] = a->value;
	//			}
	//			a->counted = true;
	//		}
	//		a = nullptr;
	//		break;
	//	}
	//	if (a->childRight == nullptr) {
	//		if (a->childLeft->counted == false){
	//		jump++;
	//		drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_l;
	//		a = a->childLeft;
	//		}
	//		//h = 0;
	//		//jump++;
	//		continue;
	//	}
	//	if (a->childRight != nullptr && a->childLeft != nullptr) {
	//		//drzewo[start].moves[0] = a->value;
	//		jump++;
	//		if (a->down_value_l < a->down_value_r){
	//			if (a->childRight->counted == false) {
	//				drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_r;
	//				a->counted = true;
	//				a = a->childLeft;
	//			}
	//			else {
	//				a = a->childLeft;
	//						}
	//			continue;
	//			//jump++;
	//		}
	//		if (a->down_value_l >= a->down_value_r){
	//			if (a->childLeft->counted == false) {
	//				drzewo[start].moves[jump] = drzewo[start].moves[jump - 1] + a->down_value_l;
	//				a->counted = true;
	//				a = a->childRight;
	//			}
	//			else {
	//				a = a->childRight;
	//				}
	//			continue;
	//			//jump++;
	//		}
	//	}
	//	
	//	//jump++;
	//}
	//drzewo[start].max_moves = jump;
	return 0;
}


//int* count(int i, int moves_left, Sciezka* sciezka, int moves) {
//	//Sciezka *sciezka = first;
//	int ilosc = 0;
//	int val = 0;
//	int gd = moves_left;
//	while (sciezka->childLeft != nullptr&&ilosc <= moves_left) {
//		if (sciezka->childRight != nullptr) {
//			if (gd > sciezka->childLeft->max_moves) {
//				gd = sciezka->childLeft->max_moves;
//			}
//			if (sciezka->childLeft->moves[gd] >= sciezka->childRight->moves[gd]) {
//				sciezka->childLeft->moves[gd-1] -= sciezka->childLeft->value;
//				if (sciezka->childLeft->taken == false) {
//					sciezka = sciezka->childLeft;
//					val += sciezka->value;
//					ilosc++;
//					sciezka->taken = true;
//					//sciezka = sciezka->childLeft;
//					//continue;
//				}
//				else {
//					sciezka = sciezka->childRight;
//					val += sciezka->value;
//					ilosc++;
//					sciezka->taken = true;
//				}
//				continue;
//			}
//			if (sciezka->childLeft->moves[gd] < sciezka->childRight->moves[gd]) {
//				sciezka->childRight->moves[gd-1] -= sciezka->childRight->value;
//				sciezka = sciezka->childRight;
//				//sciezka->moves[moves_left] = 0;
//			if (sciezka->taken == false) {
//					val += sciezka->value;
//					ilosc++;
//					sciezka->taken = true;
//					//continue;
//				}
//				else {
//					sciezka = sciezka->childLeft;
//					val += sciezka->value;
//					ilosc++;
//					sciezka->taken = true;
//				}
//				continue;
//			}
//		}
//		else {
//			//if (sciezka->childLeft->taken == false) {
//				sciezka->childLeft->moves[gd-1] -= sciezka->childLeft->value;
//				sciezka = sciezka->childLeft;
//				val += sciezka->value;
//				ilosc++;
//				sciezka->taken = true;
//				//sciezka = sciezka->childLeft;
//				//continue;
//			//}
//		}
//	}
//
//	if	(sciezka->childLeft == nullptr&&sciezka->childRight == nullptr) {
//		//val += sciezka->value;
//		//ilosc++;
//		//sciezka->taken = true;
//		int max_next = 0;
//		while (sciezka->parent != sciezka) {
//			sciezka = sciezka->parent;
//			if (sciezka->childRight != nullptr) {
//				if (sciezka->childLeft->moves[moves - ilosc] >= sciezka->childRight->moves[moves - ilosc]) {
//					if (sciezka->childLeft->moves[moves - ilosc] >= max_next) {
//						first = sciezka->childLeft;
//						max_next = sciezka->childLeft->moves[moves - ilosc];
//					}
//				}
//				else {
//					if (sciezka->childRight->moves[moves - ilosc] >= max_next) {
//						first = sciezka->childRight;
//						max_next = sciezka->childRight->moves[moves - ilosc];
//					}
//				}
//			}
//		}
//		//sciezka = first;
//	}
//	int a[2];
//	a[0] = ilosc;
//	a[1] = val;
//	return a;
//}

int main()
{
	int n, m;
	cin >> n >> m;
	drzewo = new Sciezka[n];
	tablica_num = new long int[n];
	//sasiady = new Sciezka**[n + 2];
	//for (int i = 0; i < n + 2; i++) {
	//	sasiady[i] = new Sciezka*[n + 2];
	//	for (int j = 0; j < n + 2; j++) {
	//		sasiady[i][j] = nullptr;
	//	}
	//}
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
		drzewo[i].max_value = 0;
		drzewo[i].taken = false;
		drzewo[i].moves = new moveX[m + 1];
		drzewo[i].taken = new bool[m + 1];
		drzewo[i].counts = new int[m + 1];
		for (int ia = 0; ia < m + 1; ia++) {
			drzewo[i].counts[ia] = 0;
			drzewo[i].taken[ia] = false;
		}
		if (n1 == 1) {
			first = &drzewo[i];
		}
		vec_sciezka.push_back(&drzewo[i]);
		//sasiady[n2][n1] = &drzewo[i];
	}
	/*for (int i = 0; i < vec_sciezka.size(); i++) {
		Sciezka* a = vec_sciezka[i];
		for (int j = 0; j < vec_sciezka.size(); j++) {
			if (j == i) { continue; }
			if (a->number == vec_sciezka[j]->p_number  && a->value != vec_sciezka[j]->value || a->number == vec_sciezka[j]->p_number && a->value!= vec_sciezka[j]->value) {
				vec_sciezka[j]->parent = a;
				continue;
			}
			
		}
	}*/
	Sciezka *start = first;
	while (start->p_number != n + 1 && start->number != n + 1) {
		for (int j = 0; j < vec_sciezka.size(); j++) {
			if (vec_sciezka[j]->number == start->number || vec_sciezka[j]->p_number == start->number) {
				if (vec_sciezka[j]->value != start->value) {
					if (start->childLeft == nullptr) {
						start->childLeft->parent = start;
						start->childLeft = vec_sciezka[j];
						start->down_value_l = vec_sciezka[j]->value;
						start = &drzewo[j];
					}
					else {
						start->childRight->parent = start;
						start->childRight = vec_sciezka[j];
						start->down_value_r = vec_sciezka[j]->value;
					}
				}
			}
		}
	}
	//for (int i = n+1; i > 0; i--) {
	//	for (int j = n+1; j > 0; j--) {
	//		if (sasiady[i][j] == nullptr) {
	//			//cout << "_ ";
	//		}
	//		else {
	//			if (tablica_num[j] > 0) {
	//				drzewo[tablica_num[i]].parent = &drzewo[tablica_num[j]];
	//			}
	//			if (tablica_num[i] > 0) {
	//				drzewo[tablica_num[j]].parent = &drzewo[tablica_num[i]];
	//			}
	//			//cout << "1" << " ";
	//		}
	//	}
	//	//cout << endl;
	//}
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





	for (int i = vec_sciezka.size()-1; i >= 0; i--) {
		//if (i > 0) {
		if (drzewo[i].childLeft == nullptr&&drzewo[i].childRight == nullptr&&drzewo[i].parent!=nullptr) {
			count(&drzewo[i], m);
		}
		//}
	}
	//calculate_all(first, m);
	for(int i=0;i<n;i++){
		cout << &drzewo[i] << endl;
	cout << drzewo[i].p_number << endl;
		cout << drzewo[i].number << endl;
		cout << drzewo[i].value << endl;
		cout << drzewo[i].parent << endl;

		cout << drzewo[i].childLeft << endl;
		cout << drzewo[i].childRight << endl;
		//for (int h = 0; h <= m; h++) {
		/*	cout << "moves:" << endl << h << ":" << drzewo[i].moves[h].value << endl;
		}
		cout << drzewo[i].down_value_l << endl;
		cout << drzewo[i].down_value_r << endl << endl;*/
		cout << endl << endl;
		//int x = 0;
		//cin >> x;
	}


	int cn = 0;
	//int max_val =first->value;
	//first->taken = true;
	//int moves = m-1;
	//int moves_done = 0;
	//Sciezka *cnx = first;
	//while (moves_done < moves) {
	//	//int* x = count(0, moves - moves_done-1,cnx,moves);
	//	//moves_done += x[0];
	//	//max_val += x[1];
	//}
	//
	cout << first->moves[m-1].value << endl;
	return 0;
}
