#ifndef BSTREE_H
#define BSTREE_H
#include<initializer_list>
class Node
{
public:
	Node(int val=0) :value(val), left(nullptr), right(nullptr),count(new int(1)) {};
	Node(const Node& rhs):value(rhs.value),left(rhs.left),right(rhs.right),count(new int(1)) {}
	Node& operator=(const Node& rhs) {
		count++;
		*this=Node(rhs);
		return *this;
	}
	~Node() {
		if (!count--) {
			left = right = nullptr;
		}
	}
public:
	int value;
	int* count;
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
	bool Remove(const int&);

private:
	bool Isleft(Node*,Node*);
	Node* findMin(Node*);
	Node* findMax(Node*);
private:
	size_t size;
	Node* root;
};
#endif // !BSTREE
