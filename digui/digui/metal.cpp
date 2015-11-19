#include<iostream>
using namespace std;


int s[100];
int c = 3;
int cut(int *p, int n)
{
	if (n <=0)
		return 0;
	int q = -INFINITY;
	for (int i = 1; i <= n&&i<=10; i++)
	{
		int qmax = p[i - 1] + cut(p, n - i);
		if (qmax > q)
			q = qmax;
	}
	return q;
}

int cut1(int *p, int n)
{
	int *r=new int[n];
	r[0] = 0;
	s[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int q = -INFINITY;
		int qmax;
		for (int j = 1; j <= i&&j<=10; j++)
		{
			qmax = p[j - 1] + r[i - j];
			if (i != j)
				qmax -= c;
			if (qmax > q)
			{
				q = qmax;
				s[i] = j;
			}
		}
		r[i] = q;
	}
	return r[n];
}

int cut2(int *p, int *r, int n)
{
	int q;
	if (r[n] > 0)
		return r[n];
	if (n == 0)
		q = 0;
	else
	{
		q = -INFINITY;
		for (int i = 1; i <= n&&i <= 10; i++)
		{
			int qmax;
			if (i == n)
				qmax = p[i - 1] + cut2(p, r, n - i);
			else
				qmax = p[i - 1] + cut2(p, r, n - i) - c;
			if (qmax > q)
				q = qmax;
		}
	}
	r[n] = q;
	return q;
}

int main()
{
	int cost;
	int p[] = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	int *r = new int[100];
	int n = 27;
	//for (int n = 1; n <= 30; n++)
	//{
		//cost = cut(p, n);
		//cout << cost << endl;
		cost = cut1(p, n);
		cout << cost << endl;
		for (int i = 0; i < n; i++)
			cout << s[i] << " ";
		cout << endl;
		for (int i = n; i >= 0; i-=s[i])
		{
			cout << "->"<<s[i] ;
			if (s[i] == i)
				break;
		}
		cout << endl;
		cost = cut2(p, r, n);
		cout << cost << endl;
	//}
}