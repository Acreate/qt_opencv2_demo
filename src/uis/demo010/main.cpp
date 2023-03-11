#include <QApplication>
#include <QDir>
#include "ConverQimageOrCvMat.h"
#include <opencv2/opencv.hpp>
#include <sstream>

int main( int argc, char *argv[] ) {
	QGuiApplication app(argc, argv);
	auto imgName1 = "./1.png",
		imgName2 = "./2.png";
	// 原始图片
	cv::Mat img1 = cv::imread(QString(imgName1).toLocal8Bit().toStdString(), cv::IMREAD_UNCHANGED);
	if( img1.empty() )
		return -1;

	cv::Mat img2 = cv::imread(QString(imgName2).toLocal8Bit().toStdString(), cv::IMREAD_UNCHANGED);
	if( img2.empty() )
		return -1;


	cv::namedWindow(imgName1, cv::WINDOW_NORMAL);
	cv::imshow(imgName1, img1);
	cv::namedWindow(imgName2, cv::WINDOW_NORMAL);
	cv::imshow(imgName2, img2);

	int type1 = img1.type();
	int type2 = img2.type();
	cv::Mat out1 = img1.clone(), out2 = img2.clone(), merge;
	if( type2 != type1 ) {
		img1.convertTo(out1, type1);
		img2.convertTo(out2, type1);
	}
	cv::MatStep matStep1 = out1.step;
	cv::MatStep matStep2 = out2.step;
	if( matStep1.buf[1] != matStep2.buf[1] ) {
		cv::cvtColor(out2, out2, cv::COLOR_BGR2BGRA);
	}
	cv::Size newSize1 = cv::Size(out1.cols, out1.rows);
	cv::Size newSize2 = cv::Size(out2.cols, out2.rows);
	cv::resize(out1, out1, newSize1, 0, 0, cv::INTER_NEAREST);
	cv::resize(out2, out2, newSize1, 0, 0, cv::INTER_NEAREST);
	double alpha = 0.5;
	cv::addWeighted(out1, alpha, out2, (1.0 - alpha), 0, merge);
	cv::namedWindow("merge", cv::WINDOW_NORMAL);
	cv::imshow("merge", merge);

	cv::imwrite("merge1.png", out1, {cv::IMWRITE_PNG_COMPRESSION, 9});
	cv::imwrite("merge2.png", out2, {cv::IMWRITE_PNG_COMPRESSION, 9});
	cv::imwrite("merge_result.png", merge, {cv::IMWRITE_PNG_COMPRESSION, 9});
	// 相加
	cv::Mat  addImg;
	cv::add(out1, out2, addImg);
	cv::namedWindow("addImg", cv::WINDOW_NORMAL);
	cv::imshow("addImg", addImg);
	cv::imwrite("addImg_result.png", addImg, {cv::IMWRITE_PNG_COMPRESSION, 9});
	// 相乘
	cv::Mat  mulImg;
	cv::multiply(out1, out2, mulImg);
	cv::namedWindow("mulImg", cv::WINDOW_NORMAL);
	cv::imshow("mulImg", mulImg);
	cv::imwrite("mulImg_result.png", mulImg, {cv::IMWRITE_PNG_COMPRESSION, 9});
	cv::waitKey();

	cv::destroyAllWindows();
	return 0;
}