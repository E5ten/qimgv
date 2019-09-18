#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include "gui/customwidgets/sidepanelwidget.h"

class SidePanel : public QWidget
{
    Q_OBJECT

public:
    explicit SidePanel(QWidget *parent = nullptr);

    void setWidget(SidePanelWidget *w);
    SidePanelWidget* widget();

public slots:
    void show();
    void hide();

protected:
    void paintEvent(QPaintEvent *);
private:
    QVBoxLayout layoutVRoot;
    SidePanelWidget *mWidget;
    void setupLayout();
};

#endif // SIDEPANEL_H
