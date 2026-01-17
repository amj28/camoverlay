#include <iostream>
#include <QApplication>

#include <QCamera>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QVideoWidget>
#include <QCameraDevice>

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	QApplication::setApplicationName("CamOverlay");

	
	QVideoWidget viewfinder;
	viewfinder.show();

	// get default camera
	QCamera camera(QMediaDevices::defaultVideoInput());

	if (camera.cameraDevice().isNull()) {
		std::cout << "No camera available!\n";
		return -1;
	}

	// connect camera to viewfinder
	QMediaCaptureSession captureSession;
	captureSession.setCamera(&camera);
	captureSession.setVideoOutput(&viewfinder);

	camera.start();

    	return app.exec();
}

