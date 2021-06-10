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

    void doConnect();
    void doConnect(QString addr);
    void sendParameters(int new_N, int new_Nu, double new_lambda);
    void sendYoutput();
signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;

};

#endif // TCPSOCKET_H
