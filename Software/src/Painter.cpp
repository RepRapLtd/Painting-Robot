//============================================================================
// Name        : Painter.cpp
// Author      : Adrian Bowyer
// Version     :
// Copyright   : GPL
// Description : Painting robot control program
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

#include "Painter.h"

#define STROKES 2000
#define REPORT 200

void Painter::ShowResult(Mat img, char* title)
{
	char text[100];
	sprintf(text,"%s %d", title, frameCount);

	cvNamedWindow(text, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(text, 100+frameXOff, 100+frameYOff);

	frameXOff += 50;
	frameYOff += 50;

	IplImage copy = img;
	IplImage* new_image = &copy;

	cvShowImage(text, new_image );

	cvWaitKey(0);

	// release the image
	//cvReleaseImage(&img );
	frameCount++;
}



uchar Painter::Percentile(Mat img, double percentile)
{
	int histogram[MAX_PIXEL];
	for(int i = 0; i < MAX_PIXEL; i++)
		histogram[i] = 0;
	uchar p;

	for(int x = 0; x < imageWidth; x++)
		for(int y = 0; y < imageHeight; y++)
		{
			p = GetPixelMono(img, x, y);
			histogram[p]++;
		}

	//for(int i = 0; i < MAX_PIXEL; i++)
	//	cout << histogram[i] << ' ';
	//cout << endl;

	double frac = percentile*pixelCount;
	//cout << "frac: " << frac << endl;

	double total = 0;

	for(int i = 0; i < MAX_PIXEL; i++)
	{
		total += (double)histogram[i];
		if(total >= frac)
			return i;
	}

	cerr << "Can't find percentile in histogram!" << endl;

	return MAX_PIXEL;
}


void Painter::GoColour(Mat img, uchar p[])
{
	for(int x = 0; x < imageWidth; x++)
		for(int y = 0; y < imageHeight; y++)
			PutPixel(img, x, y, p);
}


void Painter::Threshold(Mat image, double percentile)
{
	double t = (double)Percentile(image, percentile);
	if(debug)
		cout << "Threshold: " << t << endl;
	threshold(image, image, t, 255.0, THRESH_BINARY);
}




void Painter::Blob(Mat image, Point pixel, uchar colour[], double d)
{
	double r2 = d*d/4;
	for(int y = 0; y < round(d/2); y++)
	{
		int xm = round(sqrt(r2 - y*y));
		for(int x = 0; x < xm; x++)
		{
			PutPixel(image, pixel.x + x, pixel.y + y, colour);
			PutPixel(image, pixel.x - x, pixel.y + y, colour);
			PutPixel(image, pixel.x + x, pixel.y - y, colour);
			PutPixel(image, pixel.x - x, pixel.y - y, colour);
		}
	}
}


void Painter::Stroke(Mat image, int count, uchar colour[], double d)
{
	for(int i = 0; i < count; i++)
		Blob(image, pixels[i], colour, d+1);
}


uint Painter::PixelDifference2(uchar a[], uchar b[])
{
	uint result = 0;
	for(int k = 0; k < 3; k++)
	{
		int diff = a[k] - b[k];
		result += diff*diff;
	}
	return result;
}


uchar Painter::PixelDifference(uchar a[], uchar b[])
{
	uint d2 = PixelDifference2(a, b);
	d2 = sqrt((double)d2)*255.0/441.67295593;  // Scaling factor from 3D to 1D
	return (uchar)d2;
}


void Painter::ImageDifference(Mat a, Mat b)
{
	uchar dataA[3];
	uchar dataB[3];
	uchar pixel;
	for(int x = 0; x < imageWidth; x++)
		for(int y = 0; y < imageHeight; y++)
		{
			GetPixel(a, x, y, dataA);
			GetPixel(b, x, y, dataB);
			pixel = PixelDifference(dataA, dataB);
			PutPixelMono(difference, x, y, pixel);
		}
}


Painter::Painter(const Mat org, bool db)
{
	debug = db;

	frameXOff = 0;
	frameYOff = 0;

	org.copyTo(original);
	imageWidth = original.cols;
	imageHeight = original.rows;
	pixelCount = imageWidth*imageHeight;
	original.copyTo(painting);

	for(int k = 0; k < 3; k++)
		average[k] = 0;

	for(int x = 0; x < imageWidth; x++)
		for(int y = 0; y < imageHeight; y++)
		{
			GetPixel(original, x, y, pixel);
			for(int k = 0; k < 3; k++)
				average[k] += (double)pixel[k];
		}

	for(int k = 0; k < 3; k++)
		pixel[k] = (uchar)(average[k]/(double)pixelCount);

	GoColour(painting, pixel);

	cvtColor(original, difference, CV_BGR2GRAY);
	difference.copyTo(eroded);

	frameCount = 0;
	blob = imageWidth/30;
	thresholdValue = 0.7;
	brushReduction = 0.7;

	strokes = 0;
	keepGoing = true;

	ShowResult(org, "original");
}

void Painter::Draw()
{

}

void Painter::Paint()
{
	blob = imageWidth/30;
	thresholdValue = 0.7;
	brushReduction = 0.7;

	strokes = 0;
	keepGoing = true;

	Size *myBlob = new Size(blob, blob);
	kernel = getStructuringElement(MORPH_ELLIPSE, *myBlob);

	while(strokes < STROKES && keepGoing)
	{
		ImageDifference(original, painting);
		if(debug && strokes%REPORT == 0)
			ShowResult(difference, "difference");
		Threshold(difference, thresholdValue);
		if(debug && strokes%REPORT == 0)
			ShowResult(difference, "threshold");
		erode(difference, eroded, kernel);

		findContours(eroded, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

		big = 0;
		largestContourIndex = -1;

		for(int i = 0; i < contours.size(); i++)
		{
			b = contourArea(contours[i], false);
			if(b > big)
			{
				big = b;
				largestContourIndex=i;
			}
		}

		if(largestContourIndex < 0)
		{
			cout << "biggest null!" << endl;
			return;
		}


		pixels = contours[largestContourIndex];

		track = pixels.size();
		if(track > 20)
		{
			track = track/2;

			average[0] = average[1] = average[2] = 0;
			for(pix = 0; pix < track; pix++)
			{
				GetPixel(original, pixels[pix].x, pixels[pix].y, pixel);
				for(int k = 0; k < 3; k++)
					average[k] += (double)pixel[k];
			}
			for(int k = 0; k < 3; k++)
				pixel[k] = (uchar)(average[k]/(double)track);
			Stroke(painting, track, pixel, blob);
		}else
		{
			cout << "Short contour: " << track << ", blob: " << blob << endl;
			blob = blob*brushReduction;

			if(blob < 2)
				keepGoing = false;
			else
			{
				delete myBlob;
				myBlob = new Size(blob, blob);
				kernel = getStructuringElement(MORPH_ELLIPSE, *myBlob);
			}
		}
		strokes++;
		if(strokes%REPORT == 0)
			ShowResult(painting, "Partial painting");
	}
}

void Painter::Show()
{
	ShowResult(painting, "painting");
}




int main(int argc, char *argv[])
{
	Mat org = cvLoadImage("/home/ensab/Desktop/rrl-cloud/Libraries-and-settings/workspace/opencv-one/resources/ab-square.jpg");
	Painter* p = new Painter(org, true);
	p->Paint();
	//p->Draw();
	p->Show();
	return 0;
}
