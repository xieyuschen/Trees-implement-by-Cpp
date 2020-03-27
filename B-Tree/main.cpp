#include<iostream>
#include"BinarySearchTree.h"
#include<vector>
#include<set>
using namespace std;
int main() {
	Bstree t{ 1,2,3,4,5 };
	cout << t.empty() << endl;;
	for (int i = 0; i < 10; i++) {
		cout << t.Add(i)<<ends;
	}

}