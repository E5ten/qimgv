#include "sidepanel.h"

SidePanel::SidePanel(QWidget *parent) :
    QWidget(parent),
    mWidget(nullptr)
{
    setupLayout();
    this->setObjectName("SidePanel");
    this->hide();
}

void SidePanel::setupLayout() {
    this->setFixedWidth(250);
    layoutVRoot.setContentsMargins(0,0,0,0);
    layoutVRoot.setSpacing(0);
}

void SidePanel::setWidget(SidePanelWidget* w) {
    if(mWidget) {
        mWidget->hide();
        layoutVRoot.removeWidget(mWidget);
    }
    mWidget = w;
    layoutVRoot.addWidget(mWidget);
    this->setLayout(&layoutVRoot);
    w->show();
}

SidePanelWidget* SidePanel::widget() {
    return mWidget;
}

void SidePanel::show() {
    QWidget::show();
    if(mWidget)
        mWidget->show();
}

void SidePanel::hide() {
    if(mWidget) {
        mWidget->hide();
    }
    QWidget::hide();
}

void SidePanel::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
