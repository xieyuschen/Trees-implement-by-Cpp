#include<iostream>
#include"SetMe.h"
#include<vector>
using namespace std;
int main() {
	size_t t = 1;
	SetMe<int> set;
	for (int i = 1; i < 18; i++) {
		set.insert(i);
	}
	vector<SetMe<int>*> vec1;
	vector<int> vec2;
	set.loose_remove(1,vec1,vec2);
	vec1[1]->fix_shortage(0);
	set.Show();

}