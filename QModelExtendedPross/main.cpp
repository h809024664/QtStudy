#include "mainwindow.h"

#include <QApplication>
#include "modelextended.h"
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    ModelExtended modelextended;
    QTableView view;
    view.setModel(&modelextended);
    view.setWindowTitle("ModelExtended模型扩展--测试操作");
    view.resize(500,300);
    view.show();


    return QCoreApplication::exec();
}
