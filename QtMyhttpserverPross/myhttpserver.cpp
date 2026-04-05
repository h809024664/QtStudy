#include "myhttpserver.h"
#include <QDebug>

MyHttpServer::MyHttpServer(QObject *parent)
    :QObject(parent)
{
    ser = new QTcpServer(this);

    //信号与槽函数连接
    connect(ser,&QTcpServer::newConnection,this,&MyHttpServer::connection);

    if(!ser->listen(QHostAddress::Any,8080))
    {
        qDebug()<<"致命错误：Web服务器没有启动，请重新检查";
    }
    else
    {
        qDebug()<<"正常启动：Web服务器端口8080，等待客户端连接....";
    }

}

MyHttpServer::~MyHttpServer()
{
    socket->close();
}

qint64 MyHttpServer::bytesAvailable() const
{

}

void MyHttpServer::connection()
{
    socket=ser->nextPendingConnection();

    while(!(socket->waitForReadyRead(100)));

    char webdata[1000];
    int sv = socket->read(webdata,1000);
    qDebug()<<"正常运行：从浏览器读取数据信息......"<<QString(webdata);

    socket->write("HTTP/1.1 200 OK\r\n");
    socket->write("Content-Type:text/html; charset=utf-8\r\n");
    socket->write("Connection:close\r\n");
    socket->write("\r\n");//每秒刷新Web浏览器

    socket->write("<!DOCTYPE>"
                  "<html>"
                  "<header>"
                  "<meta http-equiv=\"refresh\" content=\"1\">"
                  "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>"
                  "<title>httpserver</title>"
                  "</header>"
                  "<body>客户端已经连接到HttpServer服务器秒数为：");
    QByteArray bytesary;
    static qint16 icount;//用于在浏览器上显示的统计访问数字
    bytesary.setNum(icount++);
    socket->write(bytesary);
    socket->write("</html>");

    socket->flush();

    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    socket->disconnectFromHost();

}
