#include<iostream>
#include<cstring>
using namespace std;

template<class T>
class CArray
{
private:
	int size;
	T *ptr;
public:
	CArray(int s = 0);
	CArray(CArray &a);
	~CArray();
	void push_back(const T &v);
	CArray& operator=(const CArray &a);
	int length(){
		return size;
	}
	T& operator[](int i){ return ptr[i]; }
};

template<class T>
CArray<T>::CArray(int s) :size(s)
{
	if (s == 0)
		ptr = NULL;
	else
		ptr = new T[s];
}

template<class T>
CArray<T>::CArray(CArray &a)
{
	if (!a.ptr)
	{
		ptr = NULL;
		size = 0;
		return;
	}
	ptr = new T[a.size];
	memcpy(ptr, a.ptr, sizeof(T)*a.size);
	size = a.size;
}

template<class T>
CArray<T>::~CArray()
{
	if (ptr)
		delete[] ptr;
}

template<class T>
CArray<T>& CArray<T>::operator=(const CArray &a)
{
	if (ptr == a.ptr)
		return *this;
	if (a.ptr == NULL)
	{
		if (ptr)
			delete[] ptr;
		ptr = NULL;
		size = 0;
		return *this;
	}
	if (size < a.size)
	{
		if (ptr)
			delete[] ptr;
		ptr = new T[a.size];
	}
	memcpy(ptr, a.ptr, sizeof(T)*a.size);
	size = a.size;
	return *this;
}

template<class T>
void CArray<T>::push_back(const T& v)
{
	if (ptr)
	{
		T* ptrtmp = new T[size + 1];
		memcpy(ptrtmp, ptr, sizeof(T)*size);
		delete[] ptr;
		ptr = ptrtmp;
	}
	else
		ptr = new T[1];
	ptr[size++] = v;
}

int main()
{
	CArray<double> a;
	for (int i = 0; i < 5; ++i)
		a.push_back(i+2.2);
	for (int i = 0; i < a.length(); ++i)
		cout << a[i] << " ";
	cout << endl;
	CArray<double> b(a);
	b[3] = 4.5;
	CArray<double> c;
	c = b;
	c.push_back(3.9);
	for (int i = 0; i < b.length(); ++i)
		cout << b[i] << " ";
	cout << endl;
	for (int i = 0; i < c.length(); ++i)
		cout << c[i] << " ";
	cout << endl;
}