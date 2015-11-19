#include<iostream>
using namespace std;

int factorial_recursive(int n)
{
	if (n == 0)
		return 1;
	else
		return factorial_recursive(n - 1)*n;
}

int factorial_loop(int n)
{
	int result = 1;
	if (n == 0)
		return 1;
	else
		for (int i = 1; i <= n; i++)
			result *= i;
	return result;
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		cout << i << "!=" << factorial_recursive(i) << endl;
		cout << i << "!=" << factorial_loop(i) << endl;
	}
}