#include <QApplication>
#include <QDir>
#include "ConverQimageOrCvMat.h"
#include <opencv2/opencv.hpp>
#include <sstream>
void showImg( const QString &name, const cv::Mat &mulImg );
void myLine( cv::Mat &img );
void myRectangle( cv::Mat &img );
void myEllipse( cv::Mat &img );

int main( int argc, char *argv[] ) {
	QGuiApplication app(argc, argv);
	auto imgName1 = "./1.png";
	// 原始图片
	cv::Mat img1 = cv::imread(QString(imgName1).toLocal8Bit().toStdString(), cv::IMREAD_UNCHANGED);
	if( img1.empty() )
		return -1;
	showImg("input_image", img1);
	myLine(img1);
	showImg("muLin1", img1);
	myRectangle(img1);
	showImg("myRectangle", img1);
	myEllipse(img1);
	showImg("myEllipse", img1);
	cv::waitKey();
	cv::destroyAllWindows();
	return 0;
}

void showImg( const QString &name, const cv::Mat &mulImg ) {
	std::string winname = name.toLocal8Bit().toStdString();
	cv::namedWindow(winname, cv::WINDOW_NORMAL);
	cv::imshow(winname, mulImg);
}

void myLine( cv::Mat &img ) {
	cv::Point p1 = cv::Point(20, 30);
	cv::Point p2;
	p2.x = 300;
	p2.y = 300;
	cv::Scalar color = cv::Scalar(0, 0, 255);
	cv::line(img, p1, p2, color, 1, cv::LINE_8);
}

void myRectangle( cv::Mat &img ) {
	cv::Rect rect = cv::Rect(50, 50, 50, 50);
	cv::Scalar color(255, 0, 0);
	cv::rectangle(img, rect, color, 2, cv::LINE_4);
}

void myEllipse( cv::Mat &img ) {
	cv::ellipse(
		// 绘制目标
		img,
		// 中心坐标
		cv::Point(img.cols / 2, img.rows / 2),
		// 给与矩形当中
		// 水平(img.cols / 4)长度
		// 垂直(img.rows / 8)长度
		cv::Size(img.cols / 2, img.rows / 8),
		// 角度
		0,
		// 开始绘制的角度
		0,
		// 结束绘制的角度
		360,
		// 绘制颜色
		cv::Scalar(0, 255, 0),
		// 绘制宽度
		2,
		// 线条类型
		cv::LINE_AA);
}