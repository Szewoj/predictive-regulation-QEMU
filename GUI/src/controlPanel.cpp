#include "../include/controlPanel.h"

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
    ZChart->setTitle("Zakłócenie");
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
    firstForm = new QFormLayout;
    hBoxLayout = new QHBoxLayout;
    hBoxLayout1 = new QHBoxLayout;
    hBoxLayout2 = new QHBoxLayout;
    hBoxLayout3 = new QHBoxLayout;
    hBoxLayout4 = new QHBoxLayout;

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
    Ydsb->setRange(0,110);
    Ydsb->setSingleStep(5);
    Ydsb->setValue(5);

    Nsb = new QSpinBox(this);
    Nsb->setRange(10, 150);
    Nsb->setSingleStep(1);
    Nsb->setValue(100);

    Nusb = new QSpinBox(this);
    Nusb->setRange(1,50);
    Nusb->setSingleStep(1);
    Nusb->setValue(15);

    Lambdadsb = new QDoubleSpinBox(this);
    Lambdadsb->setRange(1,1000);
    Lambdadsb->setSingleStep(0.5);
    Lambdadsb->setValue(8);
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
    centralWidget = new QWidget(this);
    mainGridLayout = new QGridLayout(centralWidget);
    vBoxRight = new QVBoxLayout;
    vBoxLeft = new QVBoxLayout;


    setWindowTitle("Regulacja predykcyjna");
    QInputDialog addr;
    QString addrs = addr.getText(nullptr, "Ustaw polaczenie","Podaj adres ip:",QLineEdit::Normal, "192.168.1.29:65433", &okay);
    if(!okay)
    {
        ErrorMessage = "Application needs address IP and port!";
    }
    QStringList adres;
    socket = new tcpSocket;
    if(okay)
    {
        QRegExp regExp("(\\:)");
        adres = addrs.split(regExp);
        socket->doConnect(adres[0], adres[1].toInt());
        if(!socket->getCon()){
            qDebug()<< "No connection";
            okay = false;
            ErrorMessage = "Connection Error";
        }

    }
    symProces = new QProcess(this);
    if(okay){
        QStringList arguments;
        QString portstr = QString::number(adres[1].toInt() + 1);
        arguments << adres[0] << portstr ;
        symProces->start("./Simulation", arguments);
        if( !symProces->waitForStarted()){
            qDebug()<<"Error during simulation Process";
            okay = false;
            ErrorMessage = "Simulation Process Error";
        }

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

        qDebug()<<socket->getCon();
        socket->sendYoutput(Ydsb->value());
        reg.setWyjscieZadane(Ydsb->value());

    });
    QObject::connect(ParamButton, &QPushButton::clicked, [=]{
        socket->sendParameters(Ydsb->value(), Nsb->value(), Nusb->value(), Lambdadsb->value());
        reg.setWyjscieZadane(Ydsb->value());
    });
    QObject::connect(symProces, &QProcess::stateChanged, [=]{
        if(symProces->state() == QProcess::NotRunning)
        {
            mainTimer.stop();
            disconnect(Ybutton,nullptr,nullptr,nullptr);
            disconnect(ParamButton,nullptr,nullptr,nullptr);
            QMessageBox::information(this, "Information", "The simulation process has stopped", QMessageBox::Yes);

        }
    });
    QObject::connect(socket, &tcpSocket::stateDisconected, [=]{
            mainTimer.stop();
            disconnect(Ybutton,nullptr,nullptr,nullptr);
            disconnect(ParamButton,nullptr,nullptr,nullptr);
            QMessageBox::information(this, "Information", "Connection lost", QMessageBox::Yes);
    });

    mainTimer.setInterval(500);
    mainTimer.start();

    setCentralWidget(centralWidget);
    resize(1200, 700);
    setMinimumSize(1200, 700);
    show();

    if(!okay){
        mainTimer.stop();
        disconnect(Ybutton,nullptr,nullptr,nullptr);
        disconnect(ParamButton,nullptr,nullptr,nullptr);
        QMessageBox::critical(this, "Error", ErrorMessage, QMessageBox::Yes);
    }
}

controlPanel::~controlPanel()
{
    delete centralWidget;
    delete socket;
}

bool controlPanel::getStatus()
{
    return okay;
}

void controlPanel::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Regulacja predykcyjna",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        symProces->close();
        event->accept();
    }
}
