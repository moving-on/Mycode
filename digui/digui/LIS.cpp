#include<iostream>
using namespace std;

int f[100];
void LIS(int *x, int n)
{
	f[0] = 1;
	for (int i = 1; i < n; i++)
	{
		int max = -INFINITY;
		for (int j = 0; j < i; j++)
		{
			int temp;
			if (x[i]>x[j])
				temp = f[j] + 1;
			else
				temp = 1;
			if (temp > max)
				max = temp;
		}
		f[i] = max;
	}
}

int main()
{
	int x[] = { 10, 4, 5, 3, 6, 9,8,1,2,3,4,5,6,7 ,3};
	LIS(x, 15);
	for (int i = 0; i < 15; i++)
		cout << f[i] << endl;
	return 0;
}