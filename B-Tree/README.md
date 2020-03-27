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
- 主要是Remove函数的条件筛选，我觉得我犯的错误是没有认真思考如何设置可以减少条件检查。把之前自己写的（基本上算是照着教材抄来）代码放进来比较一下，命名为`DemoBSTree`...   
- 嗯。。demo也有很大的问题，我要吐了，明天对比一下教材给的代码好好的学习一下。自己重写一遍什么神仙问题都能检查出来。写错了就是写错了，不可能蒙混过关的。。。