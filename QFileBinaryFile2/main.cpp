#include <QCoreApplication>

#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //将qnumber里面的数据写入到文件
    qint32 qnumber[3] = {1,2,3};

    //将qnumber以二进制方式存储到字节数组当中
    QByteArray bytearry;
    bytearry.resize(sizeof(qnumber));
    for(int i=0;i<3;i++)
    {
        //for循环利用指针将每个整数复制到字符数组里面去
        memcpy(bytearry.data()+i*sizeof(qint32),&(qnumber[i]),sizeof(qint32));
    }

    //将bytearry字节数组存储至对应文件当中QFileBinaryByte.txt
    QFile qfs("d:/QFileBinaryByte.dat");
    if(!qfs.open(QIODevice::WriteOnly))
    {
        qDebug()<<"打开文件失败，请重新检查";
    }
    else
    {
        qDebug()<<"打开成功。";
    }
    qfs.write(bytearry);
    qfs.close();

    qDebug()<<"结束";
    //读取文件数据
    if(!qfs.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开文件失败，请重新检查";
    }
    else
    {
        qDebug()<<"打开成功。";
    }
    QByteArray byteArry = qfs.readAll();

    //输出读取的二进制数据
    qDebug()<<"byteArry:"<<byteArry;

    //将二进制数据转化为整数
    char *ctemp = byteArry.data();
    while(*ctemp)
    {
        qDebug()<<*(qint32*)ctemp;
        ctemp = ctemp+sizeof(qint32);
    }


    qfs.close();


    return QCoreApplication::exec();
}
