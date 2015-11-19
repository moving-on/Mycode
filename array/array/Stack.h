#ifndef STACK_H
#define STACK_H

#include<deque>
#include<exception>

template<class T,class Container=deque<T>>
class Stack
{
public:
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type size_type;
private:
	Container c;
public:
	class ReadEmptyStack :public exception
	{
	public:
		virtual const char* what()const throw()
		{
			return "read empty stack";
		}
	};
	size_type size()const{ return c.size(); }
	bool empty()const{ return c.empty(); }
	void push(const T& elem)
	{
		c.push_back(elem);
	}
	void pop()
	{
		if (c.empty())
			throw ReadEmptyStack();
		c.pop_back();
	}
	T& top()
	{
		if (c.empty())
			throw ReadEmptyStack();
		return c.back();
	}
};

#endif