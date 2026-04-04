#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitTableViewFunc();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitTableViewFunc()
{
    //1.添加表头，准备数据模型
    QStandardItemModel *stuMode = new QStandardItemModel();
    stuMode->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("学号")));
    stuMode->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("姓名")));
    stuMode->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("性别")));
    stuMode->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("分数")));

    //通过api函数将数据模型绑定到QTableView
    ui->tableView->setModel(stuMode);

    //设置表哥列的宽度
    ui->tableView->setColumnWidth(0,80);

    //2.添加数据信息
    stuMode->setItem(0,0,new QStandardItem("2022001"));
    stuMode->setItem(0,1,new QStandardItem("张三"));
    stuMode->setItem(0,2,new QStandardItem("男"));
    stuMode->setItem(0,3,new QStandardItem("714"));

    stuMode->setItem(1,0,new QStandardItem("2022002"));
    stuMode->setItem(1,1,new QStandardItem("李四"));
    stuMode->setItem(1,2,new QStandardItem("男"));
    stuMode->setItem(1,3,new QStandardItem("532"));

    stuMode->setItem(2,0,new QStandardItem("2022003"));
    stuMode->setItem(2,1,new QStandardItem("王五"));
    stuMode->setItem(2,2,new QStandardItem("女"));
    stuMode->setItem(2,3,new QStandardItem("689"));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //排序
    stuMode->sort(3,Qt::DescendingOrder);

}
