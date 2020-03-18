#define SETME_H
#ifdef SETME_H
#include<cstdlib>
#include<vector>
#include<queue>
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
	void fix_shortage(std::size_t i);
	bool loose_remove(const T& entry, std::vector<SetMe<T>*>& path, std::vector<int>& index);

	void Show();
private:
	static const std::size_t MINIMUM = 2;
	static const std::size_t MAXIMUM = 2 * MINIMUM;

	//how many entries a root owns
	std::size_t data_count;
	//store the value the set specipies
	T data[MAXIMUM + 1];
	//avoid to calculate how many elements in array data
	std::size_t child_count;
	//pointer to children
	SetMe<T>* subset[MAXIMUM + 2];
	bool loose_insert(const T& entry,std::vector<SetMe<T>*> &vec,std::vector<int>&);
	bool is_leaf() const { return (child_count == 0); }
	void remove_biggest(T& removed_entry);
	void fix_excess(std::size_t i);
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

//谁的孩子节点少了元素对谁操作，谁家孩子少了零件要对家长操作(滑稽）
template<typename T>
void SetMe<T>::fix_shortage(std::size_t i) {
	//subset[i]少一个元素，subset[i-1]可以提供一个元素
	if (subset[i]->data_count == MINIMUM - 1 && subset[i - 1]->data_count > MINIMUM&& i > 0) {
		int j = --subset[i - 1]->data_count;
		T temp = data[i - 1];
		data[i - 1] = subset[i - 1]->data[j];

		//subset[i]元素后移
		for (int m = subset[i]->data_count; m > 0; m--) {
			subset[i]->data[m] = subset[i]->data[m - 1];
		}
		subset[i]->data[0] = temp;
	}
	else if (subset[i]->data_count == MINIMUM - 1 && subset[i + 1]->data_count > MINIMUM&& i < child_count - 1) {
		int& j = subset[i]->data_count;
		subset[i]->data[j++] = data[i];
		data[i] = subset[i + 1]->data[0];

		for (int m = 0; m < subset[i + 1]->data_count - 1; m++) {
			subset[i + 1]->data_count[m] = subset[i + 1]->data_count[m + 1];
		}
		--subset[i + 1]->data_count;
	}
	//进行合并操作,与左边合并,此时i不等0
	//保留左边节点丢弃右边节点,右边节点少一个元素
	else if (i != 0 && subset[i]->data_count == MINIMUM - 1 && subset[i - 1]->data_count == MINIMUM) {
		T temp = data[i - 1];
		//将this的data从i-1开始前移
		for (int j = i; j < data_count; j++) {
			data[j - 1] = data[j];
		}
		--data_count;
		int len1 = subset[i - 1]->data_count;
		int len2 = subset[i]->data_count;
		int childsize1 = subset[i - 1]->child_count;
		int childsize2 = subset[i]->child_count;

		subset[i - 1]->data[len1] = temp;
		//将右边节点的元素值合并的左边节点
		for (int j = 0; j < len2; j++) {
			subset[i - 1]->data[len1 + j + 1] = subset[i]->data[j];
		}
		subset[i]->data_count = 0;
		//将右边节点的孩子信息加到左边节点去
		for (int j = 0; j < childsize2; j++) {
			subset[i - 1]->subset[childsize1 + j] = subset[i]->subset[j];
			subset[i]->subset[j] = nullptr;
		}
		subset[i]->child_count = 0;
		//移动this的subset
		for (int j = i; j < child_count; j++) {
			subset[j] = subset[j + 1];
		}
		subset[i - 1]->child_count += childsize2;
		subset[i - 1]->data_count += (len2+1);
		--child_count;

		//需要释放节点,使用智能指针会更方便
		delete subset[i];
	}
	//节点在最左边，属于左边少一个元素
	else if (i == 0 && subset[i]->data_count == MINIMUM - 1) {
		T first=data[0];
		int j = 0;
		for (j = 0; j < data_count - 1; j++) {
			data[j] = data[j + 1];
		}
		--data_count;
		int len1 = subset[0]->data_count;
		int len2 = subset[1]->data_count;
		int childsize1 = subset[0]->child_count;
		int childsize2 = subset[1]->child_count;

		
		subset[0]->data[len1] = first;
		for (j = 0; j < len2; j++) {
			subset[0]->data[len1 + 1 + j] = subset[1]->data[j];
		}
		for (j = 0; j < childsize2; j++) {
			subset[0]->subset[childsize1 + j] = subset[1]->subset[j];
		}
		for (j = 1; j < child_count-1; j++) {
			subset[j] = subset[j + 1];
		}
		--child_count;

		subset[0]->data_count += (len2 + 1);
		subset[0]->child_count += childsize2;

		delete subset[1];
	}
	else {}
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

		//j表示倒数第一个，即最后一层
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

			left->data_count = MINIMUM;
			right->data_count = MINIMUM;
			if (this->child_count == 0) {
				left->child_count = right->child_count = 0;
			}
			else {
				left->child_count = MINIMUM + 1;
				right->child_count = MINIMUM + 1;

			}
			//保持根节点不变，修改其内容
			this->data[0] = data[MINIMUM];
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
	SetMe<T>* node = new SetMe<T>();
	//将父节点的元素的后移及插入子节点中间的元素到合适的位置
	for (int j = data_count - i; j > 0; j--) {
		data[j] = data[j-1];
	}
	data[i] = subset[i]->data[MINIMUM];
	//将子节点分成两份，node为右边的一部分
	++data_count;


	//这一行直接加指针，典型错误！！
	//node.data = subset[i]->data + MINIMUM;

	//赋予新的值和子节点的信息
	for (int j = 0; j < MINIMUM ; j++) {
		node->data[j] = subset[i]->data[MINIMUM + j+1];
		node->subset[j] = subset[i]->subset[MINIMUM + j];
	}
	if (subset[i]->child_count == 0) {
		subset[i]->data_count = MINIMUM;
		subset[i]->child_count = 0;
		node->child_count = 0;
		node->data_count=MINIMUM;
	}
	else
	{
		node->child_count = MINIMUM + 1;
		node->data_count = MINIMUM;
		subset[i]->data_count = MINIMUM;
		subset[i]->child_count = MINIMUM + 1;
	}

	//把新的右节点node更新，需要把部分subset后移
	for (int j = child_count-1; j > i; j--) {
		subset[j+1] = subset[j];
		
	}
	subset[i+1] = node;
	++child_count;

}
template<typename T>
bool SetMe<T>::loose_insert(const T& entry,std::vector<SetMe<T>*> &vec,std::vector<int>& index)
{
	std::size_t i;
	//获得第一个不小于插入值的元素的索引
	for (i = 0; entry >data[i] && i < data_count; i++) {};
	//应该检查索引i与data的关系，如果i和data_count相等就说明是在末尾
	if (entry == data[i] && i <data_count) { return false; }
	else if (child_count == 0) {
		//没有子节点，递归的出口
		//需要将部分值后移
		for (int j = data_count; j > i; j--) {
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

template<typename T>
void SetMe<T>::Show()
{
	std::queue<SetMe<T>*> que;
	
	que.push(this);
	que.push(nullptr);
	while (!que.empty()) {
		int i = 0;

		//SetMe<T>* temp = que.front();
		auto temp = que.front();
		if (temp == nullptr) {
			std::cout << std::endl;
		}
		else{
			for (i = 0; i < temp->data_count; i++) {
				std::cout << temp->data[i] << std::ends;
			}
			for (i = 0; i < temp->child_count; i++) {
				que.push(temp->subset[i]);
				if (i == temp->child_count-1) {
					que.push(nullptr);
				}
			}
		}
		que.pop();
		//que.front()!= nullptr&&!que.empty()
		//顺序很重要		
		if (!que.empty() && que.front() != nullptr) {
			std::cout << "--|||--";
		}
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