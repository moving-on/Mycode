#include<iostream>
using namespace std;

int c[100][100];
void jump(int number)
{
	for (int n = 0; n <= number; n++)
	{
		if (n == 0||n==1||n==2)
		{
			for (int i = 0; i <= n; i++)
				c[i][n] = n;
		}
		else
		{
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= n - i; j++)
				{
					c[i][n] += c[j][n - i];
				}
		}

	}
}

int main()
{
	jump(20);
	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
			cout << c[i][j]<<" ";
		cout << endl;
	}
}