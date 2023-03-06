#include "ConverQimageOrCvMat.h"
#include <opencv2/imgproc/types_c.h>


QImage ConverQimageOrCvMat::conver( const cv::Mat &cvMat ) {
	int channels = cvMat.channels();
	qint64 inBytes = cvMat.cols * cvMat.rows * channels;
	uchar *data = cvMat.data;
	size_t elemSize = cvMat.elemSize() / channels;// 单个元素的大小
	if( elemSize == sizeof(uint8_t) ) {
		uint8_t *bits = new uint8_t[inBytes];
		if( channels == 4 ) {
			copyRGBA2BGRA_8bit(cvMat.data, bits, inBytes);
			return QImage(bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGBA8888);
		}
		if( channels == 3 ) {
			copyRGB2BGR_8bit(cvMat.data, bits, inBytes);
			return QImage(bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGB888);
		}
		if( channels < 3 ) {
			copyData2CloneData_8bit(cvMat.data, bits, inBytes);
			if( channels == 2 )
				return QImage(bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_Grayscale8);
			if( channels == 1 )
				return QImage(bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_Alpha8);
		}
	} else if( elemSize == sizeof(uint16_t) ) {
		uint16_t *bits = new uint16_t[inBytes];
		if( channels == 4 ) {
			copyRGBA2BGRA_16bit((uint16_t *)cvMat.data, bits, inBytes);
			return QImage((uchar *)bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGBA16FPx4);
		}
		if( channels == 3 ) {
			copyRGB2BGR_16bit((uint16_t *)cvMat.data, bits, inBytes);
			return QImage((uchar *)bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGB16);
		}
		if( channels == 2 ) {
			copyData2CloneData_16bit((uint16_t *)cvMat.data, bits, inBytes);
			return QImage((uchar *)bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_Grayscale16);
		}

	} else if( elemSize == sizeof(uint32_t) ) {
		uint32_t *bits = new uint32_t[inBytes];
		if( channels == 4 ) {
			copyRGBA2BGRA_32bit((uint32_t *)cvMat.data, bits, inBytes);
			return QImage((uchar *)bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGBA32FPx4);
		}
		if( channels == 3 ) {
			copyRGB2BGR_32bit((uint32_t *)cvMat.data, bits, inBytes);
			return QImage((uchar *)bits, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGB16);
		}
	}

	return QImage();
}

cv::Mat ConverQimageOrCvMat::conver( const QImage &qtImage ) {
	QImage currnetImage = qtImage;
	currnetImage = currnetImage.convertToFormat(QImage::Format_RGB888);
	int channels = 0;
	QImage::Format format = currnetImage.format();
	int typeFlage = 0;
	switch( format ) {
	case QImage::Format_RGBX32FPx4 :
	case QImage::Format_RGBA32FPx4 :
		typeFlage = CV_32FC4;
		channels = 4;
		break;
	case QImage::Format_RGBA16FPx4 :
		typeFlage = CV_16FC4;
		channels = 4;
		break;
	case QImage::Format_RGB16 :
		typeFlage = CV_16UC3;
		channels = 3;
		break;
	case QImage::Format_RGB888 :
		typeFlage = CV_8UC3;
		channels = 3;
		break;
	case QImage::Format_Grayscale16 :
		typeFlage = CV_16UC1;
		channels = 1;
		break;
	case QImage::Format_Grayscale8 :
	case QImage::Format_Alpha8 :
		typeFlage = CV_8UC1;
		channels = 1;
		break;
	default :
		currnetImage = currnetImage.convertToFormat(QImage::Format_RGBA32FPx4);
		typeFlage = CV_32SC4;
		channels = 4;
		break;
	}

	// 转换到标准 rgb/rgba 格式
	int width = currnetImage.width(),
		height = currnetImage.height();
	size_t inBytes = currnetImage.sizeInBytes();
	size_t imageSize = width * height;
	size_t colorSize = inBytes / imageSize / channels;

	qint64 step = currnetImage.bytesPerLine();
	const uchar *destData = currnetImage.constBits();
	if( colorSize == sizeof(uint8_t) ) {
		uint8_t *bits = new uint8_t[inBytes];
		if( channels == 4 ) {
			copyRGBA2BGRA_8bit(destData, bits, inBytes);
			return cv::Mat(height, width, typeFlage, bits, step);
		}
		if( channels == 3 ) {
			copyRGB2BGR_8bit(destData, bits, inBytes);
			return cv::Mat(height, width, typeFlage, bits, step);
		}
		if( channels < 3 ) {
			copyData2CloneData_8bit(destData, bits, inBytes);
			if( channels == 2 )
				return cv::Mat(height, width, typeFlage, bits, step);
			if( channels == 1 )
				return cv::Mat(height, width, typeFlage, bits, step);
		}
	} else if( colorSize == sizeof(uint16_t) ) {
		uint16_t *bits = new uint16_t[inBytes];
		if( channels == 4 ) {
			copyRGBA2BGRA_16bit((uint16_t *)destData, bits, inBytes);
			return cv::Mat(height, width, typeFlage, bits, step);
		}
		if( channels == 3 ) {
			copyRGB2BGR_16bit((uint16_t *)destData, bits, inBytes);
			return cv::Mat(height, width, typeFlage, bits, step);
		}
		if( channels == 2 ) {
			copyData2CloneData_16bit((uint16_t *)destData, bits, inBytes);
			return cv::Mat(height, width, typeFlage, bits, step);
		}

	} else if( colorSize == sizeof(uint32_t) ) {
		uint32_t *bits = new uint32_t[inBytes];
		if( channels == 4 ) {
			copyRGBA2BGRA_32bit((uint32_t *)destData, bits, inBytes);
			return cv::Mat(height, width, typeFlage, bits, step);
		}
		if( channels == 3 ) {
			copyRGB2BGR_32bit((uint32_t *)destData, bits, inBytes);
			return cv::Mat(height, width, typeFlage, bits, step);
		}
	}

	return cv::Mat();
}

/// @brief 4 通道拷贝
#define For_Channel_4(_Src_Data, _Des_Data, _Data_len) \
	for( size_t index = 0; index < _Data_len; index += 4 ) {\
		_Des_Data[index] = _Src_Data[index + 2];\
		_Des_Data[index + 1] = _Src_Data[index + 1];\
		_Des_Data[index + 2] = _Src_Data[index];\
		_Des_Data[index + 3] = _Src_Data[index+3];\
	}


/// @brief 3 通道拷贝
#define For_Channel_3(_Src_Data, _Des_Data, _Data_len) \
	for( size_t index = 0; index < _Data_len; index += 3 ) {\
		_Des_Data[index] = _Src_Data[index + 2];\
		_Des_Data[index + 1] = _Src_Data[index + 1];\
		_Des_Data[index + 2] = _Src_Data[index];\
	}

/// @brief 2 通道拷贝
#define For_Channel_2(_Src_Data, _Des_Data, _Data_len) \
	for( size_t index = 0; index < _Data_len; ++index ) \
		_Des_Data[index] = _Src_Data[index ];

/// @brief 1 通道拷贝
#define For_Channel_1(_Src_Data, _Des_Data, _Data_len) \
	for( size_t index = 0; index < _Data_len; ++index ) \
		_Des_Data[index] = _Src_Data[index ];

void ConverQimageOrCvMat::copyRGBA2BGRA_8bit( const uint8_t *srcData, uint8_t *desData, size_t dataLen ) {
	For_Channel_4(srcData, desData, dataLen);
}

void ConverQimageOrCvMat::copyRGB2BGR_8bit( const uint8_t *srcData, uint8_t *desData, size_t dataLen ) {
	For_Channel_3(srcData, desData, dataLen);
}


void ConverQimageOrCvMat::copyData2CloneData_8bit( const uint8_t *srcData, uint8_t *desData, size_t dataLen ) {
	For_Channel_1(srcData, desData, dataLen);
}

void ConverQimageOrCvMat::copyRGBA2BGRA_16bit( const uint16_t *srcData, uint16_t *desData, size_t dataLen ) {
	For_Channel_4(srcData, desData, dataLen);
}

void ConverQimageOrCvMat::copyRGB2BGR_16bit( const uint16_t *srcData, uint16_t *desData, size_t dataLen ) {
	For_Channel_3(srcData, desData, dataLen);

}

void ConverQimageOrCvMat::copyData2CloneData_16bit( const uint16_t *srcData, uint16_t *desData, size_t dataLen ) {
	For_Channel_1(srcData, desData, dataLen);
}

void ConverQimageOrCvMat::copyRGB2BGR_32bit( const uint32_t *srcData, uint32_t *desData, size_t dataLen ) {
	For_Channel_3(srcData, desData, dataLen);
}

void ConverQimageOrCvMat::copyRGBA2BGRA_32bit( const uint32_t *srcData, uint32_t *desData, size_t dataLen ) {
	For_Channel_4(srcData, desData, dataLen);
}

void ConverQimageOrCvMat::copyData2CloneData_32bit( const uint32_t *srcData, uint32_t *desData, size_t dataLen ) {
	For_Channel_1(srcData, desData, dataLen);
}