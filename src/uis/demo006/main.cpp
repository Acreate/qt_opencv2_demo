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
	cv::namedWindow("winname2", cv::WINDOW_NORMAL);

	cv::imshow(winname, img);

	cv::Mat convMat;
	cv::cvtColor(img, convMat, cv::COLOR_BGR2GRAY);
	cv::imshow("winname2", convMat);
	cv::imwrite(QString("吃瓜1.png").toLocal8Bit().toStdString(), img,{cv::IMWRITE_PNG_COMPRESSION, 9});
	cv::imwrite(QString("吃瓜2.png").toLocal8Bit().toStdString(), img,{cv::IMWRITE_PNG_COMPRESSION, 0});
	cv::waitKey();

	cv::destroyAllWindows();
	return 0;
}