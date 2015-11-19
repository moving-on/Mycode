#include<iostream>
using namespace std;

class A
{
private:
	static int SA;
public:
	void Print()
	{
		cout << SA << endl;
	}
};

int A::SA = 99;
class B :public A
{

};

int main()
{
	A a;
	B b;
	a.Print();
	b.SA = 9;
}