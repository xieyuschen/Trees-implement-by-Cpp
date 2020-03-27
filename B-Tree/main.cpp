#include<iostream>
#include"DemoBSTree.h"
#include<vector>
#include<set>
using namespace std;
int main() {

	BSTree<int> tint;
	for (int i = 1; i < 6; i++) {
		cout << tint.insert(i);
	}
	for (int i = 1; i < 6; i++) {
		tint.Remove(tint.Min());
	}
}