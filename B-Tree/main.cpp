#include<iostream>
#include"SetMe.h"
#include<vector>
using namespace std;
int main() {
	SetMe<int> set;
	for (int i = 1; i <8; i++) {
		/*cout << set.insert(i) << ends;*/
		cout<<set.insert(i);
	}
	set.insert(8);
	set.Show();


	//cout << endl << set.insert(3) << endl;
	//vector<SetMe<int>*> path;
	//vector<int> index;
	//set.loose_remove(200, path, index);

}