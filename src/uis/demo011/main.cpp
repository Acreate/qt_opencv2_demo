#include <QApplication>
#include <QDir>
#include "ConverQimageOrCvMat.h"
#include <opencv2/opencv.hpp>
#include <sstream>

void showImg( const QString &name, const cv::Mat &mulImg ) {
	std::string winname = name.toLocal8Bit().toStdString();
	cv::namedWindow(winname, cv::WINDOW_NORMAL);
	cv::imshow(winname, mulImg);
}

int main( int argc, char *argv[] ) {
	QGuiApplication app(argc, argv);
	auto imgName1 = "./1.png";
	// 原始图片
	cv::Mat img1 = cv::imread(QString(imgName1).toLocal8Bit().toStdString(), cv::IMREAD_UNCHANGED);
	if( img1.empty() )
		return -1;
	showImg("input_image", img1);

	int height = img1.rows;
	int width = img1.cols;
	double beta = 100,
		alpha = 0.2;
	cv::Mat des = cv::Mat(cv::Size(width, height), img1.type());
	cv::Mat conver;
	int channels = img1.channels();
	if( channels == 3 ) {
		img1.convertTo(conver, CV_64FC3);
	} else if( channels == 4 ) {
		img1.convertTo(conver, CV_64FC4);
	}
	for( int row = 0; row < height; ++row ) {
		for( int col = 0; col < width; ++col ) {
			if( channels == 3 ) {
				auto &srcVec = conver.at<cv::Vec3d>(row, col);
				auto &desVec = des.at<cv::Vec3b>(row, col);
				double b = srcVec[0], g = srcVec[1], r = srcVec[2];

				desVec[0] = cv::saturate_cast<uchar>(b * alpha + beta);
				desVec[1] = cv::saturate_cast<uchar>(g * alpha + beta);
				desVec[2] = cv::saturate_cast<uchar>(r * alpha + beta);
			} else if( channels == 4 ) {
				auto &srcVec = conver.at<cv::Vec4d>(row, col);
				double b = srcVec[0], g = srcVec[1], r = srcVec[2];
				auto &desVec = des.at<cv::Vec4b>(row, col);
				desVec[0] = cv::saturate_cast<uchar>(b * alpha + beta);
				desVec[1] = cv::saturate_cast<uchar>(g * alpha + beta);
				desVec[2] = cv::saturate_cast<uchar>(r * alpha + beta);
			} else if( channels == 1 ) {
				des.at<uchar>(row, col) = cv::saturate_cast<uchar>(img1.at<uchar>(row, col) * alpha + beta);
			}
		}
	}

	showImg("out_image", des);

	cv::waitKey();
	cv::destroyAllWindows();
	return 0;
}