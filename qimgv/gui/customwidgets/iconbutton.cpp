#include "iconbutton.h"

IconButton::IconButton(QWidget *parent)
    : IconWidget(parent),
      mCheckable(false),
      mChecked(false),
      mPressed(false)
{
}

void IconButton::setCheckable(bool mode) {
    mCheckable = mode;
}

void IconButton::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    mPressed = true;
    setProperty("pressed", true);
    style()->unpolish(this);
    style()->polish(this);
}

void IconButton::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    mPressed = false;
    if(mCheckable) {
        mChecked = !this->property("checked").toBool();
        setProperty("checked", mChecked);
        style()->unpolish(this);
        style()->polish(this);
        emit toggled(mChecked);
    } else {
        emit clicked();
    }
    if(!mChecked) {
        setProperty("pressed", false);
        style()->unpolish(this);
        style()->polish(this);
    }
}

void IconButton::mouseMoveEvent(QMouseEvent *event) {
    if(mChecked || !mPressed)
        return;
    if(QRect(0, 0, width(), height()).contains(event->pos())) {
        if(!property("pressed").toBool()) {
            setProperty("pressed", true);
            style()->unpolish(this);
            style()->polish(this);
        }
    } else {
        if(property("pressed").toBool()) {
            setProperty("pressed", false);
            style()->unpolish(this);
            style()->polish(this);
        }
    }
}
