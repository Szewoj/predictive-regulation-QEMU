#ifndef CONTROL_H
#define CONTROL_H

#include "include/regulacja.h"
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class control
{


public:
    control();
    ~control();
    tcpSocket *t;

};
#endif // CONTROL_H
