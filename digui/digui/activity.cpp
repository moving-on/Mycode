#include<iostream>
using namespace std;

int c[100][100];
void act(int *s, int *f,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i;j>=0; j--)
		{
			if (i == j)
				c[j][i] = 1;
			else if (j == (i - 1))
				{
					if (f[j] <= s[i])
						c[j][i] = 2;
					else
						c[j][i] = 1;
				}
			else
			{
				int max = -INFINITY;
				for (int k = i-1; k >j; k--)
				{
					int temp = c[j][k] + c[k][i] ;
					if (temp > max)
					{
						max = temp;
					}
				}
				c[j][i] = max;
			}

		}
	}
}

int act1(int *s, int *f, int k, int n)
{
	int len = 0;
	if (k == n)
		return len;
	int m = k + 1;
	while (m <= n&&s[m] < f[k])
		m = m + 1;
	if (m <= n)
		len=1+act1(s, f, m, n);
	return len;
}

int main()
{
	int s[] = { 0,1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	int f[] = { 0,4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16 };
	int n = 11;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			c[i][j] = 0;
	act(s, f, 11);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << c[i][j] << " ";
		cout << endl;
	}
	int len = act1(s, f, 0, n);
	cout << len << endl;
}