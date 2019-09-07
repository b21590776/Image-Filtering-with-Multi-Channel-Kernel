#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <numeric>

using namespace std;
using namespace cv;

inline void without_opencv(Mat &image)
{
    Mat tempImage;
    image.copyTo(tempImage);

    vector<float> bilinear;
    bilinear.push_back(1.0/16);
    bilinear.push_back(2.0/16);
    bilinear.push_back(1.0/16);
    bilinear.push_back(2.0/16);
    bilinear.push_back(4.0/16);
    bilinear.push_back(2.0/16);
    bilinear.push_back(1.0/16);
    bilinear.push_back(2.0/16);
    bilinear.push_back(1.0/16);

    vector<float> sobel;
    sobel.push_back(1.0);
    sobel.push_back(0.0);
    sobel.push_back(-1.0);
    sobel.push_back(2.0);
    sobel.push_back(0.0);
    sobel.push_back(-2.0);
    sobel.push_back(1.0);
    sobel.push_back(0.0);
    sobel.push_back(-1.0);

    vector<float> box;
    box.push_back(1.0/9);
    box.push_back(1.0/9);
    box.push_back(1.0/9);
    box.push_back(1.0/9);
    box.push_back(1.0/9);
    box.push_back(1.0/9);
    box.push_back(1.0/9);
    box.push_back(1.0/9);
    box.push_back(1.0/9);


    int imageChannels = image.channels();

    vector<vector<int>> values(imageChannels);

    int halfSize{ 3 / 2 };

    for (int i{ halfSize }; i < tempImage.rows - halfSize; i++)
    {
        for (int j{ halfSize }; j < tempImage.cols - halfSize; j++)
        {
            for (int channel = 0; channel < imageChannels; channel++)
            {
                values[channel].clear();
            }
            for (int x = { -halfSize }; x <= halfSize; x++)
            {
                for (int y = { -halfSize }; y <= halfSize; y++)
                {
                    for (int channel = 0; channel < imageChannels; channel++)
                    {
                        unsigned char * pixelValuePtr = tempImage.ptr(i + x) + ((j + y) * imageChannels) + channel;
                        values[channel].push_back(*pixelValuePtr);
                    }
                }
            }
            for (int channel = 0; channel < imageChannels; channel++)
            {
                vector channelValues = values[channel];
                if( channel == 0 ) {
                    float newPixelValue = inner_product(begin(channelValues), end(channelValues), begin(sobel), 0.0);       //blue channel
                    unsigned char * pixelValuePtr = image.ptr(i) + (j * imageChannels) + channel;
                    *pixelValuePtr = newPixelValue > 255 ? 255 : newPixelValue < 0 ? 0 : newPixelValue;
                }
                if( channel == 1 ) {
                    float newPixelValue = inner_product(begin(channelValues), end(channelValues), begin(bilinear), 0.0);   //green channel
                    unsigned char * pixelValuePtr = image.ptr(i) + (j * imageChannels) + channel;
                    *pixelValuePtr = newPixelValue > 255 ? 255 : newPixelValue < 0 ? 0 : newPixelValue;
                }
                if( channel == 2 ) {
                    float newPixelValue = inner_product(begin(channelValues), end(channelValues), begin(box), 0.0);        //red channel
                    unsigned char * pixelValuePtr = image.ptr(i) + (j * imageChannels) + channel;
                    *pixelValuePtr = newPixelValue > 255 ? 255 : newPixelValue < 0 ? 0 : newPixelValue;
                }
            }
        }
    }
}