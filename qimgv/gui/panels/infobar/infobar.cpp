#include "infobar.h"

#include <QPainter>
#include <QStyleOption>

InfoBar::InfoBar(QWidget *parent) :
    QWidget(parent),
    spacer(nullptr)
{
    setupLayout();
    this->setAccessibleName("InfoBar");
    pathLabel.setText("No file opened.");
}

InfoBar::~InfoBar() {
    delete spacer;
}

void InfoBar::setInfo(QString position, QString fileName, QString info) {
    indexLabel.setText(position);
    pathLabel.setText(fileName);
    infoLabel.setText(info);
}

void InfoBar::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void InfoBar::setupLayout() {
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Maximum);
    layoutHRoot.addWidget(&indexLabel);
    layoutHRoot.addWidget(&pathLabel);
    layoutHRoot.addSpacerItem(spacer);
    layoutHRoot.addWidget(&infoLabel);
    layoutHRoot.setContentsMargins(9,3,9,3);
    layoutHRoot.setSpacing(12);
    this->setLayout(&layoutHRoot);
}
