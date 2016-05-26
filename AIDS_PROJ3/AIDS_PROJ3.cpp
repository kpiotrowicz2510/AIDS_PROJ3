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
	int down_value_r;
	int *moves;
	bool taken;
};
Sciezka* drzewo; long int * tablica_num;
int check(int start, int n) {
	int ret = 0;
	int jump = 0;
	//drzewo[start].moves[0] = drzewo[start].value;
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
	while(a!=nullptr){
		if (a->childLeft == nullptr) {
			drzewo[start].moves[jump] = a->value;			
			a = nullptr;
			continue;
		}
		if (a->childRight == nullptr) {
			jump++;
			drzewo[start].moves[jump] = drzewo[start].moves[jump-1] + a->value + a->down_value_l;
			a = a->childLeft;
			//h = 0;
			//jump++;
			continue;
		}
		if (a->childRight != nullptr && a->childLeft != nullptr) {
			drzewo[start].moves[0] = a->value;
			jump++;
			if (a->down_value_l < a->down_value_r) {
				drzewo[start].moves[jump] = drzewo[start].moves[jump-1]+ a->value + a->down_value_r;
				a = a->childRight;
				//jump++;
			}else{
				drzewo[start].moves[jump] = drzewo[start].moves[jump-1] + a->value + a->down_value_l;
				a = a->childLeft;
				//jump++;
			}
		}
		//jump++;
	}
	return ret;
}




int main()
{
	int n, m;
	cin >> n >> m;
	drzewo = new Sciezka[n];
	tablica_num = new long int[n];
	for (int i = 0; i < n; i++) {
		int n1, n2, val;
		cin >> n1 >> n2 >> val;
		if (i > 0) {
			drzewo[i].parent = &drzewo[tablica_num[n1]];
		}
		else {
			drzewo[i].parent = nullptr;
		}

		drzewo[i].number = n2;
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
		//if (i > 0) {
			check(i, n);
		//}
		/*cout << drzewo[i].number << endl;
		cout << drzewo[i].value << endl;
		cout << drzewo[i].parent << endl;

		cout << drzewo[i].childLeft << endl;
		cout << drzewo[i].childRight << endl;
		for (int h = 0; h < m; h++) {
		cout << "moves:" << endl << h << ":" << drzewo[i].moves[h] << endl;
		}
		cout << drzewo[i].down_value_l << endl;
		cout << drzewo[i].down_value_r << endl	<< endl;
		int x;
		cin >> x;*/
	}


	int cn = 0;
	int max_val = 0;
	drzewo[0].taken = true;
	int moves = m;
	Sciezka *cnx = &drzewo[0];

	while (moves-- > 0) {
		if (cnx == nullptr) {
			cnx = &drzewo[0];
			//drze
			continue;
		}

		//max_val += (*cnx).value;
		//(*cnx).taken = true;

		if ((*cnx).childLeft == nullptr && (*cnx).childRight == nullptr) {
			max_val += (*cnx).value;
			(*cnx).taken = true;
			//moves--;
			if (moves == 0) {
				continue;
			}
			int mx = 0;
			int id = 0;
			int h = cnx->number - 2;
			if ((*cnx).parent != nullptr) {
				//h = tablica_num[(*(*cnx).parent).number-1];
			}
			for (int i = h; i > 1; i--) {
				if (drzewo[i].taken == false) {
					int mxx = drzewo[i].moves[moves-1];
					if (mxx > mx) {
						mx = mxx;
						id = i;
					}
				}
			}
			//(drzewo[id]).taken = true;
			cnx = &drzewo[id];
			//max_val += (*cnx).value;
			//continue;
		}

		if ((*cnx).childLeft == nullptr) {
			cnx = cnx->parent;
			moves++;
			continue;
		}
		int* a = (*(*cnx).childLeft).moves;
		int left = a[moves];
		int right = -1;
		int* b;
		if ((*cnx).childRight != nullptr) {
			b = (*(*cnx).childRight).moves;
			right = b[moves];
		}

		max_val += (*cnx).value;
		(*cnx).taken = true;
		if (left >= right) {
			//max_val += (*cnx).value;
			//(*cnx).taken = true;
			cnx = (*cnx).childLeft;
		}
		if (left < right) {
			//max_val += (*cnx).value;
			//(*cnx).taken = true;
			cnx = (*cnx).childRight;
		}
		//max_val += (*cnx).value;
		//(*cnx).taken = true;

	}
	cout << max_val << endl;
	return 0;
}
