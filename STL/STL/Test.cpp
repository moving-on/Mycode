#include<new>
#include<cstddef>
#include<climits>
#include<iostream>
#include<vector>
#include<exception>
using namespace std;

void outOfMemory()
{
	cerr << "out of memory" << endl;
	abort();
}

class Widget
{
public:
	static void* operator new(size_t size)throw(bad_alloc);
	static new_handler set_new_handler(new_handler p)throw();
private:
	static new_handler currentHandler;
};

class NewHandlerHolder
{
private:
	new_handler handler;
	NewHandlerHolder(const NewHandlerHolder&);
	NewHandlerHolder& operator=(const NewHandlerHolder&);
public:
	NewHandlerHolder(new_handler nh) :handler(nh){}
	~NewHandlerHolder(){ set_new_handler(handler); }
};

new_handler Widget::currentHandler = 0;

void* Widget::operator new(size_t size)throw(bad_alloc)
{
	NewHandlerHolder h(::set_new_handler(currentHandler));
	return ::operator new(size);
}

new_handler Widget::set_new_handler(new_handler p)throw()
{
	new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

int main()
{
	Widget::set_new_handler(outOfMemory);
	Widget* pw1 = new Widget;
	delete pw1;

}

