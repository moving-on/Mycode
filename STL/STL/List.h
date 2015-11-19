#include"iterator_traits.h"
template<class T>
struct __list_node
{
	T data;
	typedef void* void_pointer;
	void_pointer prev;
	void_pointer next;
};

template<class T,class Ref,class Ptr>
struct __list_iterator
{
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, Ref, Ptr> self;
	typedef bidirectional_iterator_tag_h iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	link_type node;

	__list_iterator(link_type x) :node(x){}
	__list_iterator(){}
	__list_iterator(const iterator& x) :node(x.node){}

	bool operator==(const self& x)const{ return node == x.node; }
	bool operator!=(const self& x)const{ return node != x.node; }
	reference operator*()const{ return (*node).data; }

	pointer operator->()const{ return &(operator*()); }
	self& operator++()
	{
		node = (link_type)((*node).next);
		return *this;
	}
	self operator++(int)
	{
		self tmp = *this;
		++*this;
		return tmp;
	}
	self operator--()
	{
		node = (link_type)((*node).prev);
		return *this;
	}
	self operator--(int)
	{
		node tmp = *this;
		--*this;
		return tmp;
	}

};


template<class T,class Alloc=alloc>
class list
{
protected:
	typedef void* void_pointer;
	typedef __list_node<T> list_node;
	typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef list_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
public:
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
protected:
	link_type node;
protected:
	link_type get_node(){ return list_node_allocator::allocate(); }
	void put_node(link_type p){ list_node_allocator::deallocate(p); }
	link_type create_node(const T& x)
	{
		link_type p = get_node();
		try
		{
			construct(&p->data, x);
		}
		catch (...)
		{
			put_node(p);
		}
		return p;
	}
	void destroy_node(link_type p)
	{
		destroy(&p->data);
		put_node(p);
	}
protected:
	void empty_uninitialize()
	{
		node = get_node();
		node->next = node;
		node->prev = node;
		construct(&node->data, T());
	}

	void fill_initialize(size_type n, const T& value)
	{
		empty_uninitialize();
		try
		{
			insert(begin(), n, value);
		}
		catch (...)
		{
			clear();
			put_node(node);
		}
	}
public:
	list(){ empty_uninitialize(); }
	list(size_type n, const T& value){ fill_initialize(n, value); }
	explicit list(size_type n){ fill_initialize(n, T()); }
	iterator begin(){ return (link_type)((*node).next); }
	const_iterator begin()const{ return (link_type)((*node).next); }
	iterator end(){ return node; }
	const_iterator end()const{ return node; }
	void clear();
	bool empty(){ return node->next = node; }
	size_type size(){ return mydistance(begin(), end()); }
	const_reference front()const { return *begin(); }
	reference front(){ return *begin(); }
	reference back(){ return *(--end()); }
	const_reference back()const{ return *(--end()); }
	void swap(list<T, Alloc>&x){ ::swap(node, x.node); }
	iterator insert(iterator position, const T& x)
	{
		link_type tmp = create_node(x);
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(link_type(position.node->prev))->next = tmp;
		position.node->prev = tmp;
		return tmp;
	}
	iterator insert(iterator position)
	{
		return insert(position, T());
	}
	void insert(iterator position, size_type n, const T& x);
	template<class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last);
	void insert(iterator position, const T* first, const T* last);
	void transfer(iterator position, iterator first, iterator last);
	void splice(iterator position, list& x);
	void splice(iterator position, list&, iterator i);
	void splice(iterator position, iterator first, iterator last);
	void remove(const T& value);
public:
	void push_back(const T& x)
	{
		insert(end(), x);
	}
	void push_front(const T& x)
	{ 
		insert(begin(), x);
	}
	iterator erase(iterator position)
	{
		link_type next_node = link_type(position.node->next);
		link_type prev_node = link_type(position.node->prev);
		prev_node->next = next_node;
		next_node->prev = prev_node;
		destroy_node(position.node);
		return iterator(next_node);
	}
	iterator erase(iterator first, iterator last)
	{
		while (first != last)
			erase(first++);
		return last;
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		iterator tmp = end();
		erase(--tmp);
	}
public:
	~list()
	{
		clear();
		put_node(node);
	}
	list<T, Alloc>& operator=(const list<T, Alloc>& x);
};

template<class T, class Alloc>
void list<T,Alloc>::insert(iterator position, size_type n, const T& x)
{
	for (; n > 0; --n)
		insert(position, x);
}

template<class T,class Alloc>
void list<T, Alloc>::clear()
{
	link_type cur = (link_type)node->next;
	while (cur != node)
	{
		link_type tmp = cur;
		cur = (link_type)tmp->next;
		destroy_node(tmp);
	}
	node->next = node;
	node->prev = node;
}

template<class T, class Alloc>
template<class InputIterator>
void list<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
{
	for (; first != last; ++first)
		insert(position, *first);
}

template<class T, class Alloc>
void list<T, Alloc>::insert(iterator position, const T* first, const T* last)
{
	for (; first != last; ++first)
		insert(position, *first);
}

template<class T, class Alloc>
list<T, Alloc>& list<T, Alloc>::operator=(const list<T, Alloc>& x)
{
	if (this != &x)
	{
		iterator first1 = begin();
		iterator last1 = end();
		const_iterator first2 = x.begin();
		const_iterator last2 = x.end();
		while (first1 != last1&&first2 != last2)
			*first1++ = *first2++;
		if (first2 == last2)
			erase(first1, last1);
		else
			insert(last1, first2, last2);
	}
	return *this;
}

template<class T,class Alloc>
void list<T, Alloc>::transfer(iterator position, iterator first, iterator last)
{
	if (position != last)
	{
		(*(link_type((*last.node).prev))).next = position.node;
		(*(link_type((*first.node).prev))).next = last.node;
		(*(link_type((*position.node).prev))).next = first.node;
		link_type tmp = link_type((*position.node).prev);
		(*position.node).prev = (*last.node).prev;
		(*last.node).prev = (*first.node).prev;
		(*first.node).prev = tmp;
	}
}

template<class T,class Alloc>
void list<T, Alloc>::splice(iterator position, list& x)
{
	if (!x.empty())
		transfer(position, x.begin(), x.end());
}

template<class T,class Alloc>
void list<T, Alloc>::splice(iterator position, list&, iterator i)
{
	iterator j = i;
	++j;
	if (position == i || position == j)
		return;
	transfer(position, i, j);
}

template<class T,class Alloc>
void list<T, Alloc>::splice(iterator position, iterator first, iterator last)
{
	if (first != last)
		transfer(position, first, last);
}

template<class T,class Alloc>
void list<T, Alloc>::remove(const T& x)
{
	iterator first = begin();
	iterator last = end();
	while (first != last)
	{
		iterator next = first;
		++next;
		if (*first == value)
			erase(fisrt);
		first = next;
	}
} 