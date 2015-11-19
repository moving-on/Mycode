#include<string>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<new>
using namespace std;


namespace my
{
	template <class T>
	class allocator
	{
	public:
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T value_type;

		template<class U>
		struct rebind
		{
			typedef allocator<U> other;
		};

		pointer address(reference vaule)
		{
			return &value;
		}

		const_pointer address(const_reference value)const
		{
			return &value;
		}

		allocator()throw(){}
		allocator(const allocator<T>&)throw(){}
		template<class U>
		allocator(const allocator<U>&)throw(){}
		~allocator()throw(){}
		pointer allocate(size_type size)
		{
			return (pointer)(::operator new(size*sizeof(T)));
		}

		void construct(pointer p, const T& value)
		{
			new ((void*)p) T(value);
		}

		void destroy(pointer p)
		{
			p->~T();
		}

		void deallocate(pointer p, size_type num)
		{
			::operator delete((void*)p);
		}
	};
}

namespace my
{
	template<class T, class Allocator = allocator<T>>
	class Vector
	{
	public:
		struct iterator
		{
			typedef T* pointer;
			typedef T& reference;
			typedef T value_type;
			typedef int difference;
			pointer p;
			iterator(pointer _p) :p(_p){}
			iterator() :p(NULL){}
			T& operator*(){ return *p; }
			bool operator!=(iterator& iter)
			{
				return p != iter.p;
			}
			const pointer& operator++()
			{
				++p;
				return p;
			}
		};
	private:
		T* elems;
		Allocator alloc;
		int  numElems;
		int  sizeElems;
	public:
		typedef unsigned int size_type;
		explicit Vector(const Allocator& = Allocator());
		explicit Vector(size_type num, const T& val = T(), const Allocator& = Allocator());
		explicit Vector(const Vector<T, Allocator>&);
		explicit Vector(const iterator& beg, const iterator& end,const Allocator& =Allocator());
		~Vector();
		T& operator[](int i){ return elems[i]; }
	public:
		iterator begin(){ return iterator(elems); }
		iterator end(){ return iterator(elems + numElems); }

	};

	template<class T, class Allocator = allocator<T>>
	Vector<T, Allocator>::Vector(size_type nums, const T& val, const Allocator& a) :alloc(a)
	{
		sizeElems = numElems = nums;
		elems = alloc.allocate(nums);
		uninitialized_fill_n(elems, nums, val);
	}

	template<class T,class Allocator>
	Vector<T, Allocator>::~Vector()
	{
		for (size_type i = 0; i < numElems; ++i)
			alloc.destroy(&elems[i]);
		alloc.deallocate(elems, sizeElems);
	}

	template<class T,class Allocator>
	Vector<T, Allocator>::Vector(const Vector<T, Allocator>& v)
	{
		numElems = sizeElems = v.sizeElems;
		alloc = v.alloc;
		elems = alloc.allocate(numElems);
		for (int i = 0; i < numElems; i++)
		{
			alloc.construct(&elems[i], v.elems[i]);
		}
	}

	template<class T,class Allocator>
	Vector<T, Allocator>::Vector(const iterator& beg, const iterator& end, const Allocator& a)
	{
		numElems = sizeElems = distance<T,Allocator>(beg, end);
		alloc = a;
		elems = alloc.allocate(numElems);
		iterator pos = beg;
		for (int i = 0; i < numElems;i++,++pos)
			alloc.construct(elems+i, *pos);
	}
}


namespace my
{
	template<class T, class Allocator>
	typename Vector<T, Allocator>::iterator::difference distance(typename const Vector<T, Allocator>::iterator& iter1, typename const Vector<T, Allocator>::iterator& iter2)
	{
		int diff = 0;
		typename Vector<T, Allocator>::iterator pos = iter1;
		while (pos.p != iter2.p)
		{
			++ diff;
			++pos.p;
		}
		return diff;
	}
}

int main()
{
	my::Vector<int> v(10, 2);
	for (int i = 0; i < 10; i++)
		cout << v[i] << " ";
	cout << endl;
	my::Vector<int> v2(v);
	v2[2] = 5;
	v2[4] = 6;
	my::Vector<int>::iterator pos;
	for (pos = v2.begin(); pos != v2.end(); ++pos)
	{
		cout << *pos << " ";
	}
	cout << endl;
	my::Vector<int> v3(v2.begin(), v2.end());
	for (pos = v3.begin(); pos != v3.end(); pos++)
		cout << *pos << " ";

}