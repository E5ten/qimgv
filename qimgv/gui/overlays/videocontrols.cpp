#include "videocontrols.h"

VideoControls::VideoControls(OverlayContainerWidget *parent) :
    FloatingWidget(parent),
    spacerH1(nullptr),
    spacerH2(nullptr),
    spacerH3(nullptr)
{
    setupLayout();
    this->setAttribute(Qt::WA_NoMousePropagation, true);
    hide();

    playIcon.addPixmap(QPixmap(":res/icons/buttons/play24.png"));
    pauseIcon.addPixmap(QPixmap(":res/icons/buttons/pause24.png"));

    setPosition(FloatingWidgetPosition::BOTTOM);

    lastVideoPosition = -1;

    connect(&pauseButton, SIGNAL(pressed()), this, SIGNAL(pause()));
    connect(&prevFrameButton, SIGNAL(pressed()), this, SIGNAL(prevFrame()));
    connect(&nextFrameButton, SIGNAL(pressed()), this, SIGNAL(nextFrame()));
    connect(&seekBar, SIGNAL(sliderMovedX(int)), this, SIGNAL(seek(int)));

    if(parent)
        setContainerSize(parent->size());
}

void VideoControls::setupLayout() {
    this->setMinimumSize(300, 40);

    spacerH1 = new QSpacerItem(4, 10, QSizePolicy::Fixed, QSizePolicy::Maximum);
    spacerH2 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Maximum);
    spacerH3 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Maximum);
    label.setText("/");
    seekBar.setFixedSize(200,28);
    seekBar.setFocusPolicy(Qt::NoFocus);
    pauseButton.setFocusPolicy(Qt::NoFocus);
    prevFrameButton.setFocusPolicy(Qt::NoFocus);
    nextFrameButton.setFocusPolicy(Qt::NoFocus);
    pauseButton.setAccessibleName("Button");
    prevFrameButton.setAccessibleName("ButtonSetLeft");
    nextFrameButton.setAccessibleName("ButtonSetRight");
    pauseButton.setFixedSize(44,36);
    prevFrameButton.setFixedSize(36,36);
    nextFrameButton.setFixedSize(36,36);
    pauseButton.setIconSize(QSize(24,24));
    prevFrameButton.setIconSize(QSize(24,24));
    nextFrameButton.setIconSize(QSize(24,24));
    prevFrameButton.setIcon(QIcon(":res/icons/buttons/skip-backwards24.png"));
    nextFrameButton.setIcon(QIcon(":res/icons/buttons/skip-forward24.png"));

    layoutHButtons.setContentsMargins(0,0,0,0);
    layoutHButtons.setSpacing(0);

    layoutHButtons.addWidget(&pauseButton);
    layoutHButtons.addSpacing(4);
    layoutHButtons.addWidget(&prevFrameButton);
    layoutHButtons.addWidget(&nextFrameButton);

    layoutHRoot.setContentsMargins(14,10,14,10);
    layoutHRoot.setSpacing(7);

    layoutHRoot.addLayout(&layoutHButtons);
    layoutHRoot.addSpacing(5);
    layoutHRoot.addWidget(&seekBar);
    layoutHRoot.addSpacing(5);
    layoutHRoot.addWidget(&positionLabel);
    layoutHRoot.addWidget(&label);
    layoutHRoot.addWidget(&durationLabel);
    this->setLayout(&layoutHRoot);
}

void VideoControls::setDurationSeconds(int time) {
    int hours   = time / 3600;
    int minutes = time / 60;
    int seconds = time % 60;
    QString str = QString("%1").arg(minutes, 2, 10, QChar('0')) + ":" +
                  QString("%1").arg(seconds, 2, 10, QChar('0'));
    if(hours)
        str.append(QString("%1").arg(hours, 2, 10, QChar('0')) + ":");

    seekBar.setRange(0, time);
    durationLabel.setText(str);
    recalculateGeometry();
}

void VideoControls::setPositionSeconds(int time) {
    if(time != lastVideoPosition) {
        int hours   = time / 3600;
        int minutes = time / 60;
        int seconds = time % 60;
        QString str = QString("%1").arg(minutes, 2, 10, QChar('0')) + ":" +
                      QString("%1").arg(seconds, 2, 10, QChar('0'));
        if(hours)
            str.append(QString("%1").arg(hours, 2, 10, QChar('0')) + ":");

        positionLabel.setText(str);
        seekBar.blockSignals(true);
        seekBar.setValue(time);
        seekBar.blockSignals(false);
        recalculateGeometry();
    }
    lastVideoPosition = time;
}

void VideoControls::onVideoPaused(bool mode) {
    if(mode)
        pauseButton.setIcon(playIcon);
    else
        pauseButton.setIcon(pauseIcon);
}
