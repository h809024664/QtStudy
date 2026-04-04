#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTransform>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Qt事件过滤器--测试程序");


    label1 = new QLabel;
    image1.load(":/images/a.jpeg");
    label1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label1->setPixmap(QPixmap::fromImage(image1));


    label2 = new QLabel;
    image2.load(":/images/b.jpeg");
    label2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label2->setPixmap(QPixmap::fromImage(image2));


    label3 = new QLabel;
    image3.load(":/images/c.jpeg");
    label3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label3->setPixmap(QPixmap::fromImage(image3));

    //UI布局
    labeldispinfo = new QLabel("鼠标按键提示信息！");
    labeldispinfo->setAlignment(Qt::AlignHCenter);   //AlignCenter窗口中兴对齐

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1);
    hlayout->addWidget(label2);
    hlayout->addWidget(label3);

    QWidget *wgt = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(wgt);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(labeldispinfo);

    setCentralWidget(wgt);//中心窗口部件

    //安装事件过滤
    label1->installEventFilter(this);
    label2->installEventFilter(this);
    label3->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == label1)
    {
        if(event->type() == QEvent::MouseButtonPress)//鼠标按键，发生在客户区域
        {
            QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
            if(mevent->button() & Qt::LeftButton)
            {
                labeldispinfo->setText("鼠标左键被按下：[左边图片]");
            }
            else if(mevent->button() & Qt::MiddleButton)
            {
                labeldispinfo->setText("鼠标中键被按下：[左边图片]");
            }
            else if(mevent->button() & Qt::RightButton)
            {
                labeldispinfo->setText("鼠标右键被按下：[左边图片]");
            }

            QTransform transform;
            transform.scale(1.5,1.5);
            QImage tempimage = image1.transformed(transform);
            label1->setPixmap(QPixmap::fromImage(tempimage));
        }
        if(event->type()== QEvent::MouseButtonRelease)
        {
            labeldispinfo->setText("鼠标按键已经释放：[左边图片]");
            label1->setPixmap(QPixmap::fromImage(image1));
        }
    }
    else if(watched == label2)
    {
        if(event->type() == QEvent::MouseButtonPress)//鼠标按键，发生在客户区域
        {
            QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
            if(mevent->button() & Qt::LeftButton)
            {
                labeldispinfo->setText("鼠标左键被按下：[中间图片]");
            }
            else if(mevent->button() & Qt::MiddleButton)
            {
                labeldispinfo->setText("鼠标中键被按下：[中间图片]");
            }
            else if(mevent->button() & Qt::RightButton)
            {
                labeldispinfo->setText("鼠标右键被按下：[中间图片]");
            }

            QTransform transform;
            transform.scale(1.5,1.5);
            QImage tempimage = image2.transformed(transform);
            label2->setPixmap(QPixmap::fromImage(tempimage));
        }
        if(event->type()== QEvent::MouseButtonRelease)
        {
            labeldispinfo->setText("鼠标按键已经释放：[中间图片]");
            label2->setPixmap(QPixmap::fromImage(image2));
        }
    }
    else if(watched == label3)
    {
        if(event->type() == QEvent::MouseButtonPress)//鼠标按键，发生在客户区域
        {
            QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
            if(mevent->button() & Qt::LeftButton)
            {
                labeldispinfo->setText("鼠标左键被按下：[右边图片]");
            }
            else if(mevent->button() & Qt::MiddleButton)
            {
                labeldispinfo->setText("鼠标中键被按下：[右边图片]");
            }
            else if(mevent->button() & Qt::RightButton)
            {
                labeldispinfo->setText("鼠标右键被按下：[右边图片]");
            }

            QTransform transform;
            transform.scale(1.5,1.5);
            QImage tempimage = image3.transformed(transform);
            label3->setPixmap(QPixmap::fromImage(tempimage));
        }
        if(event->type()== QEvent::MouseButtonRelease)
        {
            labeldispinfo->setText("鼠标按键已经释放：[右边图片]");
            label3->setPixmap(QPixmap::fromImage(image3));
        }
    }
    return QMainWindow::eventFilter(watched,event);
}
