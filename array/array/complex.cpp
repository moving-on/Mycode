#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

class Complex
{
private:
	double real;
	double image;
public:
	Complex(double r=0.0, double i=0.0) :real(r), image(i){}
	Complex operator+(const Complex &c)const;
	Complex operator-(const Complex &c)const;
	Complex operator*(const Complex &c)const;
	Complex operator/ (const Complex &c)const;
	friend ostream& operator<<(ostream& o, const Complex &c);
};

Complex Complex::operator+(const Complex &c)const
{

	return Complex(real + c.real, image + c.image);
}

Complex Complex::operator-(const Complex &c)const
{
	return Complex(real - c.real, image - c.image);
}

Complex Complex::operator*(const Complex &c)const
{
	return Complex(real*c.real - image*c.image, real*c.real + image*c.image);
}

Complex Complex::operator/(const Complex &c)const
{
	return Complex((real*c.real + image*c.image) / (c.real*c.real + c.image*c.image), (real*c.real - image*c.image) / (c.real*c.real + c.image*c.image));
}

ostream& operator<<(ostream& o, const Complex &c)
{
	o << c.real << " " << c.image;
	return o;
}

int main()
{
	double real, image;
	cin >> real >> image;
	Complex c1(real, image);
	cin >> real >> image;
	Complex c2(real, image);
	cout << c1 + c2<<endl;
	cout << c1 - c2<<endl;
	cout << c1*c2 << endl;
	cout << c1 / c2;
	
}