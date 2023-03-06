#include <QApplication>
#include <QDir>
#include <QLabel>
#include <QCamera>
#include <QImageCapture>
#include <QVideoSink>
#include <QThread>
#include <QMediaPlayer>
#include <QVideoWidget>

#include "ConverQimageOrCvMat.h"


int main( int argc, char *argv[] ) {
	QApplication a(argc, argv);

	QMediaPlayer player;
	// 拍摄显示
	QLabel captureImageLabel;
	// 不支持 "\\" 路径
	QString url = QDir::currentPath().append("/").append("test1.mp4").replace("\\", "/");
	qDebug() << url;
	player.setSource(QUrl(url));
	QVideoSink *videoSink = new QVideoSink;
	player.setVideoSink(videoSink);

	QObject::connect(videoSink, &QVideoSink::videoFrameChanged, [&]( const QVideoFrame &frame ) {
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
	int exec = a.exec();
	delete videoSink;
	return exec;
}