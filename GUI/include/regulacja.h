#ifndef REGULACJA_H
#define REGULACJA_H

#include <QMainWindow>
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QChartView>
#include <QGroupBox>
#include <QFormLayout>
#include <QFrame>
#include <QSpacerItem>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QCloseEvent>

class Regulacja : public QMainWindow
{
    Q_OBJECT

public:
    Regulacja(QWidget *parent = nullptr);
    ~Regulacja();
    QWidget *centralWidget;
    QGridLayout *mainGridLayout;

    void closeEvent (QCloseEvent *event);
};
#endif // REGULACJA_H
