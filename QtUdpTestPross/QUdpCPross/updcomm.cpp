#include "updcomm.h"
#include "ui_updcomm.h"

UpdComm::UpdComm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UpdComm)
{
    ui->setupUi(this);

    QString str = GetLocalIpAddress();//调用此函数获取本机IP地址
    ui->comboBox_TargetIp->addItem(str);    //将IP地址显示到combox控件

    udpsocket = new QUdpSocket(this);
    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(SocketReadyReadData()));

}

UpdComm::~UpdComm()
{
    delete ui;
}

//启动服务
void UpdComm::on_pushButton_Start_clicked()
{
    quint16 port = ui->spinBox_BindPort->value();//本机UDP端口
    if(udpsocket->bind(port))
    {
        ui->plainTextEdit_DispMsg->appendPlainText("**********绑定成功**********");
        ui->plainTextEdit_DispMsg->appendPlainText("**********绑定成功**********:"+QString::number(udpsocket->localPort()));
        ui->pushButton_Start->setEnabled(false);
        ui->pushButton_Stop->setEnabled(true);
    }
    else
    {
        ui->plainTextEdit_DispMsg->appendPlainText("**********绑定失败**********");
    }
}


void UpdComm::on_pushButton_Stop_clicked()
{
    udpsocket->abort();
    ui->pushButton_Start->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
    ui->plainTextEdit_DispMsg->appendPlainText("**********停止服务**********");
}


void UpdComm::on_pushButton_SendMsg_clicked()
{
    QString targetIpAddress = ui->comboBox_TargetIp->currentText(); //获取目标IP地址
    QHostAddress targetadress(targetIpAddress);

    quint16 targetport = ui->spinBox_TargetPort->value();//获取端口
    QString strmsg = ui->lineEdit_Msg->text();//获取发送信息内容

    QByteArray str = strmsg.toUtf8();
    udpsocket->writeDatagram(str,targetadress,targetport);//发送数据报信息
    ui->plainTextEdit_DispMsg->appendPlainText("[out]:"+str);
    ui->lineEdit_Msg->clear();//清除编辑框控件内容
    ui->lineEdit_Msg->setFocus();//将光标焦点定位到编辑框控件
}


void UpdComm::on_pushButton_BroadcastMsg_clicked()
{

    quint16 targetport = ui->spinBox_TargetPort->value();//获取端口
    QString strmsg = ui->lineEdit_Msg->text();//获取发送信息内容

    QByteArray str = strmsg.toUtf8();
    udpsocket->writeDatagram(str,QHostAddress::Broadcast,targetport);//发送数据报信息
    ui->plainTextEdit_DispMsg->appendPlainText("[broadcast]:"+str);
    ui->lineEdit_Msg->clear();//清除编辑框控件内容
    ui->lineEdit_Msg->setFocus();//将光标焦点定位到编辑框控件
}

QString UpdComm::GetLocalIpAddress()
{
    //根据主机名称获取IP地址
    QString strHostName = QHostInfo::localHostName();
    QHostInfo hostinfo = QHostInfo::fromName(strHostName);//通过主机名称获取IP地址

    QString strLocalIp = "";

    QList<QHostAddress> addresslist = hostinfo.addresses();    //IP地址列表
    if(!addresslist.isEmpty())
    {
        for(int i=0;i<addresslist.count();i++)
        {
            QHostAddress hostaddr = addresslist.at(i);
            if(QAbstractSocket::IPv4Protocol == hostaddr.protocol())
            {
                strLocalIp = hostaddr.toString();
                break;
            }
        }
    }
    return strLocalIp;


}

void UpdComm::SocketReadyReadData()
{
    //读取接收到的数据报信息
    //用此函数返回true至少有一个数据报需要读取
    while(udpsocket->hasPendingDatagrams())
    {
        QByteArray datagrams;
        datagrams.resize(udpsocket->pendingDatagramSize());
        QHostAddress paddress;
        quint16 pport;

        //通过readDatagram()此函数都去数据报
        udpsocket->readDatagram(datagrams.data(),datagrams.size(),&paddress,&pport);

        QString strs = datagrams.data();
        QString peer = "[From:"+paddress.toString()+":"+QString::number(pport)+"]:";

        ui->plainTextEdit_DispMsg->appendPlainText(peer+strs);

    }
}

