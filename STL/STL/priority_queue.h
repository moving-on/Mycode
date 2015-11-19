#ifndef __PRIORITY_QUEUE_H
#define __PRIORITY_QUEUE_H
#include<functional>
#include"heap.h"
template<class T, class Sequence = vector<T>, class Compare = less<typename Sequence::value_type>>
class priority_queue
{
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;
	Compare comp;
public:
	priority_queue() :c(){}
	explicit priority_queue(const Compare& x) :c(), comp(x){}
    template<class InputIterator>
	priority_queue(InputIterator first, InputIterator last, const Compare& x) : c(first, last), comp(x)
	{
		mymake_heap(c.begin(), c.end(), comp);
	}
    template<class InputIterator>
	priority_queue(InputIterator first, InputIterator last) : c(first, last)
	{
		mymake_heap(c.begin(), c.end(), comp);
	}
	bool empty()const{ return c.empty(); }
	size_type size()const{ return c.size(); }
	const_reference top()const{ return c.front(); }
	void push(const value_type& x)
	{
		c.push_back(x);
		mypush_heap(c.begin(), c.end(),comp);
	}
	void pop()
	{
		mypop_heap(c.begin(),c.end(),comp);
		c.pop_back();
	}
};

#endif