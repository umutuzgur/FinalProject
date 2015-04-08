////
////  SeniorProjectContour.cpp
////
////  Created by Çelebi Murat on 25/02/15.
////  Copyright (c) 2015 Çelebi Murat. All rights reserved.
////
//
//#include "SeniorProjectContour.h"
//
//Mat src; Mat src_gray;
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//vector<tuple<Point, Point>> seTuples = *new vector<tuple<Point, Point>>();
//
//int main( int argc, char** argv ) {
//    /// Load source image and convert it to gray
//    src = imread( argv[1], 1 );
//    
//    /// Convert image to gray and blur it
//    cvtColor( src, src_gray, COLOR_BGR2GRAY);
//    //blur( src_gray, src_gray, Size(3,3) );
//    
//    /// Create Window
//    string srcWindow = "Source";
//    //namedWindow( srcWindow, WINDOW_AUTOSIZE );
//    //imshow( srcWindow, src );
//    
//    
//    vector<vector<Point>> contours = getContours(src_gray);
//    vector<ContourRectangleTuple> crTuple = getBoundingRectangles(contours);
//    //crTuple = removeNonRelevantRectangles(crTuple);
//    drawBoundingRectangles(src, crTuple);
//    //    vector<vector<int>> relations = getRelations(crTuple, src.clone());
//    
//    waitKey(0);
//    return(0);
//}
//
//vector<vector<Point>> getContours(Mat image) {
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    Mat dst;
//    
//    GaussianBlur( image, dst, Size(3,3), 0, 0, BORDER_DEFAULT );
////    applySobel(&dst);
//    Canny(dst, dst, 50, 200, 3);
//    //Canny(image, image, 50, 100);
//    
//    vector<Vec4i> lines;
//    HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 3);
//    for( size_t i = 0; i < lines.size(); i++ )
//    {
//        Vec4i l = lines[i];
//        line( dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,255,255), 2, CV_AA);
//    }
//
//    imshow("source", image);
//    imshow("detected lines", dst);
//    
//    waitKey();
//    
//    if(true) exit(0);
//    
//    erode(image, image, Mat());
//    dilate(image, image, Mat());
//    dilate(image, image, Mat());
//    
//    //imshow("canny", image);
//    threshold(image, image, 50, 255, THRESH_BINARY );
//    imshow("sobel", image);
//    findContours(image, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE,Point(0,0));
//    
//    return contours;
//}
//
//void applySobel(Mat* image) {
//    int scale = 1;
//    int delta = 0;
//    int ddepth = CV_16S;
//    /// Generate grad_x and grad_y
//    Mat grad_x, grad_y;
//    Mat abs_grad_x, abs_grad_y;
//    
//    /// Gradient X
//    Sobel( *image, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
//    convertScaleAbs( grad_x, abs_grad_x );
//    
//    /// Gradient Y
//    Sobel( *image, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
//    convertScaleAbs( grad_y, abs_grad_y );
//    
//    /// Total Gradient (approximate)
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, *image );
//}
//
//vector<ContourRectangleTuple> getBoundingRectangles(vector<vector<Point>> contours) {
//    vector<vector<Point> > contoursPoly( contours.size() );
//    vector<ContourRectangleTuple> crTuples = *new vector<ContourRectangleTuple>();
//    vector<Point2f>center( contours.size() );
//    vector<float>radius( contours.size() );
//    
//    for( int i = 0; i < contours.size(); i++ ) {
//        
//        approxPolyDP(Mat(contours[i]),contoursPoly[i],0.2*arcLength(contours[i],true),true);
//        
//        if(contourArea(contours[i])>60){
//            Rect rect = boundingRect( Mat(contoursPoly[i]));
////            if (isContourRelevant(make_tuple(contours[i], rect))) {
//                crTuples.push_back(make_tuple(contours[i], rect));
////            }
//        }
//    }
//    
//    return crTuples;
//}
//
//bool isContourRelevant(ContourRectangleTuple crTuple){
//    Rect rect = get<1>(crTuple);
//    vector<Point> contour = get<0>(crTuple);
//    
//    if((contourArea(contour)/rect.area()) < CONTOUR_RECT_RATIO) {
//        return false;
//    }
//    
//    if(((double)(rect.width + rect.height)/rect.area()) < CIRCUMFERENCE_AREA_RATIO) {
//        return false;
//    }
//    
//    if(((double)rect.width/rect.height) > (1/LINE_ERROR)
//       || ((double)rect.width/rect.height) < (LINE_ERROR)) {
//        return true;
//    }
//    
//    return true;
//}
//
//vector<ContourRectangleTuple> removeNonRelevantRectangles(vector<ContourRectangleTuple> crTuple) {
//    vector<ContourRectangleTuple>  newCrTuple = *new vector<ContourRectangleTuple> ();
//    for (int i = 0; i < crTuple.size(); i++) {
//        bool include = true;
//        Rect r1 = get<1>(crTuple.at(i));
//        
//        //        if(isContourConvex(get<0>(crTuple.at(i)))) {
//        //            continue;
//        //        }
//        
//        //        if(((r1.width/r1.area()) > (1+LINE_ERROR) || (r1.width/r1.area()) < (1-RECT_ERROR))
//        //            && ((r1.height/r1.area()) > (1+LINE_ERROR) || (r1.height/r1.area()) < (1-RECT_ERROR))) {
//        //            continue;
//        //        }
//        
////        if(((double)(r1.width + r1.height)/r1.area()) > 0.2) {
////            continue;
////        }
////        
////        
////        if(fabs(contourArea(get<0>(crTuple.at(i)))) < 50) {
////            continue;
////        }
//        
//        for (int j = 0; j < crTuple.size(); j++) {
//            Rect r2 = get<1>(crTuple.at(j));
//            Rect intersection = r1 & r2;
//            if(intersection.height != 0 && intersection.width != 0) {
//                if (r1.area() > r2.area()) {
//                    include = false;
//                }
//            }
//        }
//        if (include) {
//            newCrTuple.push_back(crTuple.at(i));
//        }
//    }
//    return newCrTuple;
//}
//
//void drawBoundingRectangles(Mat image, vector<ContourRectangleTuple> crTuple) {
//    
//    
//    for( int i = 0; i< crTuple.size(); i++ ) {
//        Rect r = get<1>(crTuple.at(i));
//        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//        rectangle(image, r.tl(), r.br(), color, 2, 8, 0 );
//    }
//    
//    imwrite("images/output.jpg", image);
//    /// Show in a window
//    namedWindow( "Contours", WINDOW_AUTOSIZE );
//    imshow( "Contours", image );
//    
//}
//
//vector<vector<int>> getRelations(vector<ContourRectangleTuple> crTuple, Mat image) {
//    vector<vector<int>> relations = *new vector<vector<int>>();
//    
//    for(int i = 0; i < crTuple.size(); i++) {
//        relations.push_back(getRelatedContours(get<1>(crTuple.at(i)), crTuple, image));
//    }
//    
//    imshow("Matched pips", image);
//    
//    return relations;
//}
//
//
//vector<int> getRelatedContours(Rect r, vector<ContourRectangleTuple> crTuple, Mat image) {
//    vector<int> relatedContours = *new vector<int>();
//    
//    for(int i = 0; i < crTuple.size(); i++) {
//        Rect r2 = get<1>(crTuple.at(i));
//        
//        if (r.x == r2.x && r.y == r2.y) {
//            continue;
//        }
//        
//        if (isRelated(r, get<1>(crTuple.at(i)), image)) {
//            relatedContours.push_back(i);
//        }
//    };
//    
//    return relatedContours;
//}
//
//bool isRelated(Rect r1, Rect r2, Mat image) {
//    tuple<Point, Point> seTuple = getStartEndPoints(r1, r2);
//    
//    Point start = get<0>(seTuple);
//    Point end = get<1>(seTuple);
//    
//    double x = start.x;
//    double y = start.y;
//    
//    int dx = end.x - start.x;
//    int dy = end.y - start.y;
//    
//    int step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
//    
//    double ddx = dx/((double) step);
//    double ddy = dy/((double) step);
//    
//    for (int i = 0; i < step - OVER_STEP; i++) {
//        Vec3b intensity1 = image.at<Vec3b>(y, x);
//        
//        int diff = 0;
//        
//        for (int  j = 0; j < OVER_STEP; j++) {
//            Vec3b intensity2 = image.at<Vec3b>(y + j*ddy, x + j*ddx);
//            
//            diff += abs(intensity1.val[0] - intensity2.val[0]);
//            diff += abs(intensity1.val[1] - intensity2.val[1]);
//            diff += abs(intensity1.val[2] - intensity2.val[2]);
//        }
//        
//        if(diff > TRACE_ERROR){
//            return false;
//        }
//        
//        x += ddx;
//        y += ddy;
//    }
//    
//    line(image, start, end, Scalar(255, 0, 255));
//    return true;
//}
//
//tuple<Point, Point> getStartEndPoints(Rect r1, Rect r2) {
//    Point start, end;
//    if(r1.x > r2.x) {
//        if(r1.y > r2.y) {
//            start = *new Point(r1.x, r1.y);
//            end = *new Point(r2.x + r2.width, r2.y + r2.height);
//        } else {
//            start = *new Point(r1.x, r1.y + r1.height);
//            end = *new Point(r2.x + r2.width, r2.y);
//        }
//    } else {
//        if(r1.y > r2.y) {
//            start = *new Point(r1.x + r1.width, r1.y);
//            end = *new Point(r2.x, r2.y + r2.height);
//        } else {
//            start = *new Point(r1.x + r1.width, r1.y + r1.height);
//            end = *new Point(r2.x, r2.y);
//        }
//    }
//    
//    return make_tuple(start, end);
//}
//
