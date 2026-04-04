#include "updcomm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UpdComm w;
    w.show();
    return QCoreApplication::exec();
}
