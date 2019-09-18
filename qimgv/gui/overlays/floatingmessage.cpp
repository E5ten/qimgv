#include "floatingmessage.h"

FloatingMessage::FloatingMessage(OverlayContainerWidget *parent) :
    FloatingWidget(parent),
    preferredPosition(FloatingWidgetPosition::BOTTOM)
{
    setupLayout();
    hideDelay = 700;

    visibilityTimer.setSingleShot(true);
    visibilityTimer.setInterval(hideDelay);

    setFadeEnabled(true);
    setFadeDuration(300);

    iconLeftEdge = QIcon(":/res/icons/message/dir_start20.png");
    iconRightEdge = QIcon(":/res/icons/message/dir_end20.png");
    iconSuccess = QIcon(":/res/icons/buttons/success16.png");
    setIcon(FloatingMessageIcon::NO_ICON);

    this->setAccessibleName("FloatingMessage");
    connect(&visibilityTimer, SIGNAL(timeout()), this, SLOT(hide()));

    readSettings();

    connect(settings, SIGNAL(settingsChanged()),
            this, SLOT(readSettings()));

    if(parent)
        setContainerSize(parent->size());
}

void FloatingMessage::readSettings() {
    /*
    // don't interfere with the main panel
    if(settings->panelEnabled() && settings->panelPosition() == PanelHPosition::PANEL_BOTTOM) {
        preferredPosition = FloatingWidgetPosition::TOP;
    } else {
        preferredPosition = FloatingWidgetPosition::BOTTOM;
    }
    */
}

void FloatingMessage::showMessage(QString text, FloatingWidgetPosition _position, FloatingMessageIcon icon, int duration) {
    setPosition(_position);
    doShowMessage(text, icon, duration);
}

void FloatingMessage::showMessage(QString text, FloatingMessageIcon icon, int duration) {
    setPosition(preferredPosition);
    doShowMessage(text, icon, duration);
}

void FloatingMessage::doShowMessage(QString text, FloatingMessageIcon icon, int duration) {
    hideDelay = duration;
    setIcon(icon);
    setText(text);
    show();
}

void FloatingMessage::setupLayout() {
    layoutHRoot.addWidget(&textLabel);
    layoutHRoot.addWidget(&iconLabel);
    layoutHRoot.setContentsMargins(12,11,12,11);
    layoutHRoot.setSizeConstraint(QLayout::SetDefaultConstraint);
    this->setLayout(&layoutHRoot);
}

void FloatingMessage::setText(QString text) {
    textLabel.setText(text);
    text.isEmpty() ? textLabel.hide() : textLabel.show();
    recalculateGeometry();
    update();
}

void FloatingMessage::setIcon(FloatingMessageIcon icon) {
    switch (icon) {
        case FloatingMessageIcon::NO_ICON:
            iconLabel.hide();
            break;
        case FloatingMessageIcon::ICON_LEFT_EDGE:
            iconLabel.show();
            iconLabel.setPixmap(iconLeftEdge.pixmap(20,20));
            break;
        case FloatingMessageIcon::ICON_RIGHT_EDGE:
            iconLabel.show();
            iconLabel.setPixmap(iconRightEdge.pixmap(20,20));
            break;
        case FloatingMessageIcon::ICON_SUCCESS:
            iconLabel.show();
            iconLabel.setPixmap(iconSuccess.pixmap(16,16));
            break;
    }
}

void FloatingMessage::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED (event)
}

// "blink" the widget; show then fade out immediately
void FloatingMessage::show() {
    visibilityTimer.stop();
    FloatingWidget::show();
    // fade out after delay
    visibilityTimer.setInterval(hideDelay);
    visibilityTimer.start();
}
