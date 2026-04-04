#include "qfilesdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFilesDialog w;
    w.show();
    return QCoreApplication::exec();
}
