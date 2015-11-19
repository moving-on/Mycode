#include<iostream>
#include"listNode.h"
using namespace std;

template<typename T>
class List
{
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;
protected:
	void init();
	void copyNodes(ListNodePosi(T), int);
	void selectionSort(ListNodePosi(T), int);
	void insertionSort(ListNodePosi(T), int);
public:
	//构造函数
	List(){ init(); }
	List(List<T> const& L);
	List(List<T> const& L, Rank r, int n);
	List(ListNodePosi(T) p, int n);
	//析构函数
	~List();
	//接口
	Rank size() const{ return _size; }
	bool empty() const{ return _size <= 0; }
	T& operator[](Rank r) const;
	ListNodePosi(T) first() const{ return header->succ; }
	ListNodePosi(T) last() const{ return trailer->pred; }
	bool valid(ListNodePosi(T) p)
	{
		return p && (trailer != p) && (header != p);
	}
	ListNodePosi(T) find(T const& e)const { return find(e, _size, trailer); }
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) search(T const& e) const{ return search(e, _size, trailer); }
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e);
	T remove(ListNodePosi(T) p);
	int clear();
	void traverse(void(*)(T&));
	template<typename VST>
	void traverse(VST&);
	friend ostream& operator<<(ostream &os, List<T> const& L)
	{
		for (ListNodePosi(T) p = L.first(); p != L.last()->succ;p=p->succ)
		{
			os << p->data << " ";
		}
		return os;
	}
};

template<typename T>
void List<T>::init()
{
	header = new ListNode < T > ;
	trailer = new ListNode < T > ;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}

template<typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p)const
{
	while (n-- > 0)
	{
		p = p->pred;
		if (p->data == e)
			return p;
	}
	return NULL;
}

template<typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) p = new ListNode(e, this, succ);
	succ->pred = p;
	succ = p;
	return p;
}

template<typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
	ListNodePosi(T) p = new ListNode(e, pred, this);
	pred->succ = p;
	pred = p;
	return p;
}

template<typename T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const& e)
{
	++_size;
	return p->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const& e)
{
	++_size;
	return p->insertAsPred(e);
}

template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}

template<typename T>
List<T>::List(List<T> const& L)
{
	copyNodes(L.first(), L._size);
}

template<typename T>
List<T>::List(List<T> const& L, int r, int n)
{
	copyNodes(L[r], n);
}

template<typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}

template<typename T>
T List<T>::remove(ListNodePosi(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template<typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (_size > 0)
		remove(header->succ);
	return oldSize;
}

int main()
{
	List<int> l1;
	for (int i = 0; i < 10; i++)
	{
		l1.insertAsLast(i);
	}
	cout << l1.size() << endl;
	cout << l1 << endl;
	l1.insertAsFirst(10);
	cout << l1 << endl;
	List<int> l2(l1);
	cout << l2 << endl;
	List<int> l3(l1.first(), 5);
	cout << l3 << endl;
	cout<<l1.clear()<<endl;
}
