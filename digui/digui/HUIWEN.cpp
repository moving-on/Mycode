#include<iostream>
using namespace std;

int p[100][100];
int huiwen(char s[],int n)
{
	int maxlen = 0;
	for (int i = 0; i < n; i++)
		p[i][i] = 1;
	for (int i = 0; i < n - 1; i++)
		if (s[i] == s[i + 1])
		{
			p[i][i + 1] = 1;
			maxlen = 2;
		}
	for (int len = 3; len <= n; len++)
	{
		for (int i = 0; i < n - len + 1; i++)
		{
			int j = i + len - 1;
			if (s[i] == s[j] && p[i + 1][j - 1] == 1)
			{
				p[i][j] = 1;
				maxlen = len;
			}
		}
	}
	return maxlen;
}


int main()
{
	char s1[] = "racecar";
	int n = 9;
	int maxlen=huiwen(s1, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << p[i][j]<<" ";
		cout << endl;
	}
	cout << maxlen << endl;
}