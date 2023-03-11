#include <QApplication>
#include <QMessageBox>
#include <QDir>
#include <QLabel>
#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QImageCapture>
#include <QVideoWidget>
#include <QVideoSink>


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
	// 静态拍摄
	QImageCapture captureImage;
	// 媒体录制
	QMediaRecorder recorder;
	// 显示窗口
	QVideoWidget showVieo;
	// 拍摄显示
	QLabel captureImageLabel;
	captureSession.setCamera(&camera);
	captureSession.setRecorder(&recorder);
	captureSession.setVideoOutput(&showVieo);
	captureSession.setImageCapture(&captureImage);

	QVideoSink *videoSink = captureSession.videoSink();
	// 信号
	QObject::connect(videoSink, &QVideoSink::videoFrameChanged, [&]( const QVideoFrame &frame ) {
		// 每帧都拍摄
		captureImage.capture();
	});

	recorder.setQuality(QMediaRecorder::HighQuality);
	QString localfile = QDir::currentPath().append(QDir::separator()).append("recorder.mp4").replace("\\", "/");
	recorder.setOutputLocation(QUrl::fromLocalFile(localfile));
	QObject::connect(&recorder, &QMediaRecorder::recorderStateChanged, [&]( QMediaRecorder::RecorderState state ) {
		qDebug() << "state : " << state;
	});

	QObject::connect(&captureImage, &QImageCapture::imageCaptured, [&]( int id, const QImage &preview ) {
		// 不安全返回
		if( preview.isNull() )
			return;
		// 截图缩放
		QPixmap pixmap = QPixmap::fromImage(preview);
		size_t height = captureImageLabel.height(),
			width = captureImageLabel.width();

		pixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::FastTransformation);
		// 不安全返回
		if( pixmap.isNull() )
			return;
		// 拍摄完成之后实现更新窗口
		captureImageLabel.setPixmap(pixmap);
		// 输出帧数 id
		int mod = id % 200;
		qDebug() << "id : " << id << ", mod = " << mod;
		if( id > 0 )
			if( mod == 0 )
				recorder.stop();
	});

	camera.start();
	recorder.record();
	showVieo.show();
	showVieo.setWindowTitle(QObject::tr("视频播放窗口"));
	QSize size = showVieo.size() / 2;
	const auto &mapFromGlobal = showVieo.mapToGlobal(QPoint(size.width(), size.height()));
	QRect geometry = showVieo.geometry();
	captureImageLabel.setGeometry(mapFromGlobal.x(), mapFromGlobal.y(), size.width(), size.height());
	captureImageLabel.setWindowTitle(QObject::tr("拍摄截图预览"));
	captureImageLabel.show();

	return a.exec();
}