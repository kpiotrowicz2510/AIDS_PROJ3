// AIDS_PROJ3.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

using namespace std;
int maxKROKOW= 500;
class Sciezka;
struct Node {
	Sciezka *s;
	int value;
	int number;
	int p_number;
};
vector<Node> nodes;
class Sciezka {
	
public:
	//int p_number;
	//int number;
	//int index;
	int value;
	Sciezka* parent;
	Sciezka* childLeft;
	Sciezka* childRight;
	Node connections[3];
	int down_value_l;
	
	int down_value_r;
	int *counts;
	bool taken;
	bool counted;
	int max_moves;
	int max_value;
	Sciezka() {
		value = 1;
		childLeft = nullptr;
		childRight = nullptr;
		parent = nullptr;
		counts = new int[maxKROKOW];
		for (int i = 0; i < maxKROKOW; i++) {
			counts[i] = 0;
		}
		for (int i = 0; i < 3; i++) {
			connections[i].s = nullptr;
		}
	}
	void addConnection(Sciezka* sc, int weight) {
		//if (sc->value == 0) {
		//}
		for (int i = 0; i < 3; i++) {
			if (connections[i].s == nullptr) {
				connections[i].s = sc;
				connections[i].value = weight;
				break;
			}
		}
	}
	void setParent(Sciezka* parent) {
			if (parent == nullptr) {
				this->childRight = this->childLeft;
				this->childLeft = this->parent;
			}
			else {
				if (parent == this->childLeft) {
					this->childLeft = this->parent;
					this->parent = parent;
				}
				else if (parent == this->childRight) {
					this->childRight = this->parent;
					this->parent = parent;
				}
			}
	}
};


Sciezka *first;
Sciezka*** sasiady; Sciezka* drzewo; long int * tablica_num;
vector<Sciezka*> vec_sciezka;


void calculate_normal(Sciezka *a, int mm) {
	//cout << "C:" << a->value;
	a->counts[1] = a->value;
	//a->moves[0].path = a;
	a->counted = true;
	if (a->childLeft->value >= a->childRight->value) {
		a->counts[2] = a->value+a->childLeft->value;
		//a->moves[1].path = a->childLeft;
		a->counts[3] = a->value + a->childLeft->value + a->childRight->value;
	}
	else {
		a->counts[2] = a->value+a->childRight->value;
		//a->moves[1].path = a->childRight;
		a->counts[3] = a->value + a->childLeft->value + a->childRight->value;
	}
	int max = 0;
	int ac = 0;
	for (size_t j = 4; j < mm; j++)
	{
		for (size_t i = 0; i < j; i++)
		{
			int r = j - i - 1;
			//for (size_t j = 0; j < mm ; j++)
			//{
			int value = a->childLeft->counts[i];
			int vakue = a->childRight->counts[r];


			if (value + vakue + a->value> a->counts[j]) {
				a->counts[j] = value + vakue + a->value;
				ac++;
			}
		}
	}
	
}
void calculate_all(Sciezka *a, int mm) {
	//a->counts[0] = a->value;
	////a->moves[0].path = a;
	//a->counted = true;
	//if (a->down_value_l >= a->down_value_r) {
	//	a->counts[1] = a->value + a->down_value_l;
	////	a->moves[1].path = a->childLeft;
	//}
	//else {
	//	a->counts[1]= a->value + a->down_value_r;
	//	//a->moves[1].path = a->childRight;
	//}


	//for (size_t i = 0; i < mm - 1; i++)
	//{
	//	for (int ia = 0; ia < mm + 1; ia++) {
	//		//a->childLeft->taken[ia] = false;
	//		//a->childRight->taken[ia] = false;
	//	}
	//	int ac = 1;

	//	for (size_t j = 0; j < mm - 1; j++)
	//	{
	//		//int value = a->childLeft->moves[i].value;
	//		//int vakue = a->childRight->moves[j].value;
	//		if (value == 0 && vakue == 0) {
	//			return;
	//		}
	//		if (i == 0 && j == 0) {
	//			continue;
	//		}
	//		if (a->childLeft->taken[i] == false) {
	//			if (value >= vakue) {
	//			//	int vm = a->counts[ac] + a->childLeft->moves[i].path->value;
	//				if (a->counts[ac + 1] < vm) {
	//				a->counts[ac + 1] = vm;
	//				a->max_value += a->value;
	//				//	ac++;
	//				}
	//				a->childLeft->taken[i] = true;
	//			}
	//			if (value < vakue) {
	//				//if (a->childRight->taken[j] == false) {
	//			//	int vm = a->counts[ac] + a->childRight->moves[i].path->value;
	//			//	if (a->counts[ac + 1] < vm) {
	//					a->counts[ac + 1] = vm;
	//					a->max_value += a->value;
	//					//	ac++;
	//				}
	//				a->childRight->taken[j] = true;
	//				//}
	//			}
	//		}
	//		if (a->childLeft->taken[i] == true) {
	//			//if (value < vakue) {
	//			if (a->childRight->taken[j] == false) {
	//			//	int vm = a->counts[ac] + a->childRight->moves[i].path->value;
	//			//	if (a->counts[ac + 1] < vm) {
	//					a->counts[ac + 1] = vm;
	//					a->max_value += a->value;
	//					//	ac++;
	//				}
	//				a->childRight->taken[j] = true;
	//			}
	//			//}
	//		}

	//		//if (a->childLeft->taken[i] == false) {
	//		//	if (value >= vakue) {
	//		//		int vm = value + a->value;
	//		//		if (a->moves[ac] < vm) {
	//		//			a->moves[ac] = vm;
	//		//			//	ac++;
	//		//		}
	//		//		a->childLeft->taken[i] = true;
	//		//		//ac++;
	//		//		//break;
	//		//	}						
	//		//}else {
	//		//	if (a->childRight->taken[j] == false) {
	//		//		//ac++;
	//		//		int vm = vakue + a->value;
	//		//		if (a->moves[ac] < vm&&vakue>0) {
	//		//			a->moves[ac] = vm;
	//		//		}
	//		//		a->childRight->taken[j] = true;
	//		//		//break;
	//		//		//ac++;
	//		//	}
	//		//}
	//		ac++;
	//	}
	//}
}
void count(Sciezka* az, int mm) {
	if (az == nullptr) {
		return;
	}
	if (az->childLeft == nullptr&&az->childRight == nullptr) {
		az->counts[1] = az->value;
		//az->moves[0].path = az;
		az->max_moves = 0;
		az->max_value = az->value;
		az->max_moves = 0;
		az->counted = true;
		if (az->parent != nullptr) {
			count(az->parent,mm);
		}
		return;
	}
	if (az->childLeft != nullptr&&az->childRight == nullptr) {
		az->counts[1] = az->value;
		az->counts[2] = az->value+az->down_value_l;
		//az->moves[0].path = az;
		az->max_moves = 0;
		az->max_value = az->value;
		az->max_moves = 0;
		az->counted = true;
		return;
	}
	if (az->childLeft != nullptr&&az->childRight != nullptr) {
		if (az->childLeft->counted == false && az->childRight->counted == false) {
			return;
		}
		if (az->childLeft->counted == true && az->childRight->counted == true) {
			
				calculate_normal(az, mm);
				if (az->parent != nullptr) {
					count(az->parent, mm);
				}
			//}
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
void connect2(Sciezka* ax, int n) {
	int num = 0;

	for (int j = 0; j < nodes.size(); j++) {
		if (nodes[j].s != nullptr&&nodes[j].number == num&&nodes[j].s != ax&&nodes[j].s->parent == nullptr) {
			nodes[j].s->parent = ax;
			if (ax->childLeft == nullptr) {
				ax->childLeft = nodes[j].s;
			}
			else {
				if (ax->childRight == nullptr) {
					ax->childRight = nodes[j].s;
				}
			}
			connect2(nodes[j].s, n);
		}
	}
}
void connect(Sciezka* node, Sciezka* parent, int n) {
	for (int i = 0; i < 3; i++) {
		if (node->connections[i].s == nullptr) {
			break;
		}
		if (node->connections[i].s != nullptr&&node->childLeft == nullptr && node->connections[i].s != parent) {
			node->childLeft = node->connections[i].s;
			node->childLeft->value = node->connections[i].value;
				connect(node->childLeft, node, n);
		}else if(node->connections[i].s != nullptr&&node->childRight == nullptr && node->connections[i].s != parent){
			node->childRight = node->connections[i].s;
			node->childRight->value = node->connections[i].value;
			connect(node->childRight, node, n);
		}else if(node->connections[i].s != nullptr&&node->connections[i].s == parent){
			node->parent = node->connections[i].s;
		}
	}
}
Sciezka* root;
int main()
{
	int n, m;
	cin >> n >> m;
	maxKROKOW = m;
	drzewo = new Sciezka[n+2];
	tablica_num = new long int[n];
	root = new Sciezka();
	for (int j = 0; j <= n; j++) {
	//	drzewo[j].index = j + 1;
	}
	for (int j = 0; j < n; j++) {
		int n1, n2, val;
		cin >> n1 >> n2 >> val;
		int i = j;
	
		drzewo[n1-1].addConnection(&drzewo[n2-1],val);
		drzewo[n2-1].addConnection(&drzewo[n1-1],val);
		
	}
	
	connect(&drzewo[0], nullptr, n);
	
	drzewo[0].value =0;
	Sciezka *a = nullptr;
	for (int i = 0; i < n + 1; i++) {
		if (drzewo[i].parent == &drzewo[0]) {
			a = &drzewo[i];
			a->parent = nullptr;
		}
	}
	for (int i = n; i > 0; i--) {
		//if (i > 0) {
		//if (drzewo[i].childLeft == nullptr&&drzewo[i].childRight == nullptr&&drzewo[i].parent!=nullptr) {
		count(&drzewo[i], m);
		//}
		//}
	}
	//for (int i = 0; i <= n; i++) {
	//	cout << i << ":";
	//	cout << &drzewo[i] << endl;
	//	//cout << drzewo[i].p_number << "  " << drzewo[i].number << endl;
	//	//cout << drzewo[i].number << endl;
	//	cout << drzewo[i].value << endl;
	//	cout << drzewo[i].parent << endl;

	//	cout << drzewo[i].childLeft << endl;
	//	cout << drzewo[i].childRight << endl;
	//	for (int h = 0; h < m; h++) {
	//		cout << "moves:" << endl << h << ":" << drzewo[i].counts[h] << endl;
	//	}
	//	//cout << drzewo[i].down_value_l << endl;
	//	//cout << drzewo[i].down_value_r << endl << endl;
	//	cout << endl << endl;
	//	//int x = 0;
	//	//cin >> x;
	//}

	
	//calculate_all(first, m);
	

	int max = 0;
	for (size_t i = 0; i < m; i++)
	{
		int r = m - i - 1;
		//for (size_t j = 0; j < mm ; j++)
		//{
		int value = a->childLeft->counts[i];
		int vakue = 0;
		if (a->childRight != nullptr) {
			vakue = a->childRight->counts[r];
		}

		if (value + vakue + a->value> max) {
			max = value + vakue + a->value;
		}

	}
	//max = max + a->value;
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
	cout << max << endl;
	return 0;
}
