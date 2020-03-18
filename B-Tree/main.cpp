#include<iostream>
#include"SetMe.h"
#include<vector>
using namespace std;
int main() {
	SetMe<int> set;
	for (int i = 0; i < 220; i++) {
		cout << set.insert(i) << ends;
	}
	cout << endl << set.insert(3) << endl;
	vector<SetMe<int>*> path;
	vector<int> index;
	cout << set.loose_remove(1, path, index) << endl;
	cout << endl << set.insert(1) << endl;
	cout << endl << set.insert(1) << endl;

}