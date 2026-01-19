#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "VideoFrameGrabber.h"

#include <QIcon>
#include <QMessageBox>



int main(int argc, char *argv[]) {

	QGuiApplication app(argc, argv);
	QGuiApplication::setApplicationDisplayName("CamOverlay");
	QGuiApplication::setDesktopFileName("CamOverlay");
	QGuiApplication::setWindowIcon(QIcon("./video.svg"));

	qmlRegisterType<VideoFrameGrabber>("VideoProcessing", 1, 0, "VideoFrameGrabber");

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("test.qml")));
	if (engine.rootObjects().isEmpty()) {
		return -1;
	}


    	return app.exec();
}

