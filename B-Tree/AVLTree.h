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
