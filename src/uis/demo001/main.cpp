#include <QApplication>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

int main( int argc, char *argv[] ) {
	QApplication a(argc, argv);


	QLabel label;

	cv::Mat readImage = cv::imread("test.jpg");
	cv::cvtColor(readImage, readImage, CV_BGR2RGB);
	QImage image(readImage.data, readImage.cols, readImage.rows, readImage.step, QImage::Format_RGB888);
	QPixmap pixmap = QPixmap::fromImage(image);
	label.setPixmap(pixmap);

	QImage convertToFormat = image.convertToFormat(QImage::Format_RGB888);
	cv::Mat mat = cv::Mat(convertToFormat.height(), convertToFormat.width(), CV_8UC3, convertToFormat.bits(), convertToFormat.bytesPerLine());
	cv::cvtColor(mat, mat, CV_RGB2BGR);
	cv::imshow("opencvConvertImage", mat);
	label.show();
	return a.exec();
}