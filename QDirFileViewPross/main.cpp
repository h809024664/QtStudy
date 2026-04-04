#include "dqdirfileviews.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DQDirFileViews w;
    w.show();
    return QCoreApplication::exec();
}
