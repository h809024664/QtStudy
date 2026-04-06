#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QAbstractSocket>  //它是TcpSocket和QUdpSocket的基类
#include <QWebSocketServer>
#include <QWebSocket>
#include <QJsonDocument>    //提供读取和写入JSON文档的相关方法
#include <QJsonObject>      //JSON对象


class QWebSocket;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    Ui::Widget *ui;


    //自定义
    class QWebSocketServer *websocketserver;
    QList<QWebSocket*> websocketlist;   //存储客户端

    void getnewconnect();   //获取新连接
    void reciveMsg(const QString &msg);

public slots:
    void onerrorFunc(QAbstractSocket::SocketError error);
private slots:
    void on_pushButton_SendData_clicked();
};
#endif // WIDGET_H
