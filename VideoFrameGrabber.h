#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QVideoSink>
#include <QVideoFrame>
#include <QImage>

class VideoFrameGrabber : public QObject {
    
	Q_OBJECT
	Q_PROPERTY(QImage currentFrame READ currentFrame NOTIFY frameUpdated)

	public:
	explicit VideoFrameGrabber(QObject *parent = nullptr);

	QImage currentFrame() const { return m_currentFrame; }

	Q_INVOKABLE void setSource(const QString &filePath);

	signals:
	void frameUpdated();

	private slots:
	void onVideoFrameChanged(const QVideoFrame &frame);

	private:
	QMediaPlayer *m_player;
	QVideoSink *m_sink;
	QImage m_currentFrame;

};

