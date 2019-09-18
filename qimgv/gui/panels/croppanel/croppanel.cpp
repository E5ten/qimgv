#include "croppanel.h"

CropPanel::CropPanel(CropOverlay *_overlay, QWidget *parent) :
    SidePanelWidget(parent),
    overlay(_overlay),
    spacer(nullptr)
{
    setupLayout();

    hide();

    connect(&cancelButton, SIGNAL(clicked()), this, SIGNAL(cancel()));
    connect(&cropButton, SIGNAL(clicked()), this, SLOT(onCropClicked()));
    connect(&widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onSelectionChange()));
    connect(&heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onSelectionChange()));
    connect(&posXSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onSelectionChange()));
    connect(&posYSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onSelectionChange()));
    connect(&ARX, SIGNAL(valueChanged(double)), this, SLOT(onAspectRatioChange()));
    connect(&ARY, SIGNAL(valueChanged(double)), this, SLOT(onAspectRatioChange()));
    connect(&ARcomboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onAspectRatioSelected()));

    connect(overlay, SIGNAL(selectionChanged(QRect)),
            this, SLOT(onSelectionOutsideChange(QRect)));
    connect(this, SIGNAL(selectionChanged(QRect)),
            overlay, SLOT(onSelectionOutsideChange(QRect)));
    connect(this, SIGNAL(aspectRatioChanged(QPointF)),
            overlay, SLOT(setAspectRatio(QPointF)));
    connect(overlay, SIGNAL(escPressed()), this, SIGNAL(cancel()));
    connect(overlay, SIGNAL(enterPressed()), this, SLOT(onCropClicked()));
    connect(this, SIGNAL(selectAll()), overlay, SLOT(selectAll()));
}

CropPanel::~CropPanel() {
    delete spacer;
}

void CropPanel::setupLayout() {
    cropButton.setAccessibleName("Button");
    cancelButton.setAccessibleName("Button");
    cropButton.setText("Crop");
    cancelButton.setText("Cancel");

    ARcomboBox.addItem("Free");
    ARcomboBox.addItem("Custom");
    ARcomboBox.addItem("Current Image");
    ARcomboBox.addItem("This Screen");
    ARcomboBox.addItem("1:1");
    ARcomboBox.addItem("4:3");
    ARcomboBox.addItem("16:9");
    ARcomboBox.addItem("16:10");

    widthSpinBox.setAlignment(Qt::AlignCenter);
    widthSpinBox.setButtonSymbols(QAbstractSpinBox::NoButtons);
    widthSpinBox.setKeyboardTracking(false);

    heightSpinBox.setAlignment(Qt::AlignCenter);
    heightSpinBox.setButtonSymbols(QAbstractSpinBox::NoButtons);
    heightSpinBox.setKeyboardTracking(false);

    posXSpinBox.setAlignment(Qt::AlignCenter);
    posXSpinBox.setButtonSymbols(QAbstractSpinBox::NoButtons);
    posXSpinBox.setKeyboardTracking(false);

    posYSpinBox.setAlignment(Qt::AlignCenter);
    posYSpinBox.setButtonSymbols(QAbstractSpinBox::NoButtons);
    posYSpinBox.setKeyboardTracking(false);

    ARX.setAlignment(Qt::AlignCenter);
    ARX.setButtonSymbols(QAbstractSpinBox::NoButtons);
    ARX.setKeyboardTracking(false);

    ARY.setAlignment(Qt::AlignCenter);
    ARY.setButtonSymbols(QAbstractSpinBox::NoButtons);
    ARY.setKeyboardTracking(false);

    layoutHSize1.setContentsMargins(0,0,0,0);
    layoutHSize2.setContentsMargins(0,0,0,0);
    layoutHPos1.setContentsMargins(0,0,0,0);
    layoutHPos2.setContentsMargins(0,0,0,0);
    layoutHSize1.setSpacing(10);
    layoutHSize2.setSpacing(10);
    layoutHPos1.setSpacing(10);
    layoutHPos2.setSpacing(10);

    layoutHAR.setContentsMargins(0,0,0,0);

    layoutHSize1.addWidget(new QLabel("Width"));
    layoutHSize1.addWidget(&widthSpinBox);

    layoutHSize2.addWidget(new QLabel("Height"));
    layoutHSize2.addWidget(&heightSpinBox);

    layoutHPos1.addWidget(new QLabel("X"));
    layoutHPos1.addWidget(&posXSpinBox);

    layoutHPos2.addWidget(new QLabel("Y"));
    layoutHPos2.addWidget(&posYSpinBox);

    layoutVGroup1.setContentsMargins(0,0,0,0);
    layoutVGroup2.setContentsMargins(0,0,0,0);
    layoutVGroup3.setContentsMargins(0,0,0,0);
    layoutVGroup1.setSpacing(8);
    layoutVGroup2.setSpacing(8);
    layoutVGroup3.setSpacing(8);

    label1.setText("<b>Size</b>");
    label2.setText("<b>Position</b>");
    label3.setText("<b>Aspect Ratio</b>");
    label1.setAlignment(Qt::AlignCenter);
    label2.setAlignment(Qt::AlignCenter);
    label3.setAlignment(Qt::AlignCenter);

    layoutHAR.addWidget(&ARX);
    layoutHAR.addWidget(new QLabel(":"));
    layoutHAR.addWidget(&ARY);

    layoutVGroup1.addWidget(&label1);
    layoutVGroup2.addWidget(&label2);
    layoutVGroup3.addWidget(&label3);

    layoutVGroup1.addLayout(&layoutHSize1);
    layoutVGroup1.addLayout(&layoutHSize2);

    layoutVGroup2.addLayout(&layoutHPos1);
    layoutVGroup2.addLayout(&layoutHPos2);

    layoutVGroup3.addWidget(&ARcomboBox);
    layoutVGroup3.addLayout(&layoutHAR);

    groupBox.setLayout(&layoutVGroup1);
    groupBox2.setLayout(&layoutVGroup2);
    groupBox3.setLayout(&layoutVGroup3);

    layoutHButtons.setContentsMargins(0,0,0,0);
    layoutHButtons.setSpacing(5);
    layoutHButtons.addWidget(&cropButton);
    layoutHButtons.addWidget(&cancelButton);

    spacer = new QSpacerItem(20, 40, QSizePolicy::Maximum, QSizePolicy::Expanding);

    layoutVRoot.setContentsMargins(20,20,18,0);
    layoutVRoot.setSpacing(8);

    layoutVRoot.addWidget(&groupBox);
    layoutVRoot.addWidget(&groupBox2);
    layoutVRoot.addWidget(&groupBox3);
    layoutVRoot.addSpacing(5);
    layoutVRoot.addLayout(&layoutHButtons);
    layoutVRoot.addSpacerItem(spacer);

    setLayout(&layoutVRoot);
    setFocusPolicy(Qt::NoFocus);
}

void CropPanel::setImageRealSize(QSize sz) {
    widthSpinBox.setMaximum(sz.width());
    heightSpinBox.setMaximum(sz.height());
    realSize = sz;
    // reset to free mode on image change
    ARcomboBox.setCurrentIndex(0);
    // update aspect ratio in input fields

    onAspectRatioSelected();
}

void CropPanel::onCropClicked() {
    QRect target(posXSpinBox.value(), posYSpinBox.value(),
                 widthSpinBox.value(), heightSpinBox.value());
    if(target.width() > 0 && target.height() > 0 && target.size() != realSize)
        emit crop(target);
    else
        emit cancel();
}

// on user input
void CropPanel::onSelectionChange() {
    emit selectionChanged(QRect(posXSpinBox.value(),
                                posYSpinBox.value(),
                                widthSpinBox.value(),
                                heightSpinBox.value()));
}

void CropPanel::onAspectRatioChange() {
    ARcomboBox.setCurrentIndex(1); // "Custom"
    if(ARX.value() && ARY.value())
        emit aspectRatioChanged(QPointF(ARX.value(), ARY.value()));
}

// 0 == free
// 1 == custom (from input fields)
// 2 == current image
// 3 == current screen
// 4 ...
void CropPanel::onAspectRatioSelected() {
    QPointF newAR(1, 1);

    int index = ARcomboBox.currentIndex();
    switch(index) {
    case 0:
    {
        overlay->setForceAspectRatio(false);
        if(realSize.height() != 0)
            newAR = QPointF(qreal(realSize.width()) / realSize.height(), 1.0);
        break;
    }
    case 1:
    {
        newAR = QPointF(ARX.value(), ARY.value());
        break;
    }
    case 2:
    {
        newAR = QPointF(qreal(realSize.width()) / realSize.height(), 1.0);
        break;
    }
    case 3:
    {
        QScreen* screen = nullptr;
#if QT_VERSION >= 0x050A00
        screen = QGuiApplication::screenAt(mapToGlobal(ARcomboBox.geometry().topLeft()));
        if(!screen)
            screen = QGuiApplication::primaryScreen();
#else
        screen = QGuiApplication::primaryScreen();
#endif
        newAR = QPointF(qreal(screen->geometry().width()) / screen->geometry().height(), 1.0);
        break;
    }
    case 4:
    {
        newAR = QPointF(1.0, 1.0);
        break;
    }
    case 5:
    {
        newAR = QPointF(4.0, 3.0);
        break;
    }
    case 6:
    {
        newAR = QPointF(16.0, 9.0);
        break;
    }
    case 7:
    {
        newAR = QPointF(16.0, 10.0);
        break;
    }
    default: // apply aspect ratio; update input fields
    {
        break;
    }
    }

    ARX.blockSignals(true);
    ARY.blockSignals(true);
    ARX.setValue(newAR.x());
    ARY.setValue(newAR.y());
    ARX.blockSignals(false);
    ARY.blockSignals(false);
    if(index)
        overlay->setAspectRatio(newAR);
}

// update input box values
void CropPanel::onSelectionOutsideChange(QRect rect) {
    widthSpinBox.blockSignals(true);
    heightSpinBox.blockSignals(true);
    posXSpinBox.blockSignals(true);
    posYSpinBox.blockSignals(true);

    widthSpinBox.setValue(rect.width());
    heightSpinBox.setValue(rect.height());
    posXSpinBox.setValue(rect.left());
    posYSpinBox.setValue(rect.top());

    widthSpinBox.blockSignals(false);
    heightSpinBox.blockSignals(false);
    posXSpinBox.blockSignals(false);
    posYSpinBox.blockSignals(false);
}

void CropPanel::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CropPanel::show() {
    QWidget::show();
    // stackoverflow sorcery
    QTimer::singleShot(0, &widthSpinBox, SLOT(setFocus()));
}

void CropPanel::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        emit onCropClicked();
    } else if(event->key() == Qt::Key_Escape) {
        emit cancel();
    } else if(event->matches(QKeySequence::SelectAll)) {
        emit selectAll();
    } else {
        event->ignore();
    }
}


