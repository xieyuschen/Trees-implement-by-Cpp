#ifndef AVLTREE_H
#define AVLTREE_H
class Avltree
{
public:
	Avltree();
	~Avltree();

private:
	struct Node
	{
		int value;
		int height;
		Node* left;
		Node* right;
	};
};

Avltree::Avltree()
{
}

Avltree::~Avltree()
{
}
#endif // !AVLTREE_H
