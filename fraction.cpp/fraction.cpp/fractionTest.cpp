#include<iostream>
#include"fraction.h"
using namespace std;

int main()
{
	fraction f1, f2, f3;
	cout << "Enter 1st fraction:" << endl;
	f1.readFrac();
	cout << "Enter 2st fraction:" << endl;
	f2.readFrac();

	f3 = f1.multiply(f2);
	f1.displayFrac();
	cout << "*";
	f2.displayFrac();
	cout << "=";
	f3.displayFrac();
	cout << endl;

	f3 = f1.devide(f2);
	f1.displayFrac();
	cout << "/";
	f2.displayFrac();
	cout << "=";
	f3.displayFrac();
	cout << endl;

	f3 = f1.add(f2);
	f1.displayFrac();
	cout << "+";
	f2.displayFrac();
	cout << "=";
	f3.displayFrac();
	cout << endl;

	f3 = f1.sub(f2);
	f1.displayFrac();
	cout << "-";
	f2.displayFrac();
	cout << "=";
	f3.displayFrac();
	cout << endl;

	return 0;
}