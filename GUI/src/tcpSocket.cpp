#include "../include/tcpSocket.h"

tcpSocket::tcpSocket(QObject *parent) :
    QObject(parent)
{
}


void tcpSocket::doConnect(QString addr, int port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));


    qDebug() << "connecting...";
    socket->connectToHost(addr, port);
    address = addr;
    if(!socket->waitForConnected(5000))
    {

        qDebug() << "Error: " << socket->errorString();
        con = false;
    }

}

void tcpSocket::connected()
{
    qDebug() << "Connected to regulation QEMU";

    QByteArray arr;
    u_int8_t ACK = 1;
    u_int8_t length = 0;

    char *byte1 = (char*)&ACK;
    char *byte2 = (char*)&length;
    arr.append(byte1);
    arr.append(byte2);
    socket->write(arr, 2);

}

void tcpSocket::disconnected()
{
    qDebug() << "Disconnected";
    emit(stateDisconected());
}

void tcpSocket::readyRead()
{
    qDebug() << "Reading...";
    qDebug() << socket->readAll();
}

void  tcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void tcpSocket::sendParameters(double new_Y, int new_N, int new_Nu, double new_lambda)
{

    QByteArray arr;
    u_int8_t SETALL = 6;
    double y = new_Y;
    u_int8_t p1 = new_N;
    u_int8_t p2 = new_Nu;
    double p3 = new_lambda;

    u_int8_t length = 4 * sizeof(u_int8_t) + 2 * sizeof(double);

    char *byte1 = (char*)&SETALL;
    char *byte2 = (char*)&length;
    char *byte3 = (char*)&y;
    char *byte4 = (char*)&p1;
    char *byte5 = (char*)&p2;
    char *byte6 = (char*)&p3;

    arr.append(byte1,1);
    arr.append(byte2,1);
    arr.append(byte3,8);
    arr.append(byte4,1);
    arr.append(byte5,1);
    arr.append(byte6,8);
    qDebug() << "Sending parameters..."<< arr << " "<< length;
    socket->write(arr, length);

}

void tcpSocket::sendYoutput(double new_Y){
    QByteArray arr;
    u_int8_t SET = 5;
    double y = new_Y;
    u_int8_t length = 2 * sizeof(u_int8_t) + 1 * sizeof(double);

    char *byte1 = (char*)&SET;
    char *byte2 = (char*)&length;
    char *byte3 = (char*)&y;
    arr.append(byte1,1);
    arr.append(byte2,1);
    arr.append(byte3,8);
    qDebug() << "Sending Y..."<< arr << " "<< length;
    socket->write(arr, length);

}

bool tcpSocket::getCon()
{
    return !(socket->state() == QAbstractSocket::UnconnectedState);
}
