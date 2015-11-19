#include<iostream>
using namespace std;

int c[100][100];
int b[100][100];
int lcs(int *x, int *y,int i,int j)
{
	int result;
	if (i == -1 || j == -1)
		return 0;
	else
	{
		if (x[i] == y[j])
			result = 1 + lcs(x, y, i - 1, j - 1);
		else
		{
			int temp1,temp2;
			temp1 = lcs(x, y, i - 1, j);
			temp2 = lcs(x, y, i, j - 1);
			if (temp1 > temp2)
				result = temp1;
			else
				result = temp2;
		}
	}
	return result;
}

void lcs1(int *x, int *y)
{
	int m = 10, n = 10;
	for (int i = 0; i <=m; i++)
		c[i][0] = 0;
	for (int j = 0; j <=n; j++)
		c[0][j] = 0;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			if (x[m - i] == y[n - j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = 3;
			}
		}
}

void PrintLCS(int *y, int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 1)
	{
		PrintLCS(y, i - 1, j - 1);
		cout << "->" << y[10-i];
	}
	else if (b[i][j] == 2)
		PrintLCS(y, i - 1, j);
	else if (b[i][j] == 3)
		PrintLCS(y, i, j - 1);
}

int main()
{
	int x[] = { 1, 2, 4, 7, 2, 3, 9, 0, 2, 4 };
	int y[] = { 1, 2, 4, 2, 5, 6, 1, 0, 2, 4};
	int result = lcs(x, y, 9, 9);
	cout << result << endl;
	lcs1(x, y);
	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j <= 10; j++)
			cout << c[i][j] << " ";
		cout << endl;
	}
	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j <= 10; j++)
			cout << b[i][j] << " ";
		cout << endl;
	}
	PrintLCS(x, 10, 10);
}

