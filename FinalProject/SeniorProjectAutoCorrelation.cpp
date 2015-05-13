//
// Created by Umut Uzgur on 12/04/15.
//

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

double calculateAutoCorrelationReg(int y, int x, Mat *I);


int main(int argc, char ** argv){
    const char* filename = argc >=2 ? argv[1] : "Pictures/shelf5.jpg";

    Mat I = imread(filename, IMREAD_GRAYSCALE);
    if( I.empty())
        return -1;
    Mat result = Mat::zeros(I.rows,I.cols,CV_64FC1);

    for (int y = 0; y < I.rows; ++y) {
        for (int x = 0; x < I.cols; ++x) {
            result.at<double>(y,x) = calculateAutoCorrelationReg(y,x,&I);
        }
        //cout << y << endl;

    }

    cout << "Finished";
    normalize(result, result, 0, 8, NORM_MINMAX);
    imshow("Input",I);
    imshow("Result", result);
    waitKey();


}

double calculateAutoCorrelationReg(int y, int x, Mat *I) {
    double total = 0;
    for (int y1 = -y; y1 < I->rows-y; ++y1) {
        for (int x1 = -x; x1 < I->cols-x; ++x1) {
            total += I->at<char>((y+y1)+y,(x+x1)+2*x) * I->at<char>(y1+y,x1+x);
        }
        //cout << y1 << endl;

    }
    //cout << total << endl;



    //
    return total;
}