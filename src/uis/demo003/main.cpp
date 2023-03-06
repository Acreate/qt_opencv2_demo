#include <QApplication>
#include <QMessageBox>
#include <QDir>
#include <QLabel>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QImageCapture>
#include <QMediaDevices>
#include <QVideoSink>
#include <QThread>
#include <QMediaPlayer>

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
	if( QMediaDevices::videoInputs().count() == 0 ) {
		QMessageBox::information(nullptr, QObject::tr("错误"), QObject::tr("没有找到输入设备"));
		return -1;
	}

	// 默认的视频输入设备
	QCameraDevice defaultVideoInput = QMediaDevices::defaultVideoInput();
	// 设置摄像机
	QCamera camera(defaultVideoInput);
	// 媒体会话
	QMediaCaptureSession captureSession;
	// 设备
	QVideoSink videoSink;
	// 拍摄显示
	QLabel captureImageLabel;
	captureSession.setCamera(&camera);
	captureSession.setVideoSink(&videoSink);
	Thread *pThread = nullptr;
	// 信号
	QObject::connect(&videoSink, &QVideoSink::videoFrameChanged, [&]( const QVideoFrame &frame ) {
		if( pThread )
			if( pThread->isRunning() )
				return;
			else
				delete pThread;
		pThread = new Thread(&videoSink, frame, captureImageLabel);
		pThread->start();
	});

	camera.start();
	captureImageLabel.setWindowTitle(QObject::tr("拍摄截图预览"));
	captureImageLabel.show();
	int exec = a.exec();
	if( pThread )
		pThread->wait();
	delete pThread;
	return exec;
}