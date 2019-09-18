#include "imageinfooverlay.h"

ImageInfoOverlay::ImageInfoOverlay(OverlayContainerWidget *parent) :
    FloatingWidget(parent)
{
    setupLayout();
    hide();
    tableWidget.setColumnWidth(0, 120);
    tableWidget.setColumnWidth(1, 142);
    this->setPosition(FloatingWidgetPosition::RIGHT);

    if(parent)
        setContainerSize(parent->size());
}

void ImageInfoOverlay::setExifInfo(QMap<QString, QString> info) {
    while(tableWidget.rowCount() > 0) {
        tableWidget.removeRow(tableWidget.rowCount() - 1);
    }
    QMap<QString, QString>::const_iterator i = info.constBegin();
    while (i != info.constEnd()) {
        tableWidget.insertRow(tableWidget.rowCount());
        tableWidget.setItem(tableWidget.rowCount() - 1, 0, new QTableWidgetItem(i.key()));
        tableWidget.setItem(tableWidget.rowCount() - 1, 1, new QTableWidgetItem(i.value()));
        ++i;
    }
}

void ImageInfoOverlay::setupLayout() {
    headerLabel.setText("<b>Exif tags</b>");
    tableWidget.setFrameShape(QFrame::NoFrame);
    tableWidget.setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    tableWidget.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget.setFocusPolicy(Qt::NoFocus);
    layoutVRoot.addWidget(&headerLabel);
    layoutVRoot.addWidget(&tableWidget);
    tableWidget.setMinimumSize(258, 240); // maybe fixed?
    this->setLayout(&layoutVRoot);
}

void ImageInfoOverlay::wheelEvent(QWheelEvent *event) {
    event->accept();
}
