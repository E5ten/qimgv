#ifndef INFOOVERLAY_H
#define INFOOVERLAY_H

#include <QWidget>
#include <QLabel>
#include "gui/customwidgets/floatingwidget.h"

class InfoOverlay : public FloatingWidget {
    Q_OBJECT

public:
    explicit InfoOverlay(OverlayContainerWidget *parent = nullptr);

    void setInfo(QString pos, QString fileName, QString info);
private:
    QHBoxLayout layoutHRoot;
    QLabel posLabel, nameLabel, infoLabel;
    void setupLayout();
};

#endif // INFOOVERLAY_H
