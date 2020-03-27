#include<iostream>
#include"BinarySearchTree.h"
#include<vector>
#include<set>
using namespace std;
int main() {
	Bstree t{ 3,1,2,4,5 };
	cout << t.empty() << endl;;
	for (int i = 1; i < 6; i++) {
		cout << t.Remove(i);

	}


}