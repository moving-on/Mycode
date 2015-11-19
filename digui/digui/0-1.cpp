#include<iostream>
using namespace std;

int f[100][100];
void bag(int *p, int *w, int W, int n)
{
	for (int y = 0; y <= W; y++)
	{
		if (y >= w[n])
			f[n][y] = p[n];
		else
			f[n][y] = 0;
	}

	for (int i = n - 1; i >= 0; i--)
	{
		for (int y = 0; y <= W; y++)
		{
			if (y >= w[i])
			{
				if (f[i + 1][y] > (f[i + 1][y - w[i]]+ p[i]))
					f[i][y] = f[i + 1][y];
				else
					f[i][y] = f[i + 1][y - w[i]]+p[i];
			}
			else
				f[i][y] = f[i + 1][y];

		}
	}
}

int main()
{
	int p[] = { 60, 100, 120 };
	int w[] = { 1, 2, 3 };
	int W = 5;
	int n = 3;
	bag(p, w, W, n-1);
	for (int i = 0; i <n; i++)
	{
		for (int j = 0; j <= W; j++)
			cout << f[i][j] << " ";
		cout << endl;
	}
}