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
Sciezka* drzewo;long int * tablica_num;
int check(int start, int n) {
	int ret = 0;
	int jump = 1;
	drzewo[start].moves[0] = drzewo[start].value;
	for (int h = start; h > 0; h--) {
		if (drzewo[h].childLeft == nullptr) {
			drzewo[start].moves[jump] = drzewo[h].value;
			h =0;
			continue;
		}
		if (drzewo[h].childRight == nullptr) {
			drzewo[start].moves[jump] = drzewo[h].value+drzewo[h].down_value_l;
			h = 0;
			continue;
		}
		if (drzewo[h].childRight != nullptr && drzewo[h].childLeft != nullptr) {
			drzewo[start].moves[jump] = drzewo[h].down_value_l + drzewo[h].down_value_r;
		}
		jump++;
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
	
		//drzewo[i].number = n2;
		tablica_num[n2] = i;
		drzewo[i].value = val;
		drzewo[i].childLeft = nullptr;
		drzewo[i].childRight = nullptr;
		drzewo[i].down_value_l = 0;
		drzewo[i].down_value_r = 0;
		drzewo[i].taken = false;
		drzewo[i].moves = new int[m+1];
		for (int ia = 0; ia < m+1; ia++) {
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
		if (i > 0) {
			check(i, n);
		}
		/*cout << drzewo[i].number << endl;
		cout << drzewo[i].value << endl;
		cout << drzewo[i].parent << endl;

		cout << drzewo[i].childLeft << endl;
		cout << drzewo[i].childRight << endl;
		for (int h = 0; h < m; h++) {
			cout << "moves:" << endl << h << ":" << drzewo[i].moves[h] << endl;
		}
		cout << drzewo[i].down_value_l << endl;
		cout << drzewo[i].down_value_r << endl	<< endl;*/
	}


	int cn = 0;
	int max_val = 0;
	drzewo[0].taken = true;
	int moves = m;
	Sciezka *cnx = &drzewo[0];

	while (moves-- > 0) {
		if (cnx == nullptr) {
			//cnx = &drzewo[0];
			//drze
		}

		//max_val += (*cnx).value;
		//(*cnx).taken = true;

		if ((*cnx).childLeft == nullptr && (*cnx).childRight == nullptr) {
			max_val += (*cnx).value;
			(*cnx).taken = true;
			if (moves == 0) {
				continue;
			}
			int mx = (*cnx).moves[moves];
			int id = 0;
			int h = n - 1;
			if ((*cnx).parent != nullptr) {
				//h = tablica_num[(*(*cnx).parent).number-1];
			}
			for (int i = h; i > 1; i--) {
				if ((drzewo[i]).taken == false) {
					int mxx = drzewo[i].moves[moves];
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
		
		if((*cnx).childLeft==nullptr){
			//cnx = nullptr;
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
		max_val += (*cnx).value;
		(*cnx).taken = true;

	}
	cout << max_val << endl;
	return 0;
}

