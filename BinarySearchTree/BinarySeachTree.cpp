#include"BinarySearchTree.h"
using namespace std;
Node* Bstree::findMin(Node* node) {
	if (!node) {
		return node;
	}
	auto temp = node;
	while (temp->left != nullptr) {
		temp = temp->left;
	}
	return temp;
}
Node* Bstree::findMax(Node* node) {
	if (!node) {
		return node;
	}
	auto temp=node;
	while (temp->right != nullptr) {
		temp = temp->right;
	}
	return temp;

}
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
bool Bstree::Isleft(Node* parent, Node* child) {
	if (parent->left == child)
		return true;
}
bool Bstree::Remove(const int& val) {
	Node* temp = root;
	Node* help = temp;
	while (temp != nullptr) {
		if (val < temp->value) {
			help = temp;
			temp = temp->left;
		}
		else if (val > temp->value) {
			help = temp;
			temp = temp->right;
		}
		else {
			break;
		}
	}
	if (temp == nullptr)return false;
	

	//如果要删除的节点是根节点
	if (temp == root) {
		auto min = findMin(temp->right);
		auto max = findMax(temp->left);
		if (min == nullptr && max == nullptr) {
			root = nullptr;
			size = 0;
			return true;
		}
		else if (min == temp->right) {
			root = min;
			root->left = temp->left;
			temp->~Node();
			size--;
			return true;
		}
		else if (max == temp->left)
		{
			root = max;
			root->right = nullptr;
			temp->~Node();
			size--;
			return true;
		}
		else if (min != temp->right && min != nullptr) {
			temp->value = min->value;
			min->~Node();
			size--;
			return true;
		}
		else if (max != temp->left && max != nullptr) {
			temp->value = max->value;
			max->~Node();
			size--;
			return true;
		}
		else {
			return false;
		}
	}
	if (!temp->left && !temp->right) {
		delete temp;
		if (Isleft(help, temp)) {
			help->left = nullptr;
		}
		else {
			help->right = nullptr;
		}
		size--;
		return true;
	}
	//左节点为空右节点有元素
	else if (temp->left == nullptr && temp->right != nullptr) {
		if (Isleft(help, temp)) {
			help->left = temp->right;
		}
		else {
			help->right = temp->right;
		}
		size--;
		delete temp;
		return true;
	}
	else if (temp->left != nullptr && temp->right == nullptr) {
		if (Isleft(help, temp)) {
			help->left = temp->left;
		}
		else {
			help->right = temp->left;
		}
		size--;

		delete temp;
		return true;
	}
	else {
		auto min = findMin(temp->right);
		if (min != temp->right) {
			temp->value = min->value;
			size--;
			delete min;
			return true;
		}
		else {
			min->left = temp->left;
			if (Isleft(help, temp)) {
				help->left = min;
			}
			else {
				help->right = min;
			}
			delete temp;
			size--;
			return true;
		}
	}
}
