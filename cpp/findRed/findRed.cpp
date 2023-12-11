/*
   Codigo para filtrar el clor rojo en una imagen con opencv en formato HSV.

*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat redFilter(const Mat& src, bool show = false){

	assert(src.type() == CV_8UC3);

	Mat mask, mask0, mask1, redOnly;

	Mat img_hsv;
	cvtColor(src, img_hsv, COLOR_BGR2HSV);

	//lower mask (0-10)
	inRange(img_hsv, Scalar(0, 150, 150), Scalar(3, 255, 255), mask0);

	//upper mask (170-180)
	inRange(img_hsv, Scalar(175, 100, 100), Scalar(180, 255, 255), mask1);

	//join my masks
	bitwise_or(mask0, mask1, mask);

	// Create a structuring element 
	int morph_size = 2; 
	Mat element = getStructuringElement( MORPH_RECT, 
			Size(2 * morph_size + 1, 2 * morph_size + 1), 
			Point(morph_size, morph_size)); 
	morphologyEx(mask, mask, MORPH_CLOSE, element, Point(-1, -1), 2); 

	morph_size = 1;
	element = getStructuringElement( MORPH_RECT, 
			Size(2 * morph_size + 1, 2 * morph_size + 1), 
			Point(morph_size, morph_size)); 
	morphologyEx(mask, mask, MORPH_OPEN, element, Point(-1, -1), 2); 
	

	if(show){
		imshow("mask", mask);
		Mat redOnly;
		bitwise_and(src, src, redOnly, mask);
		imshow("maskRed", redOnly);
	}

	return mask;
}

int main(int argc, char** argv){
   
	if ( argc != 2 ){
		printf("uso: %s <Image_Path>\n", argv[0]);
		return -1;
	}
	Mat input = imread( argv[1], IMREAD_COLOR );
	imshow("input", input);

	Mat maskRedOnly = redFilter(input, true);

	// buscar contornos en la imagen binaria
	vector< vector<Point> > contours;
	findContours(maskRedOnly, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	// dibujar todos los contornos encontrados
	drawContours(input, contours, -1, Scalar(255), FILLED);

	// dibujar rectangulo y texto con coordenadas (x, y)
	for (vector<Point> contour : contours) {
		Rect r = boundingRect(contour);
		rectangle(input, r.tl(), r.br(), CV_RGB(255, 0, 0), 2, LINE_AA, 0);

		Point center(r.x + (r.width / 2), r.y + (r.height / 2));

		ostringstream str;
		str << "[" << contourArea(contour) << "]" << center.x << "," << center.y;

		putText(input, str.str(), center, FONT_HERSHEY_COMPLEX_SMALL, 0.60, CV_RGB(0, 255, 0), 1, LINE_AA);
	}

	imshow("redOnly", input);
	waitKey();

	destroyAllWindows();

	return 0;
}

