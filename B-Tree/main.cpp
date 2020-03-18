#include<iostream>
#include"SetMe.h"
using namespace std;
int main() {
	SetMe<int> set;
	for (int i = 0; i < 220; i++) {
		cout << set.insert(i) << ends;
	}
	cout<<endl << set.insert(3);
}