#include<iostream>
#include<cstring>
using namespace std;

void BiInsertSort(int *a, int n)
{
	for (int i = 1; i < n; i++)
	{
		int temp = a[i];
		int left = 0;
		int right = i - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (a[mid] <= temp)
				left = mid + 1;
			else
				right = mid - 1;
		}
		for (int j = i - 1; j >= left; j--)
		{
			a[j + 1] = a[j];
		}
		a[left] = temp;
	}
}

int main()
{
	int a[] = { 3, 4, 8, 1, 2, 0, 9, 7, 5, 6 };
	BiInsertSort(a, 10);
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
}