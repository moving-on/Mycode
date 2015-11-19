#include<iostream>
using namespace std;

double Max(double a, double b)
{
	cout << "Function Max" << endl;
	return 0;
}

template<class T>
T Max(T a, T b)
{
	cout << "Template Max1" << endl;
	return 0;
}

template<class T1,class T2>
T1 Max(T1 a, T2 b)
{
	cout << "Template Max2" << endl;
	return 0;
}

int main()
{
	int i = 4, j = 5;
	Max(1.2, 3.4);
	Max(i, j);
	Max(1.2, 3);
	return 0;
}