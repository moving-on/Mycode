#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include<vector>
#include<algorithm>
template<class T,class Container=vector<T>,class Compare=less<typename Container::value_type>>
class Priority_queue
{
public:
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type size_type;
private:
	Container c;
	Compare op;
public:
	explicit Priority_queue(const Compare& cmp = Compare(), const Container& cont = Container())
		:op(cmp), c(cont)
	{
		make_heap(c.begin(), c.end(), op);
	}
	void push(const value_type& elem)
	{
		c.push_back(elem);
		push_heap(c.begin(), c.end(), op);
	}
	void pop()
	{
		pop_heap(c.begin(), c.end(), op);
		c.pop_back();
	}
	bool empty()
	{
		return c.empty();
	}
	size_type size()
	{
		return c.size();
	}
	const value_type& top()const
	{
		return c.front();
	}
};

#endif