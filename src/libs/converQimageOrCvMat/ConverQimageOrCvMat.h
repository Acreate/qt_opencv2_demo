#ifndef CONVERQIMAGEORCVMAT_H_H_HEAD__FILE__
#define CONVERQIMAGEORCVMAT_H_H_HEAD__FILE__
#pragma once

#include "ConverQimageOrCvMat_export.h"
#include <opencv2/opencv.hpp>
#include <QImage>

class CONVERQIMAGEORCVMAT_EXPORT ConverQimageOrCvMat {
public:
	/// @brief 实现从 qt 图像转换到 opencv 图像
	/// @param qtImage qt 图像对象
	/// @return opencv 图像对象
	static cv::Mat conver( const QImage &qtImage );
	/// @brief 实现从 opencv 格式的图像转换到 qt 中
	/// @param cvImage opencv 图像对象
	/// @return qt 图像对象
	static QImage conver( const cv::Mat &cvImage );
	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyRGB2BGR_8bit( const uint8_t *srcData, uint8_t *desData, size_t dataLen );
	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyRGBA2BGRA_8bit( const uint8_t *srcData, uint8_t *desData, size_t dataLen );
	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyData2CloneData_8bit( const uint8_t *srcData, uint8_t *desData, size_t dataLen );

	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyRGB2BGR_16bit( const uint16_t *srcData, uint16_t *desData, size_t dataLen );
	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyRGBA2BGRA_16bit( const uint16_t *srcData, uint16_t *desData, size_t dataLen );
	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyData2CloneData_16bit( const uint16_t *srcData, uint16_t *desData, size_t dataLen );

	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyRGB2BGR_32bit( const uint32_t *srcData, uint32_t *desData, size_t dataLen );
	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyRGBA2BGRA_32bit( const uint32_t *srcData, uint32_t *desData, size_t dataLen );
	/// @brief rgb 拷贝到 bgr 
	/// @param srcData 存储 rgb 的图像
	/// @param desData 拷贝到 bgr 的图像 
	/// @param dataLen 拷贝长度
	static void copyData2CloneData_32bit( const uint32_t *srcData, uint32_t *desData, size_t dataLen );

private:
	ConverQimageOrCvMat( ) {}
	~ConverQimageOrCvMat( ) {}
};


#endif // CONVERQIMAGEORCVMAT_H_H_HEAD__FILE__