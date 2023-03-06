#include <QApplication>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ConverQimageOrCvMat.h>

int main( int argc, char *argv[] ) {
	QApplication a(argc, argv);
	QLabel label;

	cv::Mat readImage = cv::imread("test.jpg");
	cv::imshow("opencvConvertImage", readImage);
	QImage image = ConverQimageOrCvMat::conver(readImage);
	label.setPixmap(QPixmap::fromImage(image));
	label.show();
	return a.exec();
}