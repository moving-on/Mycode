#include<string>
#include<iostream>
using namespace std;
int main()
{
	char a[1002];
	memset(a, 0, sizeof(a));
	cout << sizeof(a) << endl;
	for (int i = 0; i < 1002; i++)
		cout << a[i] << " ";
}