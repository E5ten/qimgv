#include "infooverlay.h"

InfoOverlay::InfoOverlay(OverlayContainerWidget *parent) :
    FloatingWidget(parent)
{
    setupLayout();
    setPosition(FloatingWidgetPosition::TOPLEFT);
    this->setMarginX(0);
    this->setMarginY(0);

    if(parent)
        setContainerSize(parent->size());
}

void InfoOverlay::setupLayout() {
    layoutHRoot.addWidget(&posLabel);
    layoutHRoot.addWidget(&nameLabel);
    layoutHRoot.addWidget(&infoLabel);
    this->setLayout(&layoutHRoot);
}

void InfoOverlay::setInfo(QString pos, QString fileName, QString info) {
    posLabel.setText(pos);
    nameLabel.setText(fileName);
    infoLabel.setText(info);
    this->adjustSize();
}
