#define SETME_H
#ifdef SETME_H
#include<cstdlib>
#include<vector>
//so why the MAXIMUM equals to twice of MINIMUM? Can other value works well?

template<typename T>
class SetMe
{
public:
	typedef T value_type;
	SetMe();
	SetMe(const SetMe& source);
	SetMe operator=(const SetMe& source);
	bool insert(const T& source);
	std::size_t erase(const T& target);
	std::size_t count(const T& target) const;
	bool empty() const { return (data_count == 0); }
	//~SetMe();
	bool loose_remove(const T& entry, std::vector<SetMe<T>*>& path, std::vector<int>& index);

private:
	static const std::size_t MINIMUM = 200;
	static const std::size_t MAXIMUM = 2 * MINIMUM;

	//how many entries a root owns
	std::size_t data_count;
	//store the value the set specipies
	T data[MAXIMUM + 1];
	//avoid to calculate how many elements in array data
	std::size_t child_count;
	//pointer to children
	SetMe<T>* subset[MAXIMUM + 2];
	int* p;
	bool loose_insert(const T& entry,std::vector<SetMe<T>*> &vec,std::vector<int>&);
	bool is_leaf() const { return (child_count == 0); }
	void remove_biggest(T& removed_entry);
	void fix_excess(std::size_t i);
	void fix_shortage(std::size_t i);
};
template<typename T>
SetMe<T>::SetMe() :child_count(0), data_count(0) {};

//对this节点进行操作，去掉this的节点或者递归调用别的
template<typename T>
bool SetMe<T>::loose_remove(const T& target,std::vector<SetMe<T>*>& path,std::vector<int>& index) {
	int i = 0;
	for (i=0; i<data_count && target>data[i]; i++) {};
	//当找到这个元素，就可以去掉元素了
	
	//这个节点无子节点且未找到此元素
	
	if ((data[i]!=target||i==data_count) && child_count == 0) {
		return false;
	}
	//有子节点，在当前节点没有找到
	else if((data[i] != target || i == data_count)&&child_count!=0) {
		return subset[i]->loose_remove(target, path, index);
	}
	//找到了元素
	else if (i < data_count && data[i] == target) {
		//集体前移,从被删除的元素往前shift
		for (int j =i; j<data_count-1; j--) {
			data[j] = data[j + 1];
		}
		--data_count;
		path.push_back(this);
		index.push_back(i);
		return true;
	}
}

template<typename T>
bool SetMe<T>::insert(const T& entry) {
	std::vector<SetMe<T>*> path;
	std::vector<int> index;
	//将头部信息加入
	path.push_back(this);
	index.push_back(0);

	//没有成功插入loose_insert 返回false
	if (!loose_insert(entry,path,index)) { return false; }
	//处理成功插入的情况
	else{
		//首先检查是否超标
		std::size_t len = path.size();
		//直接循环检查调用，将到顶的情况单独留出来
		//len-j 表示当前节点，如果出问题 len-j-1表示其父节点，对父节点处理
		int j = 1;
		for (j; path[len -j]->data_count == MAXIMUM + 1 && j < len; j++) {
			SetMe<T>* temp= path[len-j-1];
			temp->fix_excess(index[len-j]);
		}
		//对顶部处理：
		if (j == len&&data_count==MAXIMUM+1) {
			//如何使用智能指针？
			SetMe<T>* left=new SetMe<T>();
			SetMe<T>* right = new SetMe<T>();

			//编辑新增加的两个节点
			for (int i = 0; i < MINIMUM;i++) {
				left->data[i] = this->data[i];
				right->data[i] = this->data[MINIMUM + 1 + i];
				
				left->subset[i] = this->subset[i];
				right->subset[i] = this->subset[MINIMUM + 1 + i];
			}
			left->subset[MINIMUM] = this->subset[MINIMUM];
			right->subset[MINIMUM] = this->subset[MAXIMUM+1];
			
			//保持根节点不变，修改其内容
			this->child_count = 2;
			this->data_count = 1;
			this->subset[0] = left;
			this->subset[1] = right;
		}
		return true;
	}
}
//节点的subset[i] 是有MAXIMUM＋1 个元素的
//谁的子节点超标调用谁
template<typename T>
void SetMe<T>::fix_excess(std::size_t i) {
	SetMe<T> node;
	//将父节点的元素的后移及插入子节点中间的元素到合适的位置
	for (int j = data_count - i; j > 0; j--) {
		data[j] = data[j-1];
	}
	data[i] = subset[i]->data[MINIMUM];
	
	//将子节点分成两份，node为右边的一部分
	node.child_count = MINIMUM+1;
	node.data_count = MINIMUM;
	//这一行直接加指针，典型错误！！
	//node.data = subset[i]->data + MINIMUM;

	//赋予新的值和子节点的信息
	for (int j = 0; j < MINIMUM + 1; j++) {
		node.data[j] = subset[i]->data[MINIMUM + j];
		node.subset[j] = subset[i]->subset[MINIMUM + j];
	}

	subset[i]->data_count = MINIMUM;
	subset[i]->child_count = MINIMUM + 1;
}
template<typename T>
bool SetMe<T>::loose_insert(const T& entry,std::vector<SetMe<T>*> &vec,std::vector<int>& index)
{
	std::size_t i;
	//获得第一个不小于插入值的元素的索引
	for (i = 0; entry > data[i] && i < data_count; i++) {};
	//应该检查索引i与data的关系，如果i和data_count相等就说明是在末尾
	if (entry == data[i] && i < data_count) { return false; }
	else if (child_count == 0) {
		//没有子节点，递归的出口
		//需要将部分值后移
		for (int j = data_count - i; j > i; j--) {
			data[j] = data[j - 1];
		}
		data[i] = entry;
		++data_count;
		return true;
	}
	else {
		vec.push_back(subset[i]);
		index.push_back(i);
		return subset[i]->loose_insert(entry,vec,index);
	}

}

#endif // !SETME_H

//template<typename T>
//class SetMe
//{
//public:
//	typedef T value_type;
//	SetMe();
//	SetMe(const SetMe& source);
//	SetMe operator=(const SetMe& source);
//	bool insert(const T& source);
//	std::size_t erase(const T& target);
//	std::size_t count(const T& target) const;
//	bool empty() cosnt { return (data_count == 0); }
//	~SetMe();
//
//private:
//	static const std::size_t MINIMUM = 200;
//	static const std::size_t MAXIMUM = 2 * MINIMUM;
//
//	//how many entries a root owns
//	std::size_t data_count;
//	//store the value the set specipies
//	T data[MAXIMUM + 1];
//	//avoid to calculate how many elements in array data
//	std::size_t child_count;
//	//pointer to children
//	SetMe* subset[MAXIMUM + 2];
//
//	bool is_leaf() const { return (child_count == 0); }
//	bool loose_insert(const T& entry);
//	bool loose_remove(const T& entry);
//	void remove_biggest(T& removed_entry);
//	void fix_excess(std::size_t i);
//	void fix_shortage(std::size_t i);
//};