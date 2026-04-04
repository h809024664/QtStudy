#include "writereadxml.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WriteReadXml w;
    w.show();
    return QCoreApplication::exec();
}
