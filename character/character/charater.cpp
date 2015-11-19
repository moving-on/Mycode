#include<iostream>
#include<cmath>
using namespace std;


double mi(double(*a)[5],int n)
{
	double *u = new double[n];
	for (int i = 1; i < n; i++)
	{
		u[i] = 0.0;
	}
	u[0] = 1;
	double eta = 0.0001;
	double error = eta + 1;
	double theta;
	double *y = new double[n];
	double beta_new=0, beta_old=0;
	while (error >= eta)
	{
		double sum = 0.0;
		for (int i = 0; i < n; i++)
		{
			sum += u[i] * u[i];
		}
		theta = sqrt(sum);
		for (int i = 0; i < n; i++)
		{
			y[i] = u[i] / theta;
		}
		for (int i = 0; i < n; i++)
		{
			double temp = 0.0;
			for (int j = 0; j < n; j++)
			{
				temp += a[i][j] * y[j];
			}
			u[i] = temp;
		}
		//for (int i = 0; i < n; i++)
		//	cout << u[i] << " ";
		//cout << endl;
		double temp = 0;
		for (int i = 0; i < n; i++)
		{
			temp += y[i] * u[i];
		}
		beta_new = temp;
		error = fabs((beta_new - beta_old)/beta_new);
		beta_old = beta_new;
	}
	//for (int i = 0; i < n; i++)
		//cout << y[i] << " ";
	//cout << endl;
	delete[] u;
	delete[] y;
	return beta_new;;
}

int main()
{
	//double a[][3] = { { 6, -12, 6 }, { -21, -3, 24 }, { -12, -12, 51 } };
	//double a[][3] = { { 2,3,2 }, { 10,3,4 }, { 3,6,1 } };
	double a[][5] = { { -1, 1, 1, 0, 0 }, { 1, -1, 1, 1, 0 }, { 1, 1, -1, 1, 1 }, { 0, 1, 1, -1, 1 }, { 0, 0, 1, 1, -1 } };
	const int n = 5;
	double beta[n] = { 0, 0 };
	for (int k = 0; k < n; k++)
	{
		if (k > 0)
		{
			for (int i = 0; i < n; i++)
				a[i][i] -= beta[k-1];
		}
		double temp = mi(a, n);
		beta[k] = temp;
		cout << temp << endl;
		for (int j = 0; j < k; j++)
			beta[k] += beta[j];
		cout << "beta" << beta[k] << endl;
	}
	for (int i = 0; i < n; i++)
		cout << beta[i] << " ";
	cout << endl;
	
};

