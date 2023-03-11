#include <QApplication>
#include <QDir>
#include "ConverQimageOrCvMat.h"
#include <opencv2/opencv.hpp>

int main( int argc, char *argv[] ) {
	auto winname = "color";
	auto imgName = "./1.png";
	// 原始图片
	cv::Mat img = cv::imread(QString(imgName).toLocal8Bit().toStdString(), cv::IMREAD_UNCHANGED);
	if( img.empty() )
		return -1;
	cv::namedWindow(winname, cv::WINDOW_NORMAL);
	cv::imshow(winname, img);

	auto outImg = img.clone();
	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(img, outImg, img.depth(), kernel);
	
	cv::namedWindow("outImg", cv::WINDOW_NORMAL);
	cv::imshow("outImg", outImg);
	cv::waitKey();

	cv::destroyAllWindows();
	return 0;
}