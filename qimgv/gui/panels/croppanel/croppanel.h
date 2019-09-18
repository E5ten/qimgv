#ifndef CROPPANEL_H
#define CROPPANEL_H

#include <QWidget>
#include <QScreen>
#include <QStyleOption>
#include <QPainter>
#include <QtGlobal>
#include "gui/customwidgets/sidepanelwidget.h"
#include "gui/customwidgets/spinboxinputfix.h"
#include "gui/overlays/cropoverlay.h"
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QSpacerItem>

class CropPanel : public SidePanelWidget {
    Q_OBJECT

public:
    explicit CropPanel(CropOverlay *_overlay, QWidget *parent = nullptr);
    ~CropPanel();
    void setImageRealSize(QSize);

public slots:
    void onSelectionOutsideChange(QRect rect);
    void show();

signals:
    void crop(QRect);
    void cancel();
    void cropClicked();
    void selectionChanged(QRect);
    void selectAll();
    void aspectRatioChanged(QPointF);

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onCropClicked();
    void onSelectionChange();
    void onAspectRatioChange(); // via manual input
    void onAspectRatioSelected(); // via ComboBox

private:
    void setupLayout();
    QRect cropRect;
    CropOverlay *overlay;
    QSize realSize;
    // ui
    QVBoxLayout layoutVRoot, layoutVGroup1, layoutVGroup2, layoutVGroup3;
    QHBoxLayout layoutHButtons, layoutHSize1, layoutHSize2, layoutHPos1, layoutHPos2, layoutHAR;
    QPushButton cancelButton, cropButton;
    QGroupBox groupBox, groupBox2, groupBox3;
    SpinBoxInputFix widthSpinBox, heightSpinBox, posXSpinBox, posYSpinBox;
    QDoubleSpinBox ARX, ARY;
    QComboBox ARcomboBox;
    QSpacerItem *spacer;
    QLabel label1, label2, label3;
};

#endif // CROPPANEL_H
