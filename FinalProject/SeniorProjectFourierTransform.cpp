//
//  FourierTransform.cpp
//  Senior Project
//
//  Created by Celebi Murat on 07/04/15.
//  Copyright (c) 2015 Celebi Murat. All rights reserved.
//

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

void swapQuadrants(Mat mat);

void zeroQuadrants(Mat mat, int width, int height);

void lowPassFilter(Mat planes[]);

void baseBandFilter(Mat planes[]);

int main(int argc, char **argv) {
    const char *filename = argc >= 2 ? argv[1] : "Pictures/shelf1.jpg";

    Mat I = imread(filename, IMREAD_GRAYSCALE);
    if (I.empty())
        return -1;

    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize(I.rows);
    int n = getOptimalDFTSize(I.cols); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zero

    dft(complexI, complexI);// this way the result may fit in the source matrix


    split(complexI, planes);


    lowPassFilter(planes);
    //baseBandFilter(planes);


    Mat magIClone = planes[0].clone();


    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude

    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));


    swapQuadrants(magI);

    normalize(magI, magI, 0, 1, NORM_MINMAX);
    // Transform the matrix with float values into a
    // viewable image form (float between values 0 and 1).

    imshow("Input Image", I);    // Show the result
    imshow("spectrum magnitude", magI);
    waitKey();

    vector<Mat> channels;
    //reverse

    channels.push_back(magIClone);
    channels.push_back(planes[1]);


    Mat temp;
    merge(channels, temp);

    cv::Mat inverseTransform;
    cv::dft(temp, inverseTransform, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);

    normalize(inverseTransform, inverseTransform, 0, 1, NORM_MINMAX);

    imshow("Reconstructed", inverseTransform);

    waitKey();


    return 0;
}

void swapQuadrants(Mat mat) {

    int cx = mat.cols / 2;
    int cy = mat.rows / 2;

    Mat q0(mat, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(mat, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(mat, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(mat, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);
}


void zeroQuadrants(Mat mat, int width, int height) {
    double value = 0;

    int cx = mat.cols / 2;
    int cy = mat.rows / 2;

    Mat q0(mat, Rect(0, 0, width, height));   // Top-Left - Create a ROI per quadrant
    Mat q1(mat, Rect(cx * 2 - width, cy * 2 - height, width, height));  // Top-Right
    Mat q2(mat, Rect(cx * 2 - width, 0, width, height));  // Bottom-Left
    Mat q3(mat, Rect(0, cy * 2 - height, width, height)); // Bottom-Right

    q0.setTo(value);
    q1.setTo(value);
    q2.setTo(value);
    q3.setTo(value);

}

void lowPassFilter(Mat planes[]) {
    zeroQuadrants(planes[0], 60, 60);
    zeroQuadrants(planes[1], 60, 60);
}

void baseBandFilter(Mat planes[]){

    swapQuadrants(planes[0]);
    swapQuadrants(planes[1]);

    circle(planes[0], Point(planes[0].cols/2,planes[0].rows/2), 150, Scalar(0), 150, 8, 0);
    circle(planes[1], Point(planes[1].cols/2,planes[1].rows/2), 150, Scalar(0), 150, 8, 0);

    swapQuadrants(planes[0]);
    swapQuadrants(planes[1]);

}
