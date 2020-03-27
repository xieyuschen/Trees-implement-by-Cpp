#include"BinarySearchTree.h"
using namespace std;

bool Bstree::empty() {
	return size ? false : true;
}
bool Bstree::Add(const int &val) {
	if (empty()) {
		++size;
		root->value = val;
		return true;
	}
	Node* temp;
	temp = root;
	while (true) {
		if (val < temp->value) {
			if (temp->left == nullptr) {
				temp->left = new Node(val);
				return true;
			}
			else
			{
				temp = temp->left;
			}
		}
		else if (val > temp->value) {
			if (temp->right == nullptr) {
				temp->right = new Node(val);
				++size;
				return true;
			}
			else {
				temp = temp->right;
			}
		}
		else
		{
			return false;
		}
	}

}