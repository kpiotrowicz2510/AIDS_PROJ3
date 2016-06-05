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
			if (i < 3) {
				connections[i].s = nullptr;
			}
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
};


Sciezka *first;
Sciezka*** sasiady; Sciezka* drzewo; long int * tablica_num;


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
	for (size_t j = 3; j < mm; j++)
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

void connect(Sciezka* sciezka, Sciezka* parent, int n) {
	for (int i = 0; i < 3; i++) {
		if (sciezka->connections[i].s == nullptr) {
			break;
		}
		if (sciezka->connections[i].s != nullptr&&sciezka->childLeft == nullptr && sciezka->connections[i].s != parent) {
			sciezka->childLeft = sciezka->connections[i].s;
			sciezka->childLeft->value = sciezka->connections[i].value;
				connect(sciezka->childLeft, sciezka, n);
		}else if(sciezka->connections[i].s != nullptr&&sciezka->childRight == nullptr && sciezka->connections[i].s != parent){
			sciezka->childRight = sciezka->connections[i].s;
			sciezka->childRight->value = sciezka->connections[i].value;
			connect(sciezka->childRight, sciezka, n);
		}else if(sciezka->connections[i].s != nullptr&&sciezka->connections[i].s == parent){
			sciezka->parent = sciezka->connections[i].s;
		}
	}
}
Sciezka* root;
int main()
{
	int n, m;
	scanf_s("%i %i", &n, &m);
	//cin >> n >> m;
	maxKROKOW = m;
	drzewo = new Sciezka[n+2];
	tablica_num = new long int[n];
	root = new Sciezka();
	for (int j = 0; j < n; j++) {
		int n1, n2, val;
		scanf_s("%i %i %i", &n1, &n2, &val);
		//cin >> n1 >> n2 >> val;	
		drzewo[n1-1].addConnection(&drzewo[n2-1],val);
		drzewo[n2-1].addConnection(&drzewo[n1-1],val);
		
	}
	
	connect(&drzewo[0], nullptr, n);
	
	drzewo[0].value =0;
	Sciezka *a = nullptr;
	drzewo[0].childLeft->parent = nullptr;
	a = drzewo[0].childLeft;
	for (int i = n; i > 0; i--) {
		count(&drzewo[i], m);
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
