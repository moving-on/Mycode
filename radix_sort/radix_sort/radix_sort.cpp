#include<iostream>
using namespace std;

const int n = 50;

int GetNDigit(int nNumber, int nIdx)
{
	for (int i = nIdx; i > 0; i--)
		nNumber /= 10;
	return nNumber % 10;
}

void CountingSort_SpecificDigit(int a[], int nIdxDigit,int nK=9)
{
	int *digitNum = new int[n];
	memset(digitNum, 0, sizeof(int)*n);
	int *count = new int[nK+1];
	memset(count, 0, sizeof(int)*(nK + 1));
	int *result = new int[n];
	memset(result, 0, sizeof(int)*n);

	for (int idx = 0; idx < n; idx++)
		digitNum[idx] = GetNDigit(a[idx], nIdxDigit);

	for (int idx = 0; idx < n; idx++)
		count[digitNum[idx]]++;
	for (int idx = 1; idx <= nK; idx++)
		count[idx] = count[idx] + count[idx - 1];
	for (int idx = n - 1; idx >= 0; idx--)
	{
		result[count[digitNum[idx]] - 1] = a[idx];
		count[digitNum[idx]]--;
	}
	memcpy(a, result, sizeof(int)*n);
	delete[] digitNum;
	delete[] count;
	delete[] result;
}

void RadixSort(int a[], int nDigit)
{
	for (int idx = 0; idx <= nDigit; idx++)
		CountingSort_SpecificDigit(a, idx);
}
  
int main()
{
	int i;
	int a[n] = {};
	for (int i = 0; i < n; i++)
		a[i] = rand() % 99999;
	RadixSort(a, 4);
	for (int i = 0; i < n; i++)
		cout << a[i] << endl;
}