# 资源控制：
关于构造函数，拷贝移动构造函数和析构函数的使用方法：
注意指针对象，是否需要动态分配？

## 内置类型：
```cpp

/*
这里使用了动态分配内置类型成员，也就是说动态分配int类型变量，那么分配的时候发生了什么呢？
在创建对象的时候我需要调用这个类的构造函数，但这里是内置类型所以不需要有构造函数，编译器自动帮助我们创建。使用动态分配只是把内存分配在堆上，而不是栈上
*/
class line{
public:
  line(int* ptr=nullptr){
    p=new int;
    p=ptr;
  }
  ~line(){
    delete p;
  }
  line(const line& org){
    p=new int;
    *p=*org.p;
  }
private:
  int* p;
}
/*
*/
```


## 自定义类型
```cpp
#include<iostream>
#include<time.h>
using namespace std;
template<typename T>
class listMe {
public:
	listMe(T val=0, listMe* c=nullptr):data(val){
		if (c != nullptr) {
			child = new listMe(0,nullptr);
			child = c;
		}
		else {
			child = c;
		}
	};
	listMe(const listMe& org) {
		if (org.child != nullptr) {
			child = new listMe();
			*child = *org.child;
		}
		else
		{
			child = nullptr;
		}
		data = org.data;
	}
	~listMe() {

	}
	T& operator[](size_t i) {
		T temp=data;
		listMe* p = this;
		for (size_t j = 0; j < i; j++) {
			if (p->child == nullptr) {
				cout << "Out of range!" << endl;
				break;
			}
			else
			{
				temp = p->data;
				p = p->child;
			}
		}
		return temp;
	}
	void Show() {
		cout << data << ends;
		if(child != nullptr) {
			child->Show();
		}
	}
	void Add(T val) {
		if (child == nullptr) {
			listMe* p = new listMe(val);
			child = p;
		}
		else
		{
			child->Add(val);
		}
	}
	void swap(listMe& n1, listMe& n2) {
		std::swap(n1.data, n2.data);
		std::swap(n1.child, n2.child);
	}
private:
	listMe<T>* child;
	T data;
};

int main() {
  //main函数中，只会调用两个析构函数，在Add方法中加上去的都不需要调用析构函数。
  //对于动态分配的自定义类类型，在delete指针的时候，会调用对应的析构函数
  //所以说，递归一时爽，析构火葬场。
	listMe<int> list(0);
	for (int i = 1; i < 10; i++) {
		list.Add(i);
	}
	listMe<int> copy(list);
	//list.Show();
}
```

# B-Tree
## insert方法的一些记录：

 <img src="./Images/1.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/2.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/3.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/4.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/5.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="./Images/6.jpg" width = "300" height = "400" alt="图片名称" align=center />

## remove
记录remove的一些思路：  
--    
 <img src="Images/remove1.jpg" width = "300" height = "400" alt="图片名称" align=center />
 <img src="Images/remove2.jpg" width = "300" height = "400" alt="图片名称" align=center /> 

<img src="Images/remove3.jpeg" width = "300" height = "400" alt="图片名称" align=center />  



## 如何测试：
----
测试的时候各种问题都会出现，记录一些测试心得在这里。  
----
 <img src="Images/remove4.jpeg" width = "300" height = "400" alt="图片名称" align=center /> 
  <img src="Images/remove5.jpeg" width = "300" height = "400" alt="图片名称" align=center />  



## 解决Show函数的换行问题
对于一个MAXIMUM=4的B-Tree来说Show函数输出以下内容并不是很友好，因为不能明显的表现出树各节点的关系。
```
27 54
9 18 --|||--36 45 --|||--63 72 81 90
3 6 --|||--12 15 --|||--21 24
30 33 --|||--39 42 --|||--48 51
48 51 --|||--57 60 --|||--66 69 --|||--84 87 --|||--93 96
1 2 --|||--4 5 --|||--7 8
10 11 --|||--13 14 --|||--16 17
16 17 --|||--19 20 --|||--22 23
22 23 --|||--28 29 --|||--31 32
31 32 --|||--37 38 --|||--40 41
40 41 --|||--46 47 --|||--49 50
40 41 --|||--46 47 --|||--49 50
49 50 --|||--55 56 --|||--58 59
58 59 --|||--64 65 --|||--67 68
67 68 --|||--82 83 --|||--85 86
85 86 --|||--91 92 --|||--94 95 99
```

## fix_shortage()中极其愚蠢的错误
这个错误是这样的，我要释放一个节点，然后把之后的节点前移。然后我先前移覆盖了要释放的位置，再把对应位置的内容释放掉（但其实这个内容已经被覆盖了），我释放掉了不该释放的内容。
```cpp
for (j = 1; j < child_count-1; j++) {
    subset[j] = subset[j + 1];
}
delete subset[1];
```
所以先删除指针再进行移位覆盖即可。

## size_t是无符号类型！循环的时候不要用size_t

# Binary Search Tree
## 3.27重写概述：
- 二叉搜索树我之前是写过的，今天又写了一遍，我写的代码是真的丑啊啊啊啊！！  
- 主要是Remove函数的条件筛选，我觉得我犯的错误是没有认真思考如何设置可以减少条件检查。把之前自己写的（基本上算是照着教材抄来）代码放进来比较一下，命名为`lastBSTree`...   
- 嗯。。demo也有很大的问题，我要吐了，明天对比一下教材给的代码好好的学习一下。自己重写一遍什么神仙问题都能检查出来。写错了就是写错了，不可能蒙混过关的。。。

## 学习DemoBstree
这个是真的Demo(滑稽,作者所提供的源代码。[源码网页在这里!](http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/).  
好好看看别人是怎么设计的吧。。代码真的写得稀烂。 :)

### 二叉树的节点设置
#### 二叉树的节点写在private里面去
我设计的时候把Node类作为独立的一个类进行设计了，但是这样没有起到良好的封装性，Node是不需要暴漏给用户的，我不需要让用户知道有这个东西。所以直接在类的私有变量中声明节点信息就很棒，作为类的类型成员。  
- 如果这个类型成员是public的话，我们还可以访问它并定义一个变量：  
```cpp
//前提是在类中声明的class BinaryNode 是public的
BinarySearchTree<int>::BinaryNode node;
```

#### 二叉树节点的构造函数：
以下两个构造函数，第二个右值引用是为了更好的绑定右值。
```cpp
BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt)
```

- 没有写拷贝构造函数，说明使用默认的拷贝构造函数。
- 没有需要析构函数专门析构的资源

### BinarySearchTree 的构造函数们
- 构造函数：直接把root赋值为nullptr表示空就完事了。
- 拷贝构造函数：具有值行为的类，动态分配每个节点都要分配新内存。记得写个打工函数。
- 移动构造函数，把根节点交了就行了(你把你根节点给我交了！).
- 拷贝赋值运算符：  
这个代码写得太好了，放到这里！！  
1. 创建一个局部变量，注意这里的=其实是初始化的方式，并不是进行拷贝
2. 将创建的这个值与copy进行交换，依此交换对应的资源，因为没有特殊的交换需求，所以没有给Node定义自己版本的swap函数。
3. 交换后返回*this就可以了
```cpp
BinarySearchTree& operator=(const BinarySearchTree& rhs)
{
	BinarySearchTree copy = rhs;
	std::swap(*this, copy);
	return *this;
}
```
- 移动赋值运算符：
注意移动赋值运算符和拷贝赋值运算符swap的对象是不太一样的，因为移动之后右值引用的值是不应该被期待的，所以我直接swap rhs的根元素就可以了。
```cpp
BinarySearchTree& operator=(BinarySearchTree&& rhs)
{
	std::swap(root, rhs.root);
	return *this;
}
```
- 析构函数：  
递归大法好，首先明确节点都是动态分配的，所以在析构的时候要进行释放。所以这就好写了。然后记得写打工函数！！！因为这些打工函数还可以在别的地方被重用，写在析构函数里面一大坨然后再别的地方要用

### BinarySearchTree 的insert函数：
首先insert直接调用打工函数，打工函数通过递归来完成插入结点的使命：  
- 这里有个很nb的地方，在我写代码的时候认为这一点是不能直接实现的所以**写了很多代码来弥补我设计思路上的漏洞**。这个思路漏洞很有意思，没有想到也正常，放到这里来专门分析一下：  
在查找到需要在哪里插入节点的时候，首先我找到了该插入位置的父节点，那么怎么样插入同时进行修改父节点的指针。
因为我使用非递归的做法，那么我首先找到插入的父节点，然后比较大小判断应该插入到左/右节点。然后动态分配修改指针就可以了。那么递归怎么办，返回两个值？
- 这里就使用了指针的引用，因为指针类型也是一种变量，所以也可以用引用。
```cpp

void insert(T&& x, BinaryNode*& t)
{
	if (t == nullptr)
		t = new BinaryNode{ std::move(x), nullptr, nullptr };
	else if (x < t->element)
		insert(std::move(x), t->left);
	else if (t->element < x)
		insert(std::move(x), t->right);
	else
		;  // Duplicate; do nothing
}
```

### Remove函数：
嗯这代码写的真的是赏心悦目，必须放上来。我写的真的是太丑陋了！  
思路很简单，嗯是这样的。
```cpp
void remove(const Comparable& x, BinaryNode*& t)
{
	if (t == nullptr)
		return;   // Item not found; do nothing
	if (x < t->element)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	
	//t->element==x 为真
	else if (t->left != nullptr && t->right != nullptr) // Two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{
		BinaryNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}
```


### 总结概述：
在树结构里，递归是一个非常重要的思想，啥东西不要光想着用循环。自己写的代码过于垃圾一堆if-else的主要问题就是妄图通过循环解决一个每次循环都高度相似的问题，这种情况是典型的递归解法更优更好。这次是个很典型的反面教材。  
想要使用递归的思路，就多使用打工函数，不要把东西一股脑全部写到一个函数里面去。

#### 一些简单函数的函数声明：
这里主要复习一下const声明符修饰函数的使用方法：  
- 在普通的非 const成员函数中，this的类型是一个指向类类型的 const指针。可以改变this所指向的值，但不能改变 this所保存的地址。  
- 在 const成员函数中，this的类型是一个指向 const类类型对象的 const指针。既不能改变 this所指向的对象，也不能改变 this所保存的地址。
这里挑了几个函数声明来展示：
```cpp
bool isEmpty() const
void printTree(ostream& out = cout) const
const Comparable& findMin() const
```

#### 递归的思想：
全部要使用递归，使用递归异常简单。。设计思路的问题。

# AVL Tree
AVL树的大部分内容和二叉搜索树是一样的，所以说这里写的时候正好复习一下今天的学习成果，然后再加上新的检验深度的函数就可以了。  
所以说问题就来了，如何检测这棵树是否均衡？  
- 如何存储高度信息：  
这一段话，怎么讲呢，我看的不太明白。作为留存问题等AVL树实现完了我再来解决。

![](Images/AVL1.png)