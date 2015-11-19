#include<iostream>
using namespace std;


void native_match(char *P, char *T,int n,int m)
{
	for (int i = 0; i < n - m + 1; i++)
	{
		int flag = 1;
		for (int j = 0; j < m; j++)
		{
			if (P[j] != T[i + j])
			{
				flag = 0;
				break;
			}
		}
		if (flag)
			cout << "pattern occurs with shift " << i << endl;
	}
}

int main()
{
	char P[] = "0001";
	char T[] = "000010001010001";
	native_match(P, T,15,4);
}