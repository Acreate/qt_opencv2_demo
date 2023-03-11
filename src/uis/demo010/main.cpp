#include <QApplication>
#include <QDir>
#include "ConverQimageOrCvMat.h"
#include <opencv2/opencv.hpp>
#include <sstream>

int main( int argc, char *argv[] ) {
	QGuiApplication app(argc, argv);
	auto winname = "color";
	auto imgName = "./1.png";
	// 原始图片
	cv::Mat img = cv::imread(QString(imgName).toLocal8Bit().toStdString(), cv::IMREAD_UNCHANGED);
	if( img.empty() )
		return -1;
	cv::namedWindow(winname, cv::WINDOW_NORMAL);
	cv::imshow(winname, img);

	// 3~4通道
	for( decltype(img.rows) row = 0; row < img.rows; ++row )
		for( decltype(img.cols) col = 0; col < img.cols; ++col ) {
			auto &color = img.at<cv::Vec3b>(row, col);
			color[0] = 255 - color[0];
			color[1] = 255 - color[1];
			color[2] = 255 - color[2];
		}

	cv::namedWindow("img", cv::WINDOW_NORMAL);
	cv::imshow("img", img);
	// 单通道
	cv::Mat outImg;
	cv::cvtColor(img, outImg, cv::COLOR_BGRA2GRAY);
	cv::namedWindow("outImg", cv::WINDOW_NORMAL);
	cv::imshow("outImg", outImg);
	auto height = outImg.rows;
	auto width = outImg.cols;
	for( decltype(height) row = 0; row < height; ++row )
		for( decltype(width) col = 0; col < width; ++col ) {
			auto &gray = outImg.at<uchar>(row, col);
			gray = 255 - gray;
		}

	cv::namedWindow("outImg2", cv::WINDOW_NORMAL);
	cv::imshow("outImg2", outImg);

	cv::waitKey();

	cv::destroyAllWindows();
	return 0;
}