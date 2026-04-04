#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpclient = new QTcpSocket(this);
    QString strip = getlocalip();
    ui->comboBox_Ip->addItem(strip);

    connect(tcpclient,SIGNAL(connected()),this,SLOT(connectfunc()));
    connect(tcpclient,SIGNAL(disconnected()),this,SLOT(disconnectfunc()));
    connect(tcpclient,SIGNAL(readyRead()),this,SLOT(socketreaddata()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getlocalip()
{
    QString hostname = QHostInfo::localHostName();
    QHostInfo hostinfo = QHostInfo::fromName(hostname);
    QString localip = "";

    QList<QHostAddress> addlist = hostinfo.addresses();
    if(!addlist.isEmpty())
    {
        for(int i=0;i<addlist.count();i++)
        {
            QHostAddress ahost = addlist.at(i);
            if(QAbstractSocket::IPv4Protocol == ahost.protocol())
            {
                localip = ahost.toString();
                break;
            }
        }
    }
    return localip;
}

void MainWindow::on_pushButton_Connect_clicked()
{
    QString addr = ui->comboBox_Ip->currentText();
    quint16 port = ui->spinBox_Port->value();
    tcpclient->connectToHost(addr,port);
}


void MainWindow::on_pushButton_Disconnect_clicked()
{
    if(tcpclient->state() == QAbstractSocket::ConnectedState)
        tcpclient->disconnectFromHost();
}


void MainWindow::on_pushButton_SendMsg_clicked()
{
    if(tcpclient->state() != QAbstractSocket::ConnectedState)
    {
        ui->plainTextEdit_lDispMsg->appendPlainText("[error]:未连接到服务器");
        return;
    }

    QString strmsg = ui->lineEdit_InputMsg->text();
    ui->plainTextEdit_lDispMsg->appendPlainText("[out]:"+strmsg);
    ui->lineEdit_InputMsg->clear();

    QByteArray str = strmsg.toUtf8();
    str.append("\n");
    tcpclient->write(str);
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    if(tcpclient->state() == QAbstractSocket::ConnectedState)
    {
        tcpclient->disconnectFromHost();
    }
    event->accept();
}

void MainWindow::connectfunc()
{
    ui->plainTextEdit_lDispMsg->appendPlainText("**********已经连接到服务器端**********");
    ui->plainTextEdit_lDispMsg->appendPlainText("**********peer address:" + tcpclient->peerAddress().toString());
    ui->plainTextEdit_lDispMsg->appendPlainText("**********peer port:" + QString::number(tcpclient->peerPort()));
    ui->pushButton_Connect->setEnabled(false);
    ui->pushButton_Disconnect->setEnabled(true);
}

void MainWindow::disconnectfunc()
{
    ui->plainTextEdit_lDispMsg->appendPlainText("**********已经断开与服务器端的连接**********");
    ui->pushButton_Connect->setEnabled(true);
    ui->pushButton_Disconnect->setEnabled(false);
}



void MainWindow::socketreaddata()
{
    while(tcpclient->canReadLine())
        ui->plainTextEdit_lDispMsg->appendPlainText("[int]:"+tcpclient->readLine());
}

