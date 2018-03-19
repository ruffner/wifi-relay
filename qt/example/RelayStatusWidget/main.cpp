#include "relaystatuswidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RelayStatusWidget w;
    w.show();

    return a.exec();
}
