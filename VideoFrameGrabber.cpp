
#include "VideoFrameGrabber.h"

VideoFrameGrabber::VideoFrameGrabber(QObject *parent) : QObject(parent) {
    m_player = new QMediaPlayer(this);
    m_sink = new QVideoSink(this);

    // Connect frame signal to our processing slot
    connect(m_sink, &QVideoSink::videoFrameChanged, this, &VideoFrameGrabber::onVideoFrameChanged);

    // Give the MediaPlayer the sink to send frames to
    m_player->setVideoSink(m_sink);
}

void VideoFrameGrabber::setSource(const QString &filePath) {
    m_player->setSource(QUrl::fromLocalFile(filePath));
    m_player->play();
}

void VideoFrameGrabber::onVideoFrameChanged(const QVideoFrame &frame) {
    if (!frame.isValid())
        return;

    QVideoFrame copy = frame;
    if (!copy.map(QVideoFrame::ReadOnly))
        return;

    // Convert frame to QImage (ready for processing)
    m_currentFrame = copy.toImage();

    // TODO: Add OpenCV / filter processing here

    emit frameUpdated();

    copy.unmap();
}
