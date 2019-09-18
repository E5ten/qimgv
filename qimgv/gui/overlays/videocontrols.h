#ifndef VIDEOCONTROLS_H
#define VIDEOCONTROLS_H

#include "gui/customwidgets/floatingwidget.h"
#include "gui/customwidgets/videoslider.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>

class VideoControls : public FloatingWidget {
    Q_OBJECT

public:
    explicit VideoControls(OverlayContainerWidget *parent = nullptr);

public slots:
    void setDurationSeconds(int);
    void setPositionSeconds(int);
    void onVideoPaused(bool);

signals:
    void pause();
    void seek(int pos);
    void seekRight();
    void seekLeft();
    void nextFrame();
    void prevFrame();

private:
    int lastVideoPosition;
    QIcon playIcon, pauseIcon;
    void setupLayout();
    QHBoxLayout layoutHRoot, layoutHButtons;
    QPushButton nextFrameButton, prevFrameButton, pauseButton;
    VideoSlider seekBar;
    QLabel label, durationLabel, positionLabel;
    QSpacerItem *spacerH1, *spacerH2, *spacerH3;
};

#endif // VIDEOCONTROLS_H
