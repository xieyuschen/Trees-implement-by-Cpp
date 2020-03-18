#include<iostream>
#include"SetMe.h"
#include<vector>
using namespace std;
int main() {
	SetMe<int> set;
	for (int i = 1; i <100; i++) {
		set.insert(i);
	}
	set.Show();

}