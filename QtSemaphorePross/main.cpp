#include <QCoreApplication>
#include <QThread>
#include <QSemaphore>
#include <QTime>
#include <iostream>


const int datasize = 10;
const int buffersize = 1;

QSemaphore freesapce(buffersize);
QSemaphore usedspace(0);

class producer:public QThread   //生产者
{
protected:
    void run()
    {
        // qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        // qsrand(NULL);

        for(int i=0;i<datasize;i++)
        {
            freesapce.acquire();//获取资源
            std::cerr<<i<<":producer-->";
            usedspace.release();//释放资源
        }
    }
};

class consumer:public QThread
{
protected:
    void run()
    {
        for(int i=0;i<datasize;i++)
        {
            usedspace.acquire();//获取资源
            std::cerr<<i<<":consumer\n";
            freesapce.release();//释放资源
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    producer p;
    consumer c;
    p.start();
    c.start();

    p.wait();
    c.wait();

    return QCoreApplication::exec();
}
