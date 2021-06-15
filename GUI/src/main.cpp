#include <QApplication>
#include "include/controlPanel.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    controlPanel pc;

    return app.exec();
}
