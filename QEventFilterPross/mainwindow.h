#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>

/*
此类独立硬件图像表示形式，此图像表示形式可以直接访问像素数据，并且可以用来绘图设备。
Qt提供4个类处理图像数据：QImage/QPixmap/QBitmap/QPicture
*/
#include <QImage>
#include <QMouseEvent>
#include <QEvent>
//此类提供水平或垂直排列相关部件
#include <QBoxLayout>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;

    QLabel *labeldispinfo;

    QImage image1;
    QImage image2;
    QImage image3;

public slots:
    bool eventFilter(QObject*, QEvent*) override;//事件过滤


};
#endif // MAINWINDOW_H
