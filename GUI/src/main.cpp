#include "include/regulacja.h"
#include "include/chart.h"
#include "include/basicChart.h"
#include "include/singleLineChart.h"
#include "include/doubleLineChart.h"
#include "include/pshm_stc.h"
#include "include/regulation.h"
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
#include<QDebug>
#include <pthread.h>
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
#include "include/tcpSocket.h"
#include <iomanip>
#include <QPointer>

void sendY(){
    qDebug()<<"Sending desired Y";
}

void sendParams(){
    qDebug()<<"Sending desired Parameters";
}

void sendParams2(int N, int Nu, double lambda, QString addrs){
    tcpSocket t2;
    t2.doConnect(addrs);
    t2.sendParameters(N, Nu, lambda);
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //polaczenie
    bool ok = false;
    QInputDialog addr;
    QString addrs = addr.getText(nullptr, "Ustaw polaczenie","Podaj adres ip:",QLineEdit::Normal, "192.168.1.20", &ok);
    //qDebug()<<"Yes"<<addrs;
    tcpSocket t;
    t.doConnect(addrs);

    /*
     *
     * //QByteArray *d = new QByteArray("Hello");
    double d = 23.3;
    QByteArray packet = QByteArray::number(d);

    qDebug()<<*reinterpret_cast<u_int64_t*>(&d);
    qDebug()<<"Hex:"<<packet.toHex();
    char *byteArray = (char*)&d;
    qDebug()<<"Bytes:"<<byteArray;
    float fl = 12.3;
    char *byte = (char*)&fl;
    qDebug()<<"Byte:"<<byte<<sizeof (float);
    for(int i=0;i<4;++i){
        qDebug()<<(int)byte[i];
    }*/
    //double final = *((double*)byteArray);

    //qDebug()<<d->toHex();
    double fl = 12.3;
    char *byte = (char*)&fl;
    //qDebug()<<byte;

    QMainWindow b;
    //QPointer<Regulation> reg = new Regulation;

    Regulation reg;


    //Init proces
    //Init Timer
    QTimer mainTimer;
    mainTimer.setInterval(500);

    //Init_charts
    QVBoxLayout *vBoxRight = new QVBoxLayout;
    doubleLineChart *YChart = new doubleLineChart();
    QWidget *centralWidget = new QWidget;
    QGridLayout *mainGridLayout = new QGridLayout;


    YChart->setTitle("Wyjście");
    YChart->legend()->hide();
    YChart->setAnimationOptions(QChart::AllAnimations);
    QChartView YchartView(YChart);
    YchartView.setRenderHint(QPainter::Antialiasing);

    singleLineChart *UChart = new singleLineChart();
    UChart->setTitle("Sterowanie");
    UChart->legend()->hide();
    UChart->setAnimationOptions(QChart::AllAnimations);
    QChartView UchartView(UChart);
    UchartView.setRenderHint(QPainter::Antialiasing);

    singleLineChart *ZChart = new singleLineChart();
    ZChart->setTitle("Zakłucenie");
    ZChart->legend()->hide();
    ZChart->setAnimationOptions(QChart::AllAnimations);
    QChartView ZchartView(ZChart);
    ZchartView.setRenderHint(QPainter::Antialiasing);


    vBoxRight->addWidget(&YchartView,0);
    vBoxRight->addWidget(&UchartView,0);
    vBoxRight->addWidget(&ZchartView,0);


    //Init rest of GUI
    QVBoxLayout *vBoxLeft = new QVBoxLayout;
    QFormLayout *firstForm = new QFormLayout;

    //Labels
    QLabel *YLabel = new QLabel;
    YLabel->setText("Pożądane wyjście");
    QLabel *ParamLabel = new QLabel;
    ParamLabel->setText("Parametry regulacji");
    QLabel *NLabel = new QLabel;
    NLabel->setText("N   ");
    QLabel *NuLabel = new QLabel;
    NuLabel->setText("Nu ");
    QLabel *LambdaLabel = new QLabel;
    LambdaLabel->setText("λ    ");

    //Buttons
    QPushButton *Ybutton = new QPushButton("USTAW");
    QPushButton *ParamButton = new QPushButton("USTAW");

    //SpinBoxes

    QDoubleSpinBox *Ydsb = new QDoubleSpinBox;
    QSpinBox *Nsb = new QSpinBox;
    QSpinBox *Nusb = new QSpinBox;
    QDoubleSpinBox *Lambdadsb = new QDoubleSpinBox;
    Ydsb->setRange(-5,5);
    Ydsb->setSingleStep(0.1);
    Lambdadsb->setSingleStep(0.01);

    //setup
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    QHBoxLayout *hBoxLayout1 = new QHBoxLayout;
    QHBoxLayout *hBoxLayout2 = new QHBoxLayout;
    QHBoxLayout *hBoxLayout3 = new QHBoxLayout;
    QHBoxLayout *hBoxLayout4 = new QHBoxLayout;


    hBoxLayout->addWidget(Ydsb);
    hBoxLayout->addWidget(Ybutton);
    firstForm->addRow("Pożądane wyjście",hBoxLayout);
    hBoxLayout->setAlignment(Qt::AlignLeft);
    hBoxLayout1->setAlignment(Qt::AlignLeft);
    hBoxLayout2->setAlignment(Qt::AlignLeft);
    hBoxLayout3->setAlignment(Qt::AlignLeft);
    hBoxLayout4->setAlignment(Qt::AlignLeft);

    vBoxLeft->addLayout(firstForm);
    vBoxLeft->addItem(new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    hBoxLayout1->addWidget(ParamLabel);
    hBoxLayout2->addWidget(NLabel);
    hBoxLayout2->addWidget(Nsb);
    hBoxLayout2->addItem(new QSpacerItem(40,2, QSizePolicy::Minimum, QSizePolicy::Minimum));
    hBoxLayout2->addWidget(ParamButton);
    hBoxLayout3->addWidget(NuLabel);
    hBoxLayout3->addWidget(Nusb);
    hBoxLayout4->addWidget(LambdaLabel);
    hBoxLayout4->addWidget(Lambdadsb);
    vBoxLeft->addLayout(hBoxLayout1);
    vBoxLeft->addLayout(hBoxLayout2);
    vBoxLeft->addLayout(hBoxLayout3);
    vBoxLeft->addLayout(hBoxLayout4);
    Lambdadsb->setFixedSize(100,25);

    mainGridLayout->addLayout(vBoxLeft, 0, 0);

    centralWidget->setLayout(mainGridLayout);

    b.setCentralWidget(centralWidget);
    b.resize(1200, 700);
    mainGridLayout->addLayout(vBoxRight,0,1);

    //Connecting Charts to timer

    QObject::connect(&mainTimer, &QTimer::timeout, &reg, &Regulation::read);
    QObject::connect(&reg, &Regulation::valueWyjscieChanged, YChart, &doubleLineChart::appendSeries);
    QObject::connect(&reg, &Regulation::valueSterowanieChanged, UChart, &singleLineChart::appendSeries);
    QObject::connect(&reg, &Regulation::valueZaklucenieChanged, ZChart, &singleLineChart::appendSeries);

    //QObject::connect(ParamButton, &QPushButton::clicked, ZChart, SLOT(ZChart->appendSeries2(reg.getWyjscie())));
    //reg.getWyjscie();
    QObject::connect(ParamButton, &QPushButton::clicked, [=]{
        qDebug()<<"Przesylane parametry to:"<<Nsb->value() << " "<<Nusb->value() << " " <<Lambdadsb->value();
        sendParams2(Nsb->value(),Nusb->value(),Lambdadsb->value(),addrs);

    });
    //QObject::connect(&mainTimer, &QTimer::timeout, ZChart, &singleLineChart::appendSeries2);

    //Connecting spin boxes
    //QObject::connect(&Ydsb, &QDoubleSpinBox::valueChanged, reg, &Regulation::setWyjscieZad);
    mainTimer.start();
    if(ok){
        b.show();
    }

    //ZChart->appendSeries(0);
    return app.exec();
}
