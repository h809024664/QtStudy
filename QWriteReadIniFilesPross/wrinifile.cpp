#include "wrinifile.h"
#include <QSettings>
#include <QDebug>


void WriteIniFiles()//写配置文件
{
    //直接使用QSettings类读写INI文件
    QSettings *ConfigWriteIniFiles = new QSettings("MySQLFiles.ini",QSettings::IniFormat);

    //向ini文件当中写入数据信息
    //第一节的第一个参数，后面就以此类推
    ConfigWriteIniFiles->setValue("/database/ip","192.168.12.189");
    ConfigWriteIniFiles->setValue("/database/port","3308");
    ConfigWriteIniFiles->setValue("/database/user","root");
    ConfigWriteIniFiles->setValue("/database/password","123456");


    ConfigWriteIniFiles->setValue("/notice/version","5.6");
    ConfigWriteIniFiles->setValue("/notice/datetime","2026-04-02");


    //向ini文件写入完成后，删除指针
    delete ConfigWriteIniFiles;

}

void ReadIniFiles()//读配置文件
{
    QSettings *ConfigReadIniFiles = new QSettings("MySQLFiles.ini",QSettings::IniFormat);

    QString strip = ConfigReadIniFiles->value("/database/ip").toString();
    QString strport = ConfigReadIniFiles->value("/database/port").toString();
    QString struser = ConfigReadIniFiles->value("/database/user").toString();
    QString strpassword = ConfigReadIniFiles->value("/database/password").toString();
    QString strversion = ConfigReadIniFiles->value("/notice/version").toString();
    QString strdatetime = ConfigReadIniFiles->value("/notice/datetime").toString();

    //输出读取配置文件的参数信息
    qDebug()<<"读取INI配置文件参数选项如下：";
    qDebug()<<"MySQL IP地址："<<strip.toUtf8().data();//去除双引号
    qDebug()<<"MySQL 端口号："<<strport.toUtf8().data();//去除双引号
    qDebug()<<"MySQL 用户名："<<struser.toUtf8().data();//去除双引号
    qDebug()<<"MySQL 密码："<<strpassword.toUtf8().data();//去除双引号
    qDebug()<<"软件版本号："<<strversion.toUtf8().data();//去除双引号
    qDebug()<<"日期："<<strdatetime.toUtf8().data();//去除双引号




    delete ConfigReadIniFiles;
}
void ReadIniFilesIsKey()
{
    QSettings setting("./MySQLFiles.ini",QSettings::IniFormat);
    foreach(QString key,setting.allKeys())
    {
        qDebug()<<key.toUtf8().data()<<":"<<setting.value(key).toString().toUtf8().data();
    }

}
