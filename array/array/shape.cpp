#include<iostream>
#include<cmath>
using namespace std;

class CShape
{
public:
	virtual double Aera(){ return 0; }
	virtual void PrintInfo(){}
};

class CRectangle :public CShape
{
public:
	int w, h;
	virtual double Aera();
	virtual void PrintInfo();
};

class CCircle :public CShape
{
public:
	int r;
	virtual double Aera();
	virtual void PrintInfo();
};

class CTriangle :public CShape
{
public:
	int a, b, c;
	virtual double Aera();
	virtual void PrintInfo();
};

double CRectangle::Aera()
{
	return w*h;
}

void CRectangle::PrintInfo()
{
	cout << "Rectangle:" << Aera() << endl;
}

double CCircle::Aera()
{
	return 3.14*r*r;
}

void CCircle::PrintInfo()
{
	cout << "CCircle:" << Aera() << endl;
}

double CTriangle::Aera()
{
	double p = (a + b + c) / 2.0;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}

void CTriangle::PrintInfo()
{
	cout << "Triangle:" << Aera() << endl;
}

CShape *pShape[100];
int MyCompare(const void *s1, const void *s2)
{
	CShape **p1 = (CShape**)s1;
	CShape **p2 = (CShape**)s2;
	double a1 = (*p1)->Aera();
	double a2 = (*p2)->Aera();
	if (a1 < a2)
		return -1;
	else if (a2 < a1)
		return 1;
	else
		return 0;
}

int main()
{
	int i, n;
	CRectangle *pr;
	CCircle *pc;
	CTriangle *pt;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		char c;
		cin >> c;
		switch (c)
		{
		case 'R':
			pr = new CRectangle();
			cin >> pr->w >> pr->h;
			pShape[i] = pr;
			break;
		case 'C':
			pc = new CCircle();
			cin >> pc->r;
			pShape[i] = pc;
			break;
		case 'T':
			pt = new CTriangle();
			cin >> pt->a >> pt->b >> pt->c;
			pShape[i] = pt;
			break;
		}
	}
	qsort(pShape, n, sizeof(CShape*), MyCompare);
	for (i = 0; i < n; i++)
	{
		pShape[i]->PrintInfo();
		delete pShape[i];
	}
	return 0;
}