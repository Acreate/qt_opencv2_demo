#include <QApplication>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>

int main( int argc, char *argv[] ) {

	cv::namedWindow("video", cv::WINDOW_NORMAL);
	cv::resizeWindow("video", 640, 480);
	auto cap = cv::VideoCapture(0);
	cv::Mat outMat;
	while( cap.read(outMat) ) {
		cv::imshow("video", outMat);
		int key = cv::waitKey(1);
		if( key & 0xff == 'q' )
			break;
	}
	return 0;
}