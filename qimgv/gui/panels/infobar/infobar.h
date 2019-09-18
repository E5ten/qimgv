#ifndef INFOBAR_H
#define INFOBAR_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpacerItem>

class InfoBar : public QWidget {
    Q_OBJECT

public:
    explicit InfoBar(QWidget *parent = nullptr);
    ~InfoBar();

public slots:
    void setInfo(QString position, QString fileName, QString info);
protected:
    void paintEvent(QPaintEvent *event);
private:
    void setupLayout();
    QHBoxLayout layoutHRoot;
    QLabel indexLabel, pathLabel, infoLabel;
    QSpacerItem *spacer;
};

#endif // INFOBAR_H
