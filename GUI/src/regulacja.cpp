#include "include/regulacja.h"
#include "include/singleLineChart.h"
#include "include/doubleLineChart.h"
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
#include <QSpinBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

Regulacja::Regulacja(QWidget *parent)
    : QMainWindow(parent),
      centralWidget(new QWidget),
      mainGridLayout(new QGridLayout)
{


}

Regulacja::~Regulacja()
{
}


void Regulacja::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "APP_NAME",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

