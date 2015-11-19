#include"Kmeans.h"
#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<time.h>
using namespace std;
double *dis = NULL;
int *lab = NULL;
double cent[2];
void Kmeans::readImage(const char *filename)
{
	img=cvLoadImage(filename);
}

void Kmeans::showImage()
{
	cvShowImage("rgb", img);
	cvShowImage("gray", img_gray);
}

void Kmeans::init()
{
	int n, m;
	n = img->height;
	m = img->width;
	label = new int[n*m];
	dist = new int[n*m];
	img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCvtColor(img, img_gray, CV_BGR2GRAY);
}

void Kmeans::loadData()
{
	CvScalar s;
	x = new int[img->height*img->width];
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
		{
			s = cvGet2D(img_gray, i, j);
			x[i*img->width + j] = s.val[0];
		}
}

void Kmeans::BiKmeans()
{
	int N = img_gray->height*img_gray->width;
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += x[i];
		label[i] = 0;
	}
	center.push_back(sum / N);

	for (int i = 0; i < N; i++)
	{
		dist[i] = caldist(x[i], center[0]);
	}

	int centernum = 1;
	vector<pair<int, int> >splitTmp;
	int splitK;
	double *cenTmp;
	int *labTmp;
	while (centernum < K)
	{
		double lowestSSE = INFINITY;
		for (int k = 0; k < centernum; k++)
		{
			vector<pair<int, int> > splitx;
			double tmpSSE = 0;
			for (int i = 0; i < N; i++)
			{
				if (label[i] == k)
				{
					splitx.push_back(make_pair(x[i], i));
				}
				else
					tmpSSE += dist[i];
			}
			split(splitx);
			double splitSSE = 0;
			for (int i = 0; i < splitx.size(); i++)
			{
				splitSSE += dis[i];
			}
			tmpSSE += splitSSE;
			if (tmpSSE < lowestSSE)
			{
				lowestSSE = tmpSSE;
				splitK = k;
				splitTmp.clear();
				splitTmp.insert(splitTmp.begin(),splitx.begin(),splitx.end());
				labTmp = lab;
				cenTmp = cent;
			}
		}
		centernum++;
		center[splitK] = cenTmp[0];
		center.push_back(cenTmp[1]);
		cout << endl;
		for (int i = 0; i < splitTmp.size(); i++)
		{
			if (labTmp[i] == 0)
				label[splitTmp[i].second] = splitK;
			else
				label[splitTmp[i].second] = centernum-1;
		}
	}
}

double Kmeans::caldist(const double &x1, const double &x2)
{
	return (x1 - x2)*(x1 - x2);
}

void Kmeans::split(vector<pair<int, int> > &xx)
{
	int minx = 256;
	int maxx = -1;
	for (int i = 0; i < xx.size(); i++)
	{
		if (xx[i].first < minx)
			minx = xx[i].first;
		if (xx[i].first > maxx)
			maxx = xx[i].first;
	}
	srand((unsigned)time(NULL));
	cent[0] = (rand() % (maxx - minx)) + minx;
	cent[1] = (rand() % (maxx - minx)) + minx;
	dis = new double[xx.size()];
	lab = new int[xx.size()];
	int labelchanged = 1;
	double distance;
	while (labelchanged)
	{
		labelchanged = 0;
		for (int i = 0; i < xx.size(); i++)
		{
			double mindist = INFINITY;
			int mink = -1;
			for (int k = 0; k < 2; k++)
			{
				distance = caldist(xx[i].first, cent[k]);
				if (distance < mindist)
				{
					mindist = distance;
					mink = k;
				}
			}
			if (lab[i] != mink)
				labelchanged = 1;
			lab[i] = mink;
			dis[i] = mindist;
		}
		double sum1 = 0.0, sum2 = 0.0;
		int n1 = 0, n2 = 0;
		for (int i = 0; i < xx.size(); i++)
		{
			if (lab[i] == 0)
			{
				sum1 += xx[i].first;
				n1++;
			}
			else
			{
				sum2 += xx[i].first;
				n2++;
			}
		}
		cent[0] = sum1 / n1;
		cent[1] = sum2 / n2;
	}
}

void Kmeans::Cluster()
{
	CvScalar s;
	for (int i = 0;i< img->height; i++)
		for (int j = 0;j< img->width; j++)
		{
			if (label[i*img->width + j]==0)
			{
				s.val[0] = 255;
				s.val[1] = 0;
				s.val[2] = 0;
				cvSet2D(img, i, j, s);
			}
			else if (label[i*img->width + j] == 1)
			{
				s.val[0] = 0;
				s.val[1] = 255;
				s.val[2] = 0;
				cvSet2D(img, i, j, s);
			}
			else if (label[i*img->width + j] == 2)
			{
				s.val[0] = 0;
				s.val[1] = 0;
				s.val[2] = 255;
				cvSet2D(img, i, j, s);
			}
			else if (label[i*img->width + j] == 3)
			{
				s.val[0] = 255;
				s.val[1] = 0;
				s.val[2] = 255;
				cvSet2D(img, i, j, s);
			}
			else if (label[i*img->width + j] == 4)
			{
				s.val[0] = 0;
				s.val[1] = 255;
				s.val[2] = 255;
				cvSet2D(img, i, j, s);
			}
		}
}