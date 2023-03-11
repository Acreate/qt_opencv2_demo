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

	auto outImg = img.clone();
	cv::Mat_<char> mat = cv::Mat_<char>(3, 3);
	cv::Mat kernel = (mat << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(img, outImg, img.depth(), kernel);
	cv::Mat m2 = cv::Mat::eye(100, 100, CV_8UC1);
	cv::namedWindow("outImg", cv::WINDOW_NORMAL);
	cv::imshow("outImg", outImg);
	
	cv::Mat demo001(img.rows, img.cols, img.type());

	cv::namedWindow("demo001", cv::WINDOW_NORMAL);
	cv::imshow("demo001", demo001);

	auto demo002 = img.clone();
	cv::namedWindow("demo002", cv::WINDOW_NORMAL);
	cv::imshow("demo002", demo002);

	cv::Mat demo003;
	img.copyTo(demo003);
	cv::namedWindow("demo003", cv::WINDOW_NORMAL);
	cv::imshow("demo003", demo003);


	cv::waitKey();

	cv::destroyAllWindows();
	return 0;
}