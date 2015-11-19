#include"Kmeans.h"
#include<iostream>
using namespace std;

int main()
{
	Kmeans km(5);
	km.readImage("E:\VS2013\MYCODE\Kmeans\Kmeans\test2.jpg");
	km.init();
	km.loadData();
	km.BiKmeans();
	km.Cluster();
	km.showImage();
	cvWaitKey();
}