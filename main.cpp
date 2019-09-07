#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <numeric>
#include "without_opencv.cpp"
#include "with_opencv.cpp"
#include <cstdio>
#include <ctime>

using namespace std;
using namespace cv;

int main(int argc, char** argv ) {
    Mat img, result1,result2;

    img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!img.data)
        return -1;

// ------------------------------------------without-opencv--------------------------------------------
    result1 = img.clone();
    clock_t start;
    double duration;
    start = clock();

    without_opencv(result1);

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"time without using opencv: "<< duration <<'\n';

// ------------------------------------with-opencv--------------------------------------------------------
    result2 = img.clone();
    clock_t start1;
    double duration1;
    start1 = clock();

    result2 = with_opencv(result2);


    duration1 = ( clock() - start1 ) / (double) CLOCKS_PER_SEC;
    cout<<"time with opencv: "<< duration1 <<'\n';

//------------------------------------------------------------------------------------------------
//    cvtColor( result1, result1,  CV_BGR2RGB );

    imwrite("part2_without_opencv.jpg",  result1);
    imwrite("part2_with_opencv.jpg",  result2);


    namedWindow("original image");
    imshow("original image", img);
    waitKey(0);

    namedWindow("without opencv");
    imshow("without opencv", result1);
    waitKey(0);

    namedWindow("with opencv");
    imshow("with opencv", result2);
    waitKey(0);

    return 0;
}