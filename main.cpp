#include <QApplication>
#include <QMessageBox>
#include <QIcon>

#include <QCamera>
#include <QCameraDevice>

#include <QMediaCaptureSession>
#include <QMediaDevices>

#include <QVideoWidget>
#include <QVideoSink>


int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	QApplication::setApplicationName("CamOverlay");

	
	QVideoWidget widget;
	widget.setWindowIcon(QIcon("./video.svg"));
	// widget.setWindowFlag(Qt::FramelessWindowHint); // removes frame but you cant drag/resize
	widget.setAttribute(Qt::WA_TranslucentBackground);	
	widget.show();

	// get default camera
	QCamera camera(QMediaDevices::defaultVideoInput());

	if (camera.cameraDevice().isNull()) {
		QMessageBox::critical(nullptr, "Error", "No Camera Found!");
		//return -1;
	}


	// connect camera to viewfinder
	QMediaCaptureSession captureSession;
	captureSession.setCamera(&camera);
	captureSession.setVideoOutput(&widget);

	QVideoSink *sink = widget.videoSink();
	QObject::connect(sink, &QVideoSink::videoFrameChanged, [](const QVideoFrame &frame) {});

	camera.start();

    	return app.exec();
}

