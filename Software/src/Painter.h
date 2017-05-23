/*
 * Painter.h
 *
 *  Created on: 3 Oct 2016
 *      Author: ensab
 */

#ifndef PAINTER_H_
#define PAINTER_H_

#include <cv.h>
#include <highgui.h>

using namespace cv;

#define  MAX_PIXEL 255

class Painter
{
public:
	Painter(const Mat original, bool db);
	void Paint();
	void Draw();
	void ShowResult(const Mat img, char* title);
	void Show();

private:

	uchar GetPixelMono(const Mat img, int x, int y);
	void PutPixelMono(Mat img, int x, int y, uchar p);
	void GetPixel(const Mat img, int x, int y, uchar p[]);
	void PutPixel(Mat img, int x, int y, uchar p[]);
	uchar Percentile(const Mat img, double percentile);
	void GoColour(Mat img, uchar p[]);
	void Threshold(Mat image, double percentile);
	void Blob(Mat image, Point pixel, uchar colour[], double d);
	void Stroke(Mat image, int count, uchar colour[], double d);
	uint PixelDifference2(uchar a[], uchar b[]);
	uchar PixelDifference(uchar a[], uchar b[]);
	void ImageDifference(Mat a, Mat b);
	void ConvexQuadrilateral(Point corner[]);


	int frameCount;
	int frameXOff;
	int frameYOff;
	int pixelCount;
	int imageWidth;
	int imageHeight;
	double blob;
	double thresholdValue;
	double brushReduction;
	int strokes;
	bool keepGoing;
	double big;
	double b;
	int largestContourIndex;
	int track;
	int pix;
	bool debug;

	Mat original;
	Mat difference;
	Mat painting;
	Mat kernel;
	Mat eroded;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	double average[3];
	uchar pixel[3];
	vector<Point> pixels;
};

inline uchar Painter::GetPixelMono(Mat img, int x, int y)
{
	if(x < 0 || y < 0 || x >= imageWidth || y >= imageHeight)
	{
		if(debug)
			cout << "Reading outside the frame." << endl;
		return 0;
	}
	int pos = img.channels()*(img.cols*y + x);
	return img.data[pos];
}

inline void Painter::PutPixelMono(Mat img, int x, int y, uchar p)
{
	if(x < 0 || y < 0 || x >= imageWidth || y >= imageHeight)
	{
		if(debug)
			cout << "Writing outside the frame." << endl;
		return;
	}
	int pos = img.channels()*(img.cols*y + x);
	img.data[pos] = p;
}

inline void Painter::GetPixel(Mat img, int x, int y, uchar p[])
{
	if(x < 0 || y < 0 || x >= imageWidth || y >= imageHeight)
	{
		if(debug)
			cout << "Reading outside the frame." << endl;
		p[0] = p[1] = p[2] = 0;
		return;
	}
	int pos = img.channels()*(img.cols*y + x);
	p[0] = img.data[pos];
	p[1] = img.data[pos + 1];
	p[2] = img.data[pos + 2];
}

inline void Painter::PutPixel(Mat img, int x, int y, uchar p[])
{
	if(x < 0 || y < 0 || x >= imageWidth || y >= imageHeight)
	{
		if(debug)
			cout << "Writing outside the frame." << endl;
		return;
	}
	int pos = img.channels()*(img.cols*y + x);
	img.data[pos] = p[0];
	img.data[pos + 1] = p[1];
	img.data[pos + 2] = p[2];
}



#endif /* PAINTER_H_ */
