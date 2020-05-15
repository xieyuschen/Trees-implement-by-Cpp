
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
	listMe& operator==(const listMe& org) {
		this(org);
	}
	~listMe() {
		//这个很难办呀
		//那咋办嘛。不办了跑路完事^_^.
		//递归一时爽，清理火葬场
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

//int main() {
//	listMe<int> list(0);
//	for (int i = 1; i < 10; i++) {
//		list.Add(i);
//	}
//	listMe<int> copy=list;
//	list[4] = 1000;
//	copy.Show();
//}