#include<iostream>
using namespace std;

int f[100];

void money(int *c, int n)
{
	f[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int min = 10000;
		for (int j = 0; j < 3; j++)
		{
			if (c[j]>i)
				break;
			int temp;
			temp = f[i - c[j]] + 1;
			if (temp < min)
				min = temp; 
		}
		f[i] = min;
	}
}

int main()
{
	int c[] = { 1, 5, 7 };
	money(c, 10);
	for (int i = 0; i <= 10; i++)
		cout << f[i] << endl;
	return 0;
}