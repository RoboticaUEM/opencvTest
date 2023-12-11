/*
   Codigo para filtrar el clor rojo en una imagen con opencv en formato HSV.

*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv){

	if ( argc != 2 ){
		cerr << "uso: " << argv[0] << " <Video_Path>" << endl;
		return -1;
	}

	VideoCapture cap;
	cap.open(argv[1]);
	if ( !cap.isOpened() ) {
		cerr << "couldn't open video: " << argv[1] << endl;
		return -1;
	}

	namedWindow( "Video", WINDOW_NORMAL | WINDOW_KEEPRATIO );
	setWindowProperty( "Video", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	resizeWindow( "Video", 1920, 1200);

	Mat frame;
	char c = 'a';
	int estado = 2;
	int nFrame = 0;
	Point pos(10, 20);

	cout << "Press 'q' for exit!" << endl;
	while( c != 'q' ) {
		cap >> frame;
		if( frame.empty( ) ) break;
		
		ostringstream str;
		str << "[" << nFrame << "]";
		putText(frame, str.str(), pos, FONT_HERSHEY_COMPLEX_SMALL, 1, CV_RGB(0, 255, 0), 1, LINE_AA);
		nFrame++;

		imshow("Video", frame);
		switch(estado) {
			case 1:
				c = waitKey(1);
				break;
			case 2:
				c = waitKey(30);
				break;
			case 3:
				c = waitKey(200);
				break;
			default:
				c = waitKey();
		}
		switch(c) {
			case ' ':
				estado = 0;
				break;
			case '1':
				estado = 1;
				break;
			case '2':
				estado = 2;
				break;
			case '3':
				estado = 3;
				break;
		}
	}

	destroyAllWindows();

	return 0;
}

