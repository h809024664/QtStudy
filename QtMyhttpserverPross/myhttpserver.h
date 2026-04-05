#ifndef MYHTTPSERVER_H
#define MYHTTPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpServer(QObject *parent = nullptr);
    ~MyHttpServer();

public:
    QTcpSocket *socket;
private:
    QTcpServer *ser;
    qint64 bytesAvailable() const;

public slots:
    void connection();//连接
};

#endif // MYHTTPSERVER_H
