#include<iostream>
using namespace std;

typedef int Type;

void exchange(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int Partion(int* a, int f, int l)
{
	Type tmp = a[l];
	int i = f;
	int j = l - 1;
	if (f >= l)
		return -1;
	for (;;)
	{
		while (a[i] < tmp) i++;
		while (a[j] > tmp) j--;
		if (i < j)
			exchange(&a[i], &a[j]);
		else
			break;
	}
	exchange(&a[i], &a[l]);
	return i;
}

void Quick_sort(Type *a, int f, int l)
{
	int r=Partion(a, f, l);
	if (r == -1)
		return;
	Quick_sort(a, f, r - 1);
	Quick_sort(a, r + 1, l);
}


int main()
{
	Type a[] = { 1, 5, 4, 8, 6, 9, 0, 7 ,2, 3, 8, 6, 9, 0, 7 };
	Quick_sort(a, 0, 14);
	for (int i = 0; i < 15; i++)
		cout << a[i] << " ";
	cout << endl;
}