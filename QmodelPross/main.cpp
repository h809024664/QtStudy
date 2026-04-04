#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //将下面两条语句注释操作
    // MainWindow w;
    // w.show();

    QFileSystemModel model; //用于获取磁盘文件目录的数据模型
    QTreeView tree; //树形视图
    QListView list;//列表视图
    QTableView table;//表视图

    model.setRootPath(QDir::rootPath()); // 设置要显示的根路径

    //设置数据模型
    tree.setModel(&model);
    list.setModel(&model);
    table.setModel(&model);

    tree.setSelectionMode(QAbstractItemView::MultiSelection);
    list.setSelectionModel(tree.selectionModel());
    table.setSelectionModel(tree.selectionModel());

    QObject::connect(&tree,SIGNAL(doubleClicked(QModelIndex)),&list,SLOT(setRootIndex(QModelIndex)));
    QObject::connect(&tree,SIGNAL(doubleClicked(QModelIndex)),&table,SLOT(setRootIndex(QModelIndex)));


    QSplitter* qsp = new QSplitter;
    qsp->addWidget(&tree);
    qsp->addWidget(&list);
    qsp->addWidget(&table);

    qsp->show();
    qsp->setWindowTitle("模型(Model)--测试操作");
    return QCoreApplication::exec();
}
