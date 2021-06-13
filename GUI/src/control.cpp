#include "include/control.h"



control::control()

{
    bool ok = false;
    QInputDialog addr;
    QString addrs = addr.getText(nullptr, "Ustaw polaczenie","Podaj adres ip:",QLineEdit::Normal, "192.168.1.29:65433", &ok);
    QRegExp regExp("(\\:)");
    QStringList adres = addrs.split(regExp);
    t = new tcpSocket;
    t->doConnect(adres[0], adres[1].toInt());

}

control::~control()
{


}
