#include <QApplication>
#include <QMessageBox>
#include <QDir>
#include <QLabel>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QMediaPlayer>
#include <QMediaRecorder>
#include <QImageCapture>
#include <QMediaDevices>
#include <QVideoSink>
#include <QThread>
#include <QMediaPlayer>
#include <QVideoWidget>

#include "ConverQimageOrCvMat.h"

class Thread : public virtual QThread {
	QImage image;
	QPixmap pixmap;
	QLabel *widget;
	QVideoFrame frame;

protected:
	void run( ) override {

		// 截图缩放
		pixmap = QPixmap::fromImage(frame.toImage());
		if( widget ) {
			pixmap = pixmap.scaled(widget->width(), widget->height(), Qt::KeepAspectRatio, Qt::FastTransformation);
			widget->setPixmap(pixmap);
		}

	}

public:
	Thread( QObject *parent, const QVideoFrame &frame, QLabel &widget )
		: frame(frame), QThread(parent), widget(&widget) { }

	Thread( const QVideoFrame &frame, QLabel &widget )
		: frame(frame), widget(&widget) { }

	virtual QImage getImage( ) {
		return image;
	}

	virtual QPixmap getPixmap( ) {
		return pixmap;
	}
};


int main( int argc, char *argv[] ) {
	QApplication a(argc, argv);

	QMediaPlayer player;
	// 拍摄显示
	QLabel captureImageLabel;
	//QVideoWidget videoWidget;
	QString url = QObject::tr("C:/quickDownLoads/OpenCV入门到进阶：实战三大典型项目/03章 图像&视频的加载与展示/3-7.mp4");
	player.setSource(QUrl(url));
	// 设备
	//player.setVideoSink(&videoSink);
	//player.setVideoOutput(&videoWidget);
	QVideoSink *videoSink = new QVideoSink;
	player.setVideoSink(videoSink);

	//Thread *pThread = nullptr;
	// 信号
	QObject::connect(videoSink, &QVideoSink::videoFrameChanged, [&]( const QVideoFrame &frame ) {
		//qDebug() << "videoSink";
		//if( pThread )
		//	if( pThread->isRunning() )
		//		return;
		//	else
		//		delete pThread;
		//pThread = new Thread(&videoSink, frame, captureImageLabel);
		//pThread->start();
		// 截图缩放
		QImage image = frame.toImage();
		QPixmap pixmap = QPixmap::fromImage(image);
		pixmap = pixmap.scaled(captureImageLabel.width(), captureImageLabel.height(), Qt::KeepAspectRatio, Qt::FastTransformation);
		captureImageLabel.setPixmap(pixmap);
	});
	QObject::connect(&player, &QMediaPlayer::errorOccurred, [&]( QMediaPlayer::Error error, const QString &errorString ) {
		qDebug() << error << " : " << errorString;
	});
	player.play();
	captureImageLabel.setWindowTitle(QObject::tr("视频播放"));
	captureImageLabel.show();
	//videoWidget.setWindowTitle(QObject::tr("视频播放"));
	//videoWidget.show();
	int exec = a.exec();
	/*if( pThread )
		pThread->wait();
	delete pThread;*/
	delete videoSink;
	return exec;
}