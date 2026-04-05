#include <QCoreApplication>
#include "myhttpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyHttpServer ser;


    return QCoreApplication::exec();
}
