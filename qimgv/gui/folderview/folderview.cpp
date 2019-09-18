#include "folderview.h"

FolderView::FolderView(QWidget *parent) :
    QWidget(parent),
    spacer(nullptr)
{
    setupLayout();

    mWrapper.reset(new DirectoryViewWrapper(this));

    openButton.setAction("open");
    settingsButton.setAction("openSettings");
    exitButton.setAction("exit");
    docViewButton.setAction("documentView");

    int min = thumbnailGrid.THUMBNAIL_SIZE_MIN;
    int max = thumbnailGrid.THUMBNAIL_SIZE_MAX;
    int step = thumbnailGrid.ZOOM_STEP;

    zoomSlider.setMinimum(min / step);
    zoomSlider.setMaximum(max / step);
    zoomSlider.setSingleStep(1);
    zoomSlider.setPageStep(1);

    connect(&thumbnailGrid, SIGNAL(thumbnailPressed(int)),
            this, SIGNAL(thumbnailPressed(int)));
    connect(&thumbnailGrid, SIGNAL(thumbnailsRequested(QList<int>, int)),
            this, SIGNAL(thumbnailsRequested(QList<int>, int)));

    connect(&zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(onZoomSliderValueChanged(int)));
    connect(&thumbnailGrid, SIGNAL(thumbnailSizeChanged(int)), this, SLOT(onThumbnailSizeChanged(int)));
    connect(&thumbnailGrid, SIGNAL(showLabelsChanged(bool)), this, SLOT(onShowLabelsChanged(bool)));
    connect(&showLabelsButton, SIGNAL(toggled(bool)), this, SLOT(onShowLabelsButtonToggled(bool)));
    connect(&sortingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSortingSelected(int)));

    sortingComboBox.setItemDelegate(new QStyledItemDelegate(&sortingComboBox));
    sortingComboBox.view()->setTextElideMode(Qt::ElideNone);

    thumbnailGrid.setThumbnailSize(settings->folderViewIconSize());
    thumbnailGrid.setShowLabels(settings->showThumbnailLabels());
    onSortingChanged(settings->sortingMode());

    QSizePolicy sp_retain = sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    setSizePolicy(sp_retain);
    hide();
}

void FolderView::setupLayout() {
    layoutHPanel.setContentsMargins(0,0,0,0);
    layoutHPanel.setSpacing(0);

    zoomSlider.setOrientation(Qt::Horizontal);
    zoomSlider.setFixedWidth(110);

    openButton.setFixedSize(38, 38);
    settingsButton.setFixedSize(38, 38);
    docViewButton.setFixedSize(38, 38);
    exitButton.setFixedSize(38, 38);

    spacer = new QSpacerItem(10, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);

    layoutH2.addWidget(&zoomSlider);

    layoutH3.addWidget(&settingsButton);
    layoutH3.addWidget(&docViewButton);
    layoutH3.addWidget(&exitButton);

    layoutHPanel.addWidget(&openButton);
    layoutHPanel.addLayout(&layoutH1);
    layoutHPanel.addSpacerItem(spacer);
    layoutHPanel.addLayout(&layoutH2);
    layoutHPanel.addWidget(&showLabelsButton);
    layoutHPanel.addSpacing(12);
    layoutHPanel.addWidget(&sortingComboBox);
    layoutHPanel.addSpacing(12);
    layoutHPanel.addLayout(&layoutH3);

    layoutVRoot.setContentsMargins(0,0,0,0);
    layoutVRoot.setSpacing(8);

    layoutVRoot.addLayout(&layoutHPanel);
    layoutVRoot.addWidget(&thumbnailGrid);
    this->setLayout(&layoutVRoot);
}

void FolderView::onShowLabelsChanged(bool mode) {
    showLabelsButton.setChecked(mode);
    settings->setShowThumbnailLabels(mode);
}

void FolderView::onShowLabelsButtonToggled(bool mode) {
    thumbnailGrid.setShowLabels(mode);
}

void FolderView::onThumbnailSizeChanged(int newSize) {
    zoomSlider.setValue(newSize / thumbnailGrid.ZOOM_STEP);
    settings->setFolderViewIconSize(newSize);
}

void FolderView::onZoomSliderValueChanged(int value) {
    thumbnailGrid.setThumbnailSize(value * thumbnailGrid.ZOOM_STEP);
}

// changed by user via combobox
void FolderView::onSortingSelected(int mode) {
    emit sortingSelected(static_cast<SortingMode>(mode));
}

void FolderView::onSortingChanged(SortingMode mode) {
    sortingComboBox.blockSignals(true);
    sortingComboBox.setCurrentIndex(static_cast<int>(mode));
    sortingComboBox.blockSignals(false);
}

std::shared_ptr<DirectoryViewWrapper> FolderView::wrapper() {
    return mWrapper;
}

// probably unneeded
void FolderView::show() {
    QWidget::show();
    thumbnailGrid.setFocus();
}

// probably unneeded
void FolderView::hide() {
    QWidget::hide();
    thumbnailGrid.clearFocus();
}

void FolderView::setExitButtonEnabled(bool mode) {
    exitButton.setHidden(!mode);
}

void FolderView::focusInEvent(QFocusEvent *event) {
    Q_UNUSED(event)
    thumbnailGrid.setFocus();
}

void FolderView::populate(int count) {
    thumbnailGrid.populate(count);
}

void FolderView::setThumbnail(int pos, std::shared_ptr<Thumbnail> thumb) {
    thumbnailGrid.setThumbnail(pos, thumb);
}

void FolderView::selectIndex(int index) {
    thumbnailGrid.selectIndex(index);
}

int FolderView::selectedIndex() {
    return thumbnailGrid.selectedIndex();
}

void FolderView::focusOn(int index) {
    thumbnailGrid.focusOn(index);
}

void FolderView::setDirectoryPath(QString path) {
    directoryPathLabel.setText(path);
}

void FolderView::addItem() {
    thumbnailGrid.addItem();
}

void FolderView::insertItem(int index) {
    thumbnailGrid.insertItem(index);
}

void FolderView::removeItem(int index) {
    thumbnailGrid.removeItem(index);
}

// prevent passthrough to parent
void FolderView::wheelEvent(QWheelEvent *event) {
    event->accept();
}

void FolderView::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FolderView::resizeEvent(QResizeEvent *event) {

}
