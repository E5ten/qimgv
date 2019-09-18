#ifndef FLOATINGMESSAGE
#define FLOATINGMESSAGE

#include <QTimer>
#include <QLabel>
#include "gui/customwidgets/floatingwidget.h"
#include "settings.h"

enum FloatingMessageIcon {
    NO_ICON,
    ICON_LEFT_EDGE,
    ICON_RIGHT_EDGE,
    ICON_SUCCESS,
    ICON_WARNING,
    ICON_ERROR
};


class FloatingMessage : public FloatingWidget {
    Q_OBJECT 
public:
    FloatingMessage(OverlayContainerWidget *parent);
    void showMessage(QString text, FloatingMessageIcon icon, int fadeDuration);
    void setIcon(FloatingMessageIcon icon);

    void showMessage(QString text, FloatingWidgetPosition position, FloatingMessageIcon icon, int duration);
public slots:
    void show();
    void setText(QString text);

private:
    QTimer visibilityTimer;
    int hideDelay;
    FloatingWidgetPosition preferredPosition;

    void doShowMessage(QString text, FloatingMessageIcon icon, int duration);

    // ui
    void setupLayout();
    QHBoxLayout layoutHRoot;
    QLabel iconLabel, textLabel;
protected:
    void mousePressEvent(QMouseEvent *event);
    QIcon iconLeftEdge, iconRightEdge, iconSuccess, iconWarning, iconError;
private slots:
    void readSettings();
};

#endif // FLOATINGMESSAGE
