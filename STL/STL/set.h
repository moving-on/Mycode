#ifndef __SET_H
#define __SET_H

#include"rbt.h"
#include<functional>
template<class Key,class Compare=less<Key>,class Alloc=alloc>
class set
{
public:
	typedef Key key_type;
	typedef Key value_type;
	typedef Compare key_compare;
	typedef Compare value_compare;
private:
	template<class T>
	struct identity :public std::unary_function<T, T>
	{
		const T& operator()(const T& x)const{ return x; }
	};
	typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
	rep_type t;
public:
	typedef typename rep_type::const_pointer pointer;
	typedef typename rep_type::const_pointer const_pointer;
	typedef typename rep_type::const_reference reference;
	typedef typename rep_type::const_reference const_reference;
	typedef typename rep_type::const_iterator iterator;
	typedef typename rep_type::const_iterator const_iterator;
	typedef typename rep_type::size_type size_type;
	typedef typename rep_type::difference_type difference_type;
	set() :t(Compare){}
	explicit set(const Compare& comp) :t(comp){}
	template<class InputIterator>
	set(InputIterator first, InputIterator last) : t(Compare())
	{
		t.insert_unique(first, last);
	}
	template<class InputIterator>
	set(InputIterator first, InputIterator last, const Compare& comp) : t(comp)
	{
		t.insert_unique(first, last);
	}
	set(const set<Key, Compare, Alloc>& x) :t(x.t){}
	set<Key, Compare, Alloc>& operator=(const set<Key, Compare, Alloc>& x)
	{
		t = x.t;
		return *this;
	}
	key_compare key_comp()const{ return t.key_comp(); }
	value_compare value_comp()const{ return t.key_comp(); }
	iterator begin(){ return t.begin(); }
	iterator end(){ return t.end(); }
	bool empty()const{ return t.empty(); }
	size_type size()const{ return t.size(); }
	size_type max_size()const{ return t.max_size(); }
	typedef __pair<iterator, bool> pair_iterator_bool;
	__pair<iterator, bool> insert(const value_type& x)
	{
		__pair<typename rep_type::iterator,bool> p = t.insert_unique(x);
		return __pair<iterator, bool>(p.first, p.second);
	}
	template<class InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		t.insert_unique(first, last);
	}
	void erase(iterator position)
	{
		typedef typename rep_type::iterator rep_iterator;
		t.erase((rep_iterator&)position);
	}
	size_type erase(const key_type& x)
	{
		return t.erase(x);
	}
	void erase(iterator first, iterator last)
	{
		typedef typename rep_type::iterator rep_iterator;
		t.erase((rep_iterator&)first, (rep_iterator&)last);
	}
	void clear(){ t.clear(); }
	iterator find(const key_type& x)
	{
		return t.find(x);
	}
	iterator lower_bound(const key_type& x)const
	{
		return t.lower_bound(x);
	}
	iterator upper_bound(const key_type& x)const
	{
		return upper_bound(x);
	}
	__pair<iterator, iterator> equal_range(const key_type& x)const
	{
		return t.equal_range(x);
	}
	friend bool operator==(const set&,const set&);
	friend bool operator<(const set&,const set&);
};

template<class Key,class Compare,class Alloc>
inline bool operator==(const set<Key, Compare, Alloc>& x, const set<Key, Compare, Alloc>& y)
{
	return x.t == y.t;
}

template<class Key,class Compare,class Alloc>
inline bool operator<(const set<Key, Compare, Alloc>& x, const set<Key, Compare, Alloc>& y)
{
	return x.t < y.t;
}

#endif