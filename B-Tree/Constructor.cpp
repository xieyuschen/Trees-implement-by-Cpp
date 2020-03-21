#include<iostream>
using namespace std;
template<typename T>
class Node {
public:
	Node() :data(0), child(nullptr) {};
	Node(T val, Node* c) :data(val), child(c) {};
	void swap(Node& n1, Node& n2) {
		std::swap(n1.data, n2.data);
		std::swap(n1.child, n2.child);
	}
	Node<T>* child;
	T data;
};

int main() {
	Node<int> head, tail;
	head.child = &tail;
	head.data = 1;
	tail.data = 3;
	swap(head, tail);
	cout << tail.child<<endl<<&tail;
}