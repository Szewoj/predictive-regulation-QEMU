#include "include/controlPanel.h"

void controlPanel::initCharts(){

    YChart = new doubleLineChart();
    YChart->setTitle("Wyjście");
    YChart->legend()->hide();
    YChart->setAnimationOptions(QChart::AllAnimations);
    YchartView = new QChartView(YChart,this
                                );
    YchartView->setRenderHint(QPainter::Antialiasing);

    UChart = new singleLineChart();
    UChart->setTitle("Sterowanie");
    UChart->legend()->hide();
    UChart->setAnimationOptions(QChart::AllAnimations);
    UchartView = new QChartView(UChart,this);
    UchartView->setRenderHint(QPainter::Antialiasing);

    ZChart = new singleLineChart();
    ZChart->setTitle("Zakłucenie");
    ZChart->legend()->hide();
    ZChart->setAnimationOptions(QChart::AllAnimations);
    ZchartView = new QChartView(ZChart,this);
    ZchartView->setRenderHint(QPainter::Antialiasing);

    vBoxRight->addWidget(YchartView,0);
    vBoxRight->addWidget(UchartView,0);
    vBoxRight->addWidget(ZchartView,0);


}
void controlPanel::initRestOfGui(){
    //aditional layouts
    hBoxLayout = new QHBoxLayout(this);
    hBoxLayout1 = new QHBoxLayout(this);
    hBoxLayout2 = new QHBoxLayout(this);
    hBoxLayout3 = new QHBoxLayout(this);
    hBoxLayout4 = new QHBoxLayout(this);

    //labels
    YLabel = new QLabel;
    YLabel->setText("Pożądane wyjście");
    ParamLabel = new QLabel;
    ParamLabel->setText("Parametry regulacji");
    NLabel = new QLabel;
    NLabel->setText("N   ");
    NuLabel = new QLabel;
    NuLabel->setText("Nu ");
    LambdaLabel = new QLabel;
    LambdaLabel->setText("λ    ");

    //buttons
    Ybutton = new QPushButton("USTAW",this);
    ParamButton = new QPushButton("USTAW",this);


    //spinboxes
    Ydsb = new QDoubleSpinBox(this);
    Nsb = new QSpinBox(this);
    Nusb = new QSpinBox(this);
    Lambdadsb = new QDoubleSpinBox(this);
    Ydsb->setRange(-5,5);
    Ydsb->setSingleStep(0.1);
    Lambdadsb->setSingleStep(0.01);
    Lambdadsb->setFixedSize(100,25);

    //layouts
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


}
controlPanel::controlPanel(QWidget *parent)
{
    vBoxRight = new QVBoxLayout(this);
    vBoxLeft = new QVBoxLayout(this);
    firstForm = new QFormLayout(this);
    centralWidget = new QWidget(this);
    mainGridLayout = new QGridLayout(this);

    QInputDialog addr;
    QString addrs = addr.getText(nullptr, "Ustaw polaczenie","Podaj adres ip:",QLineEdit::Normal, "192.168.1.29:65433", &okay);
    if(okay)
    {
        QRegExp regExp("(\\:)");
        QStringList adres = addrs.split(regExp);
        socket = new tcpSocket;
        socket->doConnect(adres[0], adres[1].toInt());
    }

    initCharts();
    initRestOfGui();
    mainGridLayout->addLayout(vBoxLeft, 0, 0);
    mainGridLayout->addLayout(vBoxRight,0,1);
    centralWidget->setLayout(mainGridLayout);

    QObject::connect(&mainTimer, &QTimer::timeout, &reg, &Regulation::read);
    QObject::connect(&reg, &Regulation::valueWyjscieChanged, YChart, &doubleLineChart::appendSeries);
    QObject::connect(&reg, &Regulation::valueSterowanieChanged, UChart, &singleLineChart::appendSeries);
    QObject::connect(&reg, &Regulation::valueZaklucenieChanged, ZChart, &singleLineChart::appendSeries);

    QObject::connect(Ybutton, &QPushButton::clicked, [=]{

        socket->sendYoutput(Ydsb->value());
        reg.setWyjscieZadane(Ydsb->value());

    });
    QObject::connect(ParamButton, &QPushButton::clicked, [=]{

        socket->sendParameters(Ydsb->value(), Nsb->value(), Nusb->value(), Lambdadsb->value());
        reg.setWyjscieZadane(Ydsb->value());
    });

    mainTimer.setInterval(500);
    mainTimer.start();

    setCentralWidget(centralWidget);
    resize(1200, 700);
    setMinimumSize(1200, 700);
    if(okay)
        show();

}

controlPanel::~controlPanel()
{
    delete centralWidget;

    delete socket;
    /*
    delete Ydsb;
    delete YLabel;

    delete firstForm;*/
    //delete hBoxLayout;
    /*
    delete hBoxLayout1;
    delete hBoxLayout2;
    delete hBoxLayout3;
    delete hBoxLayout4;*/
/*
    delete Ydsb;
    delete Nsb;
    delete Nusb;
    delete Lambdadsb;

    delete YLabel;
    delete ParamLabel;
    delete NLabel;
    delete NuLabel;
    delete LambdaLabel;

    delete Ybutton;
    delete ParamButton;

    delete YchartView;
    delete UchartView;
    delete ZchartView;

    delete YChart;
    delete UChart;
    delete ZChart;*/
    /*
    delete mainGridLayout;
    delete vBoxRight;
    delete vBoxLeft;
    delete firstForm;

    delete YChart;
    delete UChart;
    delete ZChart;

    delete YchartView;
    delete UchartView;
    delete ZchartView;

    delete Ybutton;
    delete ParamButton;

    delete YLabel;
    delete ParamLabel;
    delete NLabel;
    delete NuLabel;
    delete LambdaLabel;

    delete Ydsb;
    delete Nsb;
    delete Nusb;
    delete Lambdadsb;

    delete hBoxLayout;
    delete hBoxLayout1;
    delete hBoxLayout2;
    delete hBoxLayout3;
    delete hBoxLayout4;*/

}

void controlPanel::closeEvent (QCloseEvent *event)
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
