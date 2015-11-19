#include<iostream>
#include<vector>
using namespace std;
const int N = 8;
const int K = 6;

int A[N] = { 2, 5, 3, 0, 2, 3, 0, 3 };
int B[N] = {};


void counting_sort()
{
	int C[K];
	for (int i = 0; i < K; i++)
		C[i] = 0;
	for (int j = 0; j < N; j++)
		C[A[j]] = C[A[j]] + 1;
	for (int i = 0; i < K; i++)
		cout << C[i] << " ";
	cout << endl;
	for (int i = 1; i < K; i++)
		C[i] = C[i] + C[i - 1];
	for (int i = 0; i < K; i++)
		cout << C[i] << " ";
	cout << endl;
	for (int i = N - 1; i >= 0; i--)
	{
		B[C[A[i]]-1] = A[i];
		C[A[i]] = C[A[i]] - 1;
	}
	for (int i = 0; i < K; i++)
		cout << C[i] << " ";
	cout << endl;
}

int main()
{
	counting_sort();
	for (int i = 0; i < N; i++)
		cout << B[i] << " ";
	cout << endl;
}