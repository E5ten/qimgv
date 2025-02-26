#pragma once

#include "gui/customwidgets/iconwidget.h"
#include <QMouseEvent>

class IconButton : public IconWidget
{
    Q_OBJECT
public:
    explicit IconButton(QWidget *parent = nullptr);
    void setCheckable(bool mode);

signals:
    void clicked();
    void toggled(bool);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool mCheckable, mChecked, mPressed;
    void mouseMoveEvent(QMouseEvent *event);
};
