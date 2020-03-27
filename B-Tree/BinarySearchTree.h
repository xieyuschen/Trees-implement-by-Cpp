#ifndef BSTREE_H
#define BSTREE_H
#include<initializer_list>
class Node
{
public:
	Node(int val=0) :value(val), left(nullptr), right(nullptr) {};
	Node(const Node& rhs):value(rhs.value),left(rhs.left),right(rhs.right) {}
	Node& operator=(const Node& rhs) {
		*this=Node(rhs);
		return *this;
	}
	~Node() = default;
public:
	int value;
	Node* left;
	Node* right;
};
class Bstree {
public:
	//可以加上一个initializer_list的初始化方式
	Bstree() :root(new Node()), size(0) {};
	Bstree(std::initializer_list<int> li):root(new Node()),size(0) {
		
		for (auto it = li.begin(); it != li.end();it++) {
			Add(*it);
		}
	}
	bool empty();
	bool Add(const int&);
private:
	size_t size;
	Node* root;
};
#endif // !BSTREE
