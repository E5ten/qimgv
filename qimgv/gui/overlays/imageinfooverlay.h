#ifndef IMAGEINFOOVERLAY_H
#define IMAGEINFOOVERLAY_H

#include "gui/customwidgets/floatingwidget.h"
#include <QWheelEvent>
#include <QTableWidget>
#include <QLabel>

class ImageInfoOverlay : public FloatingWidget
{
    Q_OBJECT

public:
    explicit ImageInfoOverlay(OverlayContainerWidget *parent = nullptr);
    void setExifInfo(QMap<QString, QString>);

protected:
    void wheelEvent(QWheelEvent *event);

private:
    void setupLayout();
    QVBoxLayout layoutVRoot;
    QTableWidget tableWidget;
    QLabel headerLabel;
};

#endif // IMAGEINFOOVERLAY_H
