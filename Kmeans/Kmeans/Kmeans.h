#ifndef KMEANS_H
#define KMEANS_H
#include<opencv2/opencv.hpp>
#include<highgui.h>
#include<iostream>
#include<vector>
using namespace std;
class Kmeans
{
private:
	int K;
	IplImage *img;
	IplImage *img_gray;
	double SSE;
	int *label;
	int *dist;
	int *x;
	vector<double> center;
public:
	Kmeans() :K(1), img(NULL),img_gray(NULL),SSE(0),label(NULL),dist(NULL),x(NULL){}
	Kmeans(int k) :K(k), img(NULL),img_gray(NULL),SSE(0),label(NULL),dist(NULL),x(NULL){}
	~Kmeans(){ cout << "End Now!" << endl; }
	void readImage(const char*);
	void showImage();
	void SetK(int k){ K = k; }
	int GetK(){ return K; }
	void init();
	void loadData();
	void BiKmeans();
	double caldist(const double&, const double&);
	void split(vector<pair<int, int> >&);
	void Cluster();
};

#endif