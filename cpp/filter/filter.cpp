/*
  Codigo para filtrar el clor rojo en una imagen con opencv en formato HSV.

*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat redFilter(const Mat& src)
{
    assert(src.type() == CV_8UC3);

    Mat mask, mask0, mask1, redOnly;
    
    Mat img_hsv;
    cvtColor(src, img_hsv, COLOR_BGR2HSV);

    //lower mask (0-10)
    inRange(img_hsv, Scalar(0, 150, 150), Scalar(3, 255, 255), mask0);

    //upper mask (170-180)
    inRange(img_hsv, Scalar(175, 150, 150), Scalar(180, 255, 255), mask1);

    //join my masks
    bitwise_or(mask0, mask1, mask);
    imshow("mask", mask);
    
    //                  B  G  R
    //inRange(src, Scalar(0, 0, 100), Scalar(50, 50, 255), mask);
    bitwise_and(src, src, redOnly, mask);

    return redOnly;
}

int main(int argc, char** argv)
{   
    if ( argc != 2 )
    {
        printf("uso: %s <Image_Path>\n", argv[0]);
        return -1;
    }
    Mat input = imread( argv[1], IMREAD_COLOR );

    imshow("input", input);

    Mat redOnly = redFilter(input);
    
    // Create a structuring element 
    int morph_size = 2; 
    Mat element = getStructuringElement( MORPH_RECT, 
        Size(2 * morph_size + 1, 2 * morph_size + 1), 
        Point(morph_size, morph_size)); 

    Mat output;   
    // Opening 
    morphologyEx(redOnly, output, MORPH_CLOSE, element, Point(-1, -1), 2); 
    
    morph_size = 1;
    element = getStructuringElement( MORPH_RECT, 
        Size(2 * morph_size + 1, 2 * morph_size + 1), 
        Point(morph_size, morph_size)); 
    morphologyEx(output, output, MORPH_OPEN, element, Point(-1, -1), 2); 

    imshow("redOnly", output);
    waitKey();

    // detect squares after filtering...

    return 0;
}
