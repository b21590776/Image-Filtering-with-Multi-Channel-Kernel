#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

inline Mat with_opencv(Mat img) {
    if (!img.data) { return img; }

    Mat bgr[3],temp[3];
    split(img,bgr);
    split(img,temp);


    Mat sobel;                                                          //blue channel
    sobel = (Mat_<float>(3,3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);
    filter2D( temp[0], bgr[0],  -1, sobel, Point(-1, -1), 0, BORDER_DEFAULT);

    Mat bilinear;                                                       //green channel
    bilinear = (Mat_<float>(3,3) << 1 / 16.0, 2 / 16.0, 1 / 16.0, 2 / 16.0, 4 / 16.0, 2 / 16.0, 1 / 16.0, 2 / 16.0, 1 / 16.0);
    filter2D( temp[1], bgr[1],  -1, bilinear, Point(-1, -1), 0, BORDER_DEFAULT);

    Mat box;                                                            //red channel
    box = Mat::ones( 3, 3, CV_32F )/ (float)(3*3);
    filter2D( temp[2], bgr[2],  -1, box, Point(-1, -1), 0, BORDER_DEFAULT);

    Mat output;
    merge(bgr,3,output);

    return output;
}