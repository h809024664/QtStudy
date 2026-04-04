#include "qjsonoper.h"
#include "ui_qjsonoper.h"

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>    //JSON文档
#include <QJsonObject>      //JSON对象
#include <QJsonParseError>  //JSON异常捕捉

QJsonOper::QJsonOper(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QJsonOper)
{
    ui->setupUi(this);
}

QJsonOper::~QJsonOper()
{
    delete ui;
}

//将数据信息写入JSON文件
void QJsonOper::on_pushButtonWriteJson_clicked()
{
    //1:创建json对象
    QJsonObject mysqlinfo;

    mysqlinfo.insert("ip","192.168.0.125");
    mysqlinfo.insert("port", 3308);
    mysqlinfo.insert("user","root");
    mysqlinfo.insert("password","123456");

    QJsonObject jsonifo;
    jsonifo.insert("code",1);
    jsonifo.insert("dbmsg","MySQL数据库配置参数");
    jsonifo.insert("data",mysqlinfo);//将json对象作为Json对象插入数据值

    //2:创建JSON文档
    QJsonDocument jsondoc;
    jsondoc.setObject(jsonifo);

    //3:创建文件
    QFile qfiles("./databasejsonfiles.json");
    if(qfiles.open(QIODevice::WriteOnly))
    {
        qfiles.write(jsondoc.toJson());
        qfiles.close();
        qDebug()<<"Json数据文件写入成功";
    }
    QMessageBox::information(this,"写入成功","json数据文件写入成功");
}


void QJsonOper::on_pushButtonReadJson_clicked()
{
    //1:
    QString strjson;
    QFile qfiles("./databasejsonfiles.json");
    if(qfiles.open(QIODevice::ReadOnly))
    {
        strjson = qfiles.readAll();
        qfiles.close();
    }
    QJsonParseError jsonerror;//返回json解析错误的时候，报告错误信息
    QJsonDocument jsondoc = QJsonDocument::fromJson(strjson.toUtf8(),&jsonerror);

    QString strtemp;
    QString strmsg;
    if(!jsondoc.isEmpty() && (jsonerror.error == QJsonParseError::NoError))
    {
        //只要jsondoc不为空，且jsonerror没有错误
        //将它转化为json对象
        QJsonObject json = jsondoc.object();
        QJsonValue code = json.value("code");
        QJsonValue data = json.value("data");

        //检查数据
        if(code.isUndefined() || code.toDouble()!=1 || data.isUndefined() || !data.isObject())
        {
            qDebug()<<"转换JSON数据错误，请重新检查";
            QMessageBox::critical(this,"错误","转换JSON数据错误，请重新检查");
        }

        //如果没有错误，读取data数据信息
        QJsonObject databaseinfo = data.toObject();
        QJsonValue dbip = databaseinfo.value("ip");
        QJsonValue dbport = databaseinfo.value("port");
        QJsonValue dbuser = databaseinfo.value("user");
        QJsonValue dbpassword = databaseinfo.value("password");

        //检查接口是否正确
        if(dbip.isUndefined() || dbport.isUndefined() || dbuser.isUndefined() || dbpassword.isUndefined())
        {
            qDebug()<<"接口错误，请重新检查";
            QMessageBox::critical(this,"错误","接口错误，请重新检查");
            exit(100);
        }

        QString strip = dbip.toString();
        int iport = dbport.toInt();
        QString struser = dbuser.toString();
        QString strpassword = dbpassword.toString();

        //判断每一项是否为空
        if(strip.isEmpty() || struser.isEmpty() || strpassword.isEmpty())
        {
            qDebug()<<"此数据不能为空，请重新检查";
            QMessageBox::critical(this,"错误","此数据不能为空，请重新检查");
            exit(100);
        }

        qDebug()<<"数据库ip地址:"<<strip.toUtf8().data();
        qDebug()<<"数据库端口:"<<iport;
        qDebug()<<"数据库用户:"<<struser.toUtf8().data();
        qDebug()<<"数据库密码:"<<strpassword.toUtf8().data();


        //拼接字符串

        strmsg+="JSON配置参数";
        strmsg+="\n数据库IP地址:"+strip;
        strmsg+="\n数据库端口号:"+QString::number(iport,10);
        strmsg+="\n数据库用户:"+struser;
        strmsg+="\n数据库密码:"+strpassword;
    }
    QMessageBox::information(this,"读取成功",strmsg,QMessageBox::Yes);
}

