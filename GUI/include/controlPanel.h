#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QChartView>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QInputDialog>
#include "../include/singleLineChart.h"
#include "../include/doubleLineChart.h"
#include "../include/pshm_stc.h"
#include "../include/regulation.h"
#include "../include/tcpSocket.h"

class controlPanel : public QMainWindow
{
    Q_OBJECT

public:
    controlPanel(QWidget *parent = nullptr);
    ~controlPanel();
    bool getStatus();

private:
    QTimer mainTimer;
    QWidget *centralWidget;
    Regulation reg;
    bool okay;
    QString ErrorMessage;
    tcpSocket *socket;
    QProcess *symProces;

    QGridLayout *mainGridLayout;
    QVBoxLayout *vBoxRight;
    QVBoxLayout *vBoxLeft;
    QFormLayout *firstForm;

    doubleLineChart *YChart;
    singleLineChart *UChart;
    singleLineChart *ZChart;

    QChartView *YchartView;
    QChartView *UchartView;
    QChartView *ZchartView;

    QPushButton *Ybutton;
    QPushButton *ParamButton;

    QLabel *YLabel;
    QLabel *ParamLabel;
    QLabel *NLabel;
    QLabel *NuLabel;
    QLabel *LambdaLabel;

    QDoubleSpinBox *Ydsb;
    QSpinBox *Nsb;
    QSpinBox *Nusb;
    QDoubleSpinBox *Lambdadsb;

    QHBoxLayout *hBoxLayout;
    QHBoxLayout *hBoxLayout1;
    QHBoxLayout *hBoxLayout2;
    QHBoxLayout *hBoxLayout3;
    QHBoxLayout *hBoxLayout4;

    void closeEvent (QCloseEvent *event);

    void initCharts();
    void initRestOfGui();

};

#endif // CONTROLPANEL_H
