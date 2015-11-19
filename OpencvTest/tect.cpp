// test.cpp : 定义控制台应用程序的入口点。
//
#include<stdio.h>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
#include<math.h>
#include<highgui.h>
//#pragma comment( lib, "opencv_highgui300d.lib")
//#pragma comment( lib, "opencv_core300d.lib")
using namespace cv;
using namespace std;
void contours_extract(Mat& image, vector<vector<Point>>& contours, vector<Vec4i>& hierarchy);
void calculate_imagetectCR(vector<vector<Point>>& contours, vector<vector<double>>& imagetectCR);
void calculate_imagerightCR(vector<vector<Point>>& contours, vector<double>& imagerightCR);
void recognition(vector<vector<double>>& imagetectCR, vector<double>& imagerightCR, vector<double>&right);
int main(){
	Mat imagetect = imread("imagetect.jpg");
	if (!imagetect.data)
		return -1;
	imshow("源图像", imagetect);
	std::vector<std::vector<Point>> contours_imagetect;//vector可以理解为一个可变长的数组，存的是point形的二维数组变量，之后存储的是边界的x,y坐标  
	vector<Vec4i> hierarchy_imagetect;//类名为Vec4i
	contours_extract(imagetect, contours_imagetect, hierarchy_imagetect);
	vector<vector<double>> imagetectCR;
	calculate_imagetectCR(contours_imagetect, imagetectCR);
	Mat imageright = imread("imageright.jpg");
	if (!imageright.data)
		return -1;
	std::vector<std::vector<Point>> contours_imageright;
	vector<Vec4i> hierarchy_imageright;
	contours_extract(imageright, contours_imageright, hierarchy_imageright);
	vector<double> imagerightCR;
	calculate_imagerightCR(contours_imageright, imagerightCR);
	vector<double> right;
	recognition(imagetectCR, imagerightCR, right);
	Mat result(imagetect.size(), CV_8U, Scalar(0));
	for (int i = 0; i < right.size(); i++)
		drawContours(result, contours_imagetect, right[i], Scalar(255, 0, 0), 2, 8, hierarchy_imagetect, 0, Point());
	result = result + imagetect;
	imshow("目标T型", imageright);
	namedWindow("识别出来的T型");
	imshow("识别出来的T型", result);
	waitKey();
	return 0;
}
void contours_extract(Mat& image, vector<vector<Point>>& contours, vector<Vec4i>& hierarchy){
	Mat gray(image), cannyimage;
	cvtColor(image, gray, CV_BGR2GRAY);//将图像取灰度图像
	//Canny(gray, cannyimage, 125, 350);//用canny边缘算子进行边缘检测
	threshold(gray, gray, 80, 255, CV_THRESH_BINARY);//阈值函数，进行二值化
	//	imshow("hah ", gray);
	vector<vector<Point>> contours_result;
	findContours(gray, contours_result, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//	int minarea = 10;
	//	int maxarea = 100000;
	//	vector<vector<Point>>::const_iterator itc = contours_result.begin();
	//	while (itc != contours_result.end())//除去太长或者太短的轮廓  
	//	{
	//		if (itc->size() < minarea || itc->size() > maxarea)
	//			itc = contours_result.erase(itc);
	//		else
	//			++itc;
	//	}
	vector<Point> contours0;
	vector<Point>::size_type n = 8;
	for (size_t k = 0; k < contours_result.size(); k++)
	{
		if (contours_result[k].size() >= n)
		{
			approxPolyDP(Mat(contours_result[k]), contours0, 3, true);//参数为：输入图像的2维点集，输出结果，估计精度，是否闭合 
			if (contours0.size() >= n)
				contours.push_back(contours0);
		}
	}
}
void calculate_imagetectCR(vector<vector<Point>>& contours, vector<vector<double>>& imagetectCR)
{
	Point a, b, c, d;
	double e, f, g, h, CR;
	for (int j = 0; j < contours.size(); j++)
	{
		vector<double> CRs;
		for (int i = 0; i< 8; i++)
		{
			a = contours[j][(i + 1) % 8] - contours[j][i];
			b = contours[j][(i + 2) % 8] - contours[j][i];
			c = contours[j][(i - 1 + 8) % 8] - contours[j][i];
			d = contours[j][(i - 2 + 8) % 8] - contours[j][i];
			e = sin(atan(a.y / a.x) - atan(c.y - c.x));
			f = sin(atan(b.y / b.x) - atan(c.y - c.x));
			g = sin(atan(a.y / a.x) - atan(d.y - d.x));
			h = sin(atan(b.y / b.x) - atan(d.y - d.x));
			CR = (e*g) / (f*h);
			CRs.push_back(CR);
		}
		imagetectCR.push_back(CRs);
	}
}
void calculate_imagerightCR(vector<vector<Point>>& contours, vector<double>& imagerightCR)
{
	Point a, b, c, d;
	double e, f, g, h, CR;
	for (int i = 0; i < 8; i++)
	{
		a = contours[0][(i + 1) % 8] - contours[0][i];
		b = contours[0][(i + 2) % 8] - contours[0][i];
		c = contours[0][(i - 1 + 8) % 8] - contours[0][i];
		d = contours[0][(i - 2 + 8) % 8] - contours[0][i];
		e = sin(atan(a.y / a.x) - atan(c.y - c.x));
		f = sin(atan(b.y / b.x) - atan(c.y - c.x));
		g = sin(atan(a.y / a.x) - atan(d.y - d.x));
		h = sin(atan(b.y / b.x) - atan(d.y - d.x));
		CR = (e*g) / (f*h);
		imagerightCR.push_back(CR);
	}
}
void recognition(vector<vector<double>>& imagetectCR, vector<double>& imagerightCR, vector<double>& right){
	for (int i = 0; i < imagetectCR.size(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (abs(imagetectCR[i][j] - imagerightCR[k])<0.14)
					right.push_back(i);
			}
		}
	}
}