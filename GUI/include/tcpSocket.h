#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class tcpSocket : public QObject {
    Q_OBJECT
public:
    explicit tcpSocket(QObject *parent = 0);

    void doConnect(QString addr, int port);
    void sendParameters(double new_Y, int new_N, int new_Nu, double new_lambda);
    void sendYoutput(double new_Y);
    bool getCon();

signals:
    void stateDisconected();

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;
    QString address;
    bool con = true;

};

#endif // TCPSOCKET_H
