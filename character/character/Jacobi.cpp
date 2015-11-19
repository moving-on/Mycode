#include<iostream>
#include<cmath>
using namespace std;
int jcb(double (*a)[3], double (*v)[3], double eps, int jt,int columns,int rows)
//jacobi求实对称矩阵的特征值和特征向量 
{
	int i, j, p, q, l;
	double fm, cn, sn, omega, x, y, d;
	l = 1;
	for (i = 0; i <= columns - 1; i++)    //赋值v=I 
	{
		v[i][i] = 1.0;
		for (j = 0; j <= columns - 1; j++)
			if (i != j) v[i][j] = 0;
	}
	while (true)
	{
		fm = 0.0;
		for (i = 0; i <= columns - 1; i++)
			for (j = 0; j <= i - 1; j++)
			{
				d = fabs(a[i][j]);
				if ((i != j) && (d>fm))   //取最大的a[p][q] 
				{
					fm = d; p = i; q = j;
				}
			}
		cout << "1 :"<< fm << endl;
		if (fm<eps) //如果达到给定的精度跳出循环 
		{
			return(1);
			break;
		}
		if (l>jt) //如果不能求解 
		{
			return(-1);
			break;
		}
		l = l + 1;	 //记录迭代次数
x = -a[p][q];
y = (a[q][q] - a[p][p]) / 2.0;
omega = x / sqrt(x*x + y*y);
if (y<0.0) omega = -omega;
sn = 1.0 + sqrt(1.0 - omega*omega);
sn = omega / sqrt(2.0*sn);  //正弦 
cn = sqrt(1.0 - sn*sn);  //余弦 
fm = a[p][p];
a[p][p] = fm*cn*cn + a[q][q] * sn*sn + a[p][q] * omega;
a[q][q] = fm*sn*sn + a[q][q] * cn*cn - a[p][q] * omega;
a[p][q] = y*omega + a[p][q] * (2 * cn*cn - 1);
a[q][p] = a[p][q];
for (j = 0; j <= columns - 1; j++)
if ((j != p) && (j != q))
{
	fm = a[p][j];
	a[p][j] = fm*cn + a[q][j] * sn;
	a[q][j] = -fm*sn + a[q][j] * cn;
}
for (i = 0; i <= columns - 1; i++)
if ((i != p) && (i != q))
{
	fm = a[i][p];
	a[i][p] = fm*cn + a[i][q] * sn;
	a[i][q] = -fm*sn + a[i][q] * cn;
}
for (i = 0; i <= columns - 1; i++)
{
	fm = v[i][p];
	v[i][p] = fm*cn + v[i][q] * sn;
	v[i][q] = -fm*sn + v[i][q] * cn;

}

	}
}

void jacobi(double(*a)[3], double(*u)[3], int n)
{
	double eps = 0.00001;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				u[i][j] = 1;
			else
				u[i][j] = 0;
		}
	}
	int iternum = 0;
	while (iternum < 100)
	{
		iternum++;
		double max = -1;
		int p, q;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j <= i - 1; j++)
			{
				if (fabs(a[i][j]) > max)
				{
					max = abs(a[i][j]);
					p = i;
					q = j;
				}
			}
		}
		cout << "2 :" << max << endl;
		if (max < eps)
			break;
		double x = -a[p][q];
		double y = (a[q][q] - a[p][p]) / 2.0;
		double omega = x / sqrt(x*x + y*y);
		if (y < 0.0) omega = -omega;
		double sn = 1.0 + sqrt(1.0 - omega*omega);
		sn = omega / sqrt(2.0*sn);  //正弦 
		double cn = sqrt(1.0 - sn*sn);  //余弦 
		double app = a[p][p];
		double aqq = a[q][q];
		a[p][p] = app * cn*cn + aqq * sn*sn + 2 * a[p][q] * cn*sn;
		a[q][q] = app*sn*sn + aqq*cn*cn - 2 * a[p][q] * cn*sn;
		a[p][q] = 0.5*(aqq - app) * 2 * cn*sn + a[p][q] * (2 * cn*cn - 1);
		a[q][p] = a[p][q];
		for (int i = 0; i < n; i++)
		{
			double api = a[p][i];
			double aqi = a[q][i];
			if (i != p&&i != q)
			{
				a[p][i] = api*cn + aqi*sn;
				a[i][p] = a[p][i];
				a[q][i] = -api*sn + aqi*cn;
				a[i][q] = a[q][i];
			}
		}
		for (int i = 0; i < n; i++)
		{
			double uip = u[i][p];
			double uiq = u[i][q];
			u[i][p] = uip*cn + uiq*sn;
			u[i][q] = -uip*sn + uiq*cn;
		}
	}
}

int main()
{
	double a[3][3] = { { 1, 1, 0.5 }, { 1, 1, 0.25 }, { 0.5, 0.25, 2 } };
	double v[3][3];
	jacobi(a, v, 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3;j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << v[i][j] << " ";
		cout << endl;
	}
	double a1[3][3] = { { 1, 1, 0.5 }, { 1, 1, 0.25 }, { 0.5, 0.25, 2 } };
	double v1[3][3];
	jcb(a1, v1, 0.00001, 100, 3, 3);
}