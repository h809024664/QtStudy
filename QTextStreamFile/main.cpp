#include <QCoreApplication>

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDataStream>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile qfs("d:/qtextstreamfile.txt");

    if(!qfs.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"打开文件失败，请重新检查";
    }
    else
    {
        qDebug()<<"打开成功。";
    }

    QTextStream qtextstreamwrite(&qfs);

    //向文件写入数据
    qtextstreamwrite<<(QString)"测试写入";
    qtextstreamwrite<<(QString)"sljfskljflskajAAAA我数据的风口浪尖阿斯利康积分萨德里克解放路";

    qfs.close();

    //读取文件数据
    if(!qfs.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"打开文件失败，请重新检查";
    }
    else
    {
        qDebug()<<"打开成功。";
    }

    QTextStream qtextstreamread(&qfs);
    while(!qtextstreamread.atEnd())
    {
        QString strtemp;
        qtextstreamread>>strtemp;
        qDebug()<<strtemp;
    }
    qfs.close();

    return a.exec();
}
