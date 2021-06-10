#include "include/tcpSocket.h"

tcpSocket::tcpSocket(QObject *parent) :
    QObject(parent)
{
}

void tcpSocket::doConnect()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));

    qDebug()<<sizeof(char);
    qDebug() << "connecting...";
    socket->connectToHost("192.168.1.31", 51717);
    if(!socket->waitForConnected(5000))
        {
            qDebug() << "Error: " << socket->errorString();
        }

}

void tcpSocket::doConnect(QString addr)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));

    qDebug() << "connecting...";
    socket->connectToHost(addr, 51717);
    if(!socket->waitForConnected(5000))
        {
            qDebug() << "Error: " << socket->errorString();
        }

}

void tcpSocket::connected()
{
    qDebug() << "Connected...";
    /*double z = 12.3;
    char *v = (char*)&z;
    qDebug() << v;
    double *i = (double*) v;*/
    //socket->write(v);
    //int x = 12;
    //qDebug()<<static_cast<char*>(static_cast<void*>(&x));
    //double z = 12.4;
    //char *v = (char*)&z;
    //qDebug()<<sizeof(v);
    //socket->write(v,sizeof(v));
    socket->write("HEAD");
}

void tcpSocket::disconnected()
{
    qDebug() << "Disconnected";
}

void tcpSocket::readyRead()
{
    qDebug() << "Reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}

void  tcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void tcpSocket::sendParameters(int new_N, int new_Nu, double new_lambda)
{
    u_int8_t SETALL = 6;
    u_int8_t p1 = new_N;
    u_int8_t p2 = new_Nu;
    double p3 = new_lambda;

    u_int8_t length = sizeof(u_int8_t) + sizeof(u_int8_t) + sizeof(double);

    char *byte1 = (char*)&SETALL;
    char *byte2 = (char*)&length;
    char *byte3 = (char*)&p1;
    char *byte4 = (char*)&p2;
    char *byte56 = (char*)&p3;
    QByteArray arr;
    arr.push_back(byte1);


    arr.append(byte1, sizeof(u_int8_t));
    arr.append(byte2, sizeof(u_int8_t));
    arr.append(byte3, sizeof(u_int8_t));
    arr.append(byte4, sizeof(u_int8_t));
    arr.append(byte56, sizeof(double));
    qDebug()<<arr.toBase64();
    //socket->write(arr);

}
