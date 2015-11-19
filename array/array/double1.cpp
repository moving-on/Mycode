#include<iostream>
using namespace std;

class Complex
{
	double real, imag;
public:
	Complex(double r, double i) :real(r), imag(i){}
	operator double(){ return real; }
};

int main()
{
	Complex c(1.2, 3.4);
	cout << (double)c << endl;
	double n = 2 + c;
	cout << n << endl;
}