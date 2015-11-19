#include"Vector.h"

template<typename T>
class Stack :public Vector<T>
{
public:
	void push(T const& e){ insert(size(), e); }
	T pop(){ return remove(size() - 1); }
	T& top(){ return (*this)[size() - 1]; }
};

int main()
{
	Stack<int> s1;
	for (int i = 0; i < 10; i++)
		s1.push(i);
	cout << s1;
	cout << s1.top() << endl;
	cout << s1.pop() << endl;
	cout << s1;
}