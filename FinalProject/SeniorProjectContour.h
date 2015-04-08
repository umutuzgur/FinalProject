//
//  SeniorProjectContour.h
//  SeniorProject
//
//  Created by Çelebi Murat on 04/03/15.
//  Copyright (c) 2015 Çelebi Murat. All rights reserved.
//

#ifndef FinalProject_SeniorProjectContour_h
#define FinalProject_SeniorProjectContour_h
#define RECT_ERROR 0.2
#define LINE_ERROR 0.1
#define CONTOUR_RECT_RATIO 0.7
#define CIRCUMFERENCE_AREA_RATIO 0.1
#define OVER_STEP 8
#define TRACE_ERROR 600

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/photo/photo.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

typedef tuple<vector<Point>, Rect> ContourRectangleTuple;

vector<vector<Point>> getContours(Mat image);
void applySobel(Mat* image);
vector<ContourRectangleTuple> getBoundingRectangles(vector<vector<Point>> contours);
vector<ContourRectangleTuple> removeNonRelevantRectangles(vector<ContourRectangleTuple> crTuple);
void drawBoundingRectangles(Mat image, vector<ContourRectangleTuple> crTuple);
vector<vector<int>> getRelations(vector<ContourRectangleTuple> crTuple, Mat image);
vector<int> getRelatedContours(Rect r, vector<ContourRectangleTuple> crTuple, Mat image);
bool isRelated(Rect r1, Rect r2, Mat image);
tuple<Point, Point> getStartEndPoints(Rect r1, Rect r2);
bool isContourRelevant(ContourRectangleTuple crTuple);




#endif
