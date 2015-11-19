#include<iostream>
#include<string>
using namespace std;

typedef int Rank;
const int DEFAULT_CAPACITY = 3;

template <typename T>
class Vector
{
protected :
	Rank _size;
	int  _capacity;
	T *_elem;
protected:
	void copyFrom(T const *A, Rank lo, Rank hi);
	void expand();
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);
	void swap(T&, T&);
	Rank max(Rank lo, Rank hi);
	void selectionSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);
	void mergeSort(Rank lo, Rank hi);
	void quickSort(Rank lo, Rank hi);
public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const *A, Rank lo, Rank hi)
	{
		copyFrom(A, lo, hi);
	}
	Vector(T const *A, Rank n)
	{
		copyFrom(A, 0, n);
	}
	Vector(Vector<T> const& V, Rank lo, Rank hi)
	{
		copyFrom(V._elem, lo, hi);
	}
	Vector(Vector<T> const& V)
	{
		copyFrom(V._elemm, 0, V._size);
	}

	//析构函数
	~Vector()
	{
		delete[] _elem;
	}

public:
	Rank size() const{ return _size; }
	int capacity() const{ return _capacity; }
	bool empty() const{ return !_size; }
	int disorder() const;
	Rank find(T const& e) const{ return find(e, 0, _size); }
	Rank find(T const& e, Rank lo, Rank hi) const;
	Rank search(T const& e) const{ return (0 >= _size) ? -1 : search(e, 0, _size); }
	Rank search(T const& e, Rank lo, Rank hi) const;
	T& operator[](Rank r) const{ return _elem[r]; }
	Vector<T>& operator=(Vector<T> const&);
	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);
	Rank insert(T const& e){ insert(_size, r); }
	void traverse(void(*visit)(T&));
	template<typename VST>
	void traverse(VST& visit);
	void sort(Rank lo, Rank hi, char s);
	friend ostream& operator<<(ostream& o, Vector<T>& V)
	{
		for (int i = 0; i < V.size(); i++)
		{
			o << V[i]<<" ";
		}
		o << endl;
		return o;
	}

};



template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem)
		delete[] _elem;
	copyFrom(V._elem, 0, V._size);
	return *this;
}

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity<<=1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)
		return;
	if (_size << 2 > _capacity)
		return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	while ((lo < hi--) && _elem[hi] != e);
	return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;
	return r;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)
		return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template<typename T>
void Vector<T>::traverse(void(*visit)(T& e))
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template<typename T>
struct Increase
{
	virtual void operator()(T& e)
	{
		e++;
	}
};

template<typename T>
void increase(Vector<T> &V)
{
	V.traverse(Increase<T>());
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi, char s)
{
	switch (s)
	{
	case 'b':
		bubbleSort(lo, hi);
		break;
	case 'm':
		mergeSort(lo, hi);
		break;
	default:
		cout << "can't find the sort method!" << endl;
		break;
	}
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (!bubble(lo, hi--));
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
	bool sorted = true;
	while (++lo < hi)
	{
		if (_elem[lo - 1] > _elem[lo])
		{
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

template<typename T>
void Vector<T>::swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2)
		return;
	int mi = (lo + hi) >>1 ;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;
	int lb = mi - lo;
	T* B = new T[lb];
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mi;
	T* C = _elem + mi;
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
	{
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
			A[i++] = B[j++];
		if ((k < lc) && ((!j < lb) || (C[k] < B[j])))
			A[i++] = C[k++];
	}
	delete[] B;
}

template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{
	if (lo < hi)
	{
		Rank mi = (lo + hi) / 2;
		if (_elem[mi]>e)
			search(e, lo, mi - 1);
		else if (_elem[mi] < e)
			search(e, mi + 1, hi);
		else
			return lo;
	}
}

