#define BINARY_SEARCH_TREE_H
#ifdef  BINARY_SEARCH_TREE_H
#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
template<typename T>
class Node {
public:
	T _key;
	Node<T>* _left;
	Node<T>* _right;
	Node<T>* _parent;
	Node(const T& key) :_key(key), _left(nullptr), _right(nullptr), _parent(nullptr) {}
};


template<typename T>
class BSTree {
	typedef Node<T> Node;
private:
	Node* Troot;
public:
	//写的代码出问题主要原因即构造函数没有写好
	//对NULL
	BSTree() :Troot(NULL) {}
	bool empty() {
		if (Troot == NULL)
			return true;
		else return false;
	}
	bool insert(T val) {

		Node* neu = new Node(val);
		if (empty())
		{
			Troot = neu;
			return true;
		}
		Node* p = Troot;
		Node* temp = nullptr;
		while (p) {
			temp = p;
			if (val < p->_key)
				p = p->_left;
			else if (val > p->_key) p = p->_right;
			else return false;
		}
		if (temp->_key > val) {
			temp->_left = neu;
			neu->_parent = temp;
		}
		else if (temp->_key < val) {
			temp->_right = neu;
			neu->_parent = temp;
		}
		else return false;
		return true;


	}
	Node* Max() {
		return HelpMax(Troot);
	}
	Node* Min() {
		return HelpMin(Troot);
	}

	bool Search(T val) {
		Node* p = Troot;
		Node* temp = nullptr;
		while (p) {
			if (val < p->_key) {
				p = p->_left;
			}
			else if (val > p->_key) {
				p = p->_right;
			}
			else return true;
		}
		return false;
	}
	void Preorder() {
		HelpPreorder(Troot);
		cout << endl;

	}
	void Inorder() {
		HelpInorder(Troot);
		cout << endl;

	}
	void Postorder() {
		HelpPostorder(Troot);
		cout << endl;
	}

	//the min node in the right subtree
	Node* Successor(Node* x) {
		if (x->_right) {
			return HelpMin(x->_right);
		}
	}

	//the max node in the left subtree
	Node* Processor(Node* x) {
		if (x->_left) {
			return HelpMax(x->_left);
		}
	}
	void Remove(Node* x) {
		if (!(x->_left) && !(x->_right)) {
			if (x->_parent->_right == x)  x->_parent->_right = nullptr;
			else	x->_parent->_left = nullptr;


		}
		else if (x->_left || x->_right) {
			if (x->_left) {
				x->_left->_parent = x->_parent;
				x->_parent->_left = x->_left;
				x = nullptr;
			}
			else {
				x->_left->_parent = x->_parent;
				x->_parent->_right = x->_right;
				x = nullptr;
			}
		}
		else {
			auto temp = Successor(x);
			x = temp;
			Remove(temp);
		}
	}

	void PrintFigure() {
		int Height = GetHeight(Troot);
		vector<T>vec;
		for (int i = 0; i < Height; i++) {
			cout << setw(2 * (Height - i));
			printRow(Troot, Height, i);
		}
	}
private:
	void HelpPreorder(Node* root) {
		if (root) {
			cout << root->_key << ends;
			HelpPreorder(root->_left);
			HelpPreorder(root->_right);
		}

	}
	void HelpInorder(Node* root) {
		if (root) {
			HelpInorder(root->_left);
			cout << root->_key << ends;
			HelpInorder(root->_right);
		}
	}
	void HelpPostorder(Node* root) {
		if (root) {
			HelpPostorder(root->_left);
			HelpPostorder(root->_right);
			cout << root->_key << ends;

		}
	}
	Node* HelpSuccessor(Node* x) {
		if (x->_left) {
			x = x->_left;
		}
	}
	Node* HelpMax(Node* root) {
		Node* p = root;
		Node* temp = nullptr;
		while (p) {
			temp = p;
			p = p->_right;
		}
		return temp;
	}
	Node* HelpMin(Node* root) {
		Node* p = root;
		Node* temp = nullptr;
		while (p) {
			temp = p;
			p = p->_left;
		}
		return  temp;
	}
	int GetHeight(Node* x) {
		int Height = 0;
		if (x) {
			Height = GetHeight(x->_left) < GetHeight(x->_right) ? GetHeight(x->_right) + 1 : GetHeight(x->_left) + 1;
		}
		return Height;
	}
	void HelpPrintFigure(Node* x) {

	}
	void GetRowNodeKey(const Node* root, int depth, vector<T>& vals) {
		int placeholder = -1;
		if (depth <= 0 && root != NULL) {
			vals.push_back(root->_key);
			return;
		}
		if (root->_left)
			GetRowNodeKey(root->_left, depth - 1, vals);
		else if (depth - 1 <= 0)
			vals.push_back(placeholder);
		if (root->_right)
			GetRowNodeKey(root->_right, depth - 1, vals);
		else if (depth - 1 <= 0)
			vals.push_back(placeholder);
	}
	void printRow(const Node* p, const int height, int depth) {
		vector<T> vec;
		//int placeholder = -1;
		GetRowNodeKey(p, depth, vec);
		// start with left
		int j = height;
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i] != -1) {
				cout << vec[i] << ends;
			}
			else cout << "#" << ends;
		}
		cout << endl << setw(height - j);
	}

};

#endif