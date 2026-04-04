#include <QCoreApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //1:创建QFile对象，制定操作的相关文件
    QFile qfs("d:/qfiletext.txt");

    //2:打开文件进行写操作 ReadOnly ReadWrite Append Truncate
    if(!qfs.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"打开文件失败，请重新检查";
    }
    else
    {
        qDebug()<<"打开成功。";
    }

    //3:向打开的文件写数据信息
    qfs.write("xxxx");
    qfs.write("Qt开发工程师\n");
    qfs.write("C/C++后台开发");

    //4:关闭文件
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
    //定义字符指针
    char *pStr = new char[200];
    qint64 rcount=qfs.readLine(pStr,200);

    while((rcount!=0) && (rcount!=-1))
    {
        qDebug()<<pStr;
        rcount=qfs.readLine(pStr,200);
    }
    qfs.close();

    return QCoreApplication::exec();
}
