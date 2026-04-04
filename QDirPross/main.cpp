#include <QCoreApplication>

#include <QDir>
#include <QStringList>
#include <QDebug>
#include <iostream>


//自定义函数实现获取目录大小
qint64 GetDirFileInfoSizeFunc(const QString &qpath)
{
    //QDir类专门用来操作路径名称或底层文件系统，可以使用相对或绝对路径来指向一个文件/目录
    QDir qdirs(qpath);
    qint64 qsize = 0;//存放目录占据空间

    //QFileInfo类提供有关文件系统当中文件名称、路径（位置）、访问权限、文件类型等信息
    //entryInfoList函数获取过滤之后获得的文件夹下面的文件信息列表
    foreach (QFileInfo finfo, qdirs.entryInfoList(QDir::Files))
    {
        qsize = qsize+finfo.size();
    }

    //QDir::Dirs列出目录QDir::separator()不列出文件系统当中的特殊文件
    foreach(QFileInfo sDir, qdirs.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot))
    {
        qsize = qsize+GetDirFileInfoSizeFunc(sDir.filePath());
        qDebug()<<sDir.filePath();
    }

    char uint='B';
    qint64 currentdirsize = qsize;
    if(currentdirsize > 1024)
    {
        currentdirsize = currentdirsize/1024;
        uint = 'K';
        if(currentdirsize > 1024)
        {
            currentdirsize = currentdirsize/1024;
            uint = 'M';
            if(currentdirsize > 1024)
            {
                currentdirsize = currentdirsize/1024;
                uint = 'G';
                if(currentdirsize > 1024)
                {
                    currentdirsize = currentdirsize/1024;
                    uint = 'T';
                }
            }
        }
    }
    qDebug()<<"目录占据空间为："<<currentdirsize<<uint<<"\t"<<qPrintable(qpath);
    qDebug()<<"目录占据空间为："<<currentdirsize<<uint<<"\t"<<qpath;

    return qsize;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //该字符串存储路径
    QString strPath;
    strPath = QDir::currentPath(); //获取当前目录
    qDebug()<<"当前目录："<<strPath<<Qt::endl;

    //调用此函数求目录占据空间的大小
    GetDirFileInfoSizeFunc(strPath);


    return a.exec();
}
