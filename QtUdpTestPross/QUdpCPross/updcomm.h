#ifndef UPDCOMM_H
#define UPDCOMM_H

#include <QMainWindow>
#include <QUdpSocket>   //用于发送和接收UDP数据报
#include <QtNetwork>



QT_BEGIN_NAMESPACE
namespace Ui {
class UpdComm;
}
QT_END_NAMESPACE

class UpdComm : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdComm(QWidget *parent = nullptr);
    ~UpdComm() override;

private slots:
    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_SendMsg_clicked();

    void on_pushButton_BroadcastMsg_clicked();

private:
    Ui::UpdComm *ui;

    //自定义函数获取本机的IP地址
public:
    QUdpSocket *udpsocket;
    QString GetLocalIpAddress();//获取本机IP地址
    //自定义槽
private slots:
    void SocketReadyReadData();//读取socket传输数据信息




};
#endif // UPDCOMM_H
