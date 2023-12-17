/*
   Codigo para filtrar el clor rojo en una imagen con opencv en formato HSV.

*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

//using json = nlohmann::json;        //Json ordenado
using json = nlohmann::ordered_json;   //Json no ordenado.
using namespace std;
using namespace cv;

Mat colorFilter(const Mat& src, int hueMin, int hueMax, bool show = false){

	assert(src.type() == CV_8UC3);

	Mat mask;
	Mat img_hsv;
	
	cvtColor(src, img_hsv, COLOR_BGR2HSV);

	//mask
	inRange(img_hsv, Scalar(hueMin, 80, 80), Scalar(hueMax, 255, 255), mask);

	// Create a structuring element 
	int morph_size = 2; 
	Mat element = getStructuringElement( MORPH_RECT, 
			Size(2 * morph_size + 1, 2 * morph_size + 1), 
			Point(morph_size, morph_size)); 
	morphologyEx(mask, mask, MORPH_CLOSE, element, Point(-1, -1), 2); 
	morphologyEx(mask, mask, MORPH_OPEN, element, Point(-1, -1), 2); 

	if(show){
		imshow("mask", mask);
		imshow("img_hsv", img_hsv);
		Mat colorOnly;
		bitwise_and(src, src, colorOnly, mask);
		imshow("colorOnly", colorOnly);
	}

	return mask;
}

json contoursToJson(vector< vector<Point> > contours){
	json region, regions;

	// dibujar rectangulo y texto con coordenadas (x, y)
	for (vector<Point> contour : contours) {
		Rect r = boundingRect(contour);
		region.clear();
		region["center"] = {r.x + (r.width / 2), r.y + (r.height / 2)};
		region["size"] = {r.width, r.height};
		region["area"] = contourArea(contour);
		
		regions.push_back(region);
	}
	return regions;
}

int main(int argc, char** argv){

	/*
	VideoCapture cap;
	cap.open(0);
	if ( !cap.isOpened() ) {
		cerr << "couldn't open video: 0" << endl;
		return -1;
	}
	*/

	//cap.set(CAP_PROP_FRAME_WIDTH, 1280);
	//cap.set(CAP_PROP_FRAME_HEIGHT, 1024);

	namedWindow( "Video", WINDOW_NORMAL | WINDOW_KEEPRATIO );
	//setWindowProperty( "Video", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	//resizeWindow( "Video", 1920, 1200);

	Mat input;
	Mat mask1, mask2;
	char c = 'a';
	json yelow, blue, image;
	


	cout << "Press [space] for exit!" << endl;
	while( c != ' ' ) {
		image.clear();
		//cap >> input;
		input = imread("yelow1.jpg", IMREAD_COLOR);
		if( input.empty( ) ) break;
		image["imageSize"]["width"] = input.size[1];
		image["imageSize"]["height"] = input.size[0];

		mask1 = colorFilter(input, 210/2, 250/2, false); //Blue
		mask2 = colorFilter(input, 48/2, 58/2, false);  //Yelow

		// buscar contornos en la imagen binaria
		vector< vector<Point> > contours1;
		findContours(mask1, contours1, RETR_LIST, CHAIN_APPROX_SIMPLE);
		blue = contoursToJson(contours1);
		vector< vector<Point> > contours2;
		findContours(mask2, contours2, RETR_LIST, CHAIN_APPROX_SIMPLE);
		yelow = contoursToJson(contours2);
		image["rois"] = yelow.size() + blue.size();
		image["blue"] = blue;
		image["yelow"] = yelow;
		cout << "Image: " << image << endl;
		cout << "================================================================================" << endl << endl;
		imshow("Video", input);
		c = waitKey(200);
	}

	destroyAllWindows();

	return 0;
}

