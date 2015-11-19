#include"fraction.h"
#include<iostream>
using namespace std;

fraction::fraction()
{
	num = 0;
	denom = 1;
}

fraction::fraction(int n)
{
	num = n;
	denom = 1;
}

fraction::fraction(int n, int d)
{
	num = n;
	denom = d;
}

void fraction::setNum(int n)
{
	num = n;
}

void fraction::setDenom(int d)
{
	denom = d;
}

fraction& fraction::multiply(const fraction& f1)
{
	fraction temp(num*f1.num, denom*f1.denom);
	return temp;
}

fraction& fraction::devide(const fraction& f1)
{
	fraction temp(num*f1.denom, denom*f1.num);
	return temp;
}

fraction& fraction::add(const fraction& f1)
{
	fraction temp(num *f1.denom + f1.num*denom, denom*f1.denom);
	return temp;
}

fraction& fraction::sub(const fraction& f1)
{
	fraction temp(num*f1.denom - f1.num*denom, denom*f1.denom);
	return temp;
}

void fraction::readFrac()
{
	char slash;
	do
	{
		cout << "Enter numerator / denominator:" << endl;
		cin >> num >> slash >> denom;
	} while (slash != '/');
}

void fraction::displayFrac()const
{
	cout << num << '/' << denom;
}

int fraction::getNum()
{
	return num;
}

int fraction::getDenom()
{
	return denom;
}
