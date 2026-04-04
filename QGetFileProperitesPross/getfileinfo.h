#ifndef GETFILEINFO_H
#define GETFILEINFO_H

#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>


#include <QFileDialog>  //引用文件对话框
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>

class GetFileInfo : public QDialog
{
    Q_OBJECT

public:
    explicit GetFileInfo(QWidget *parent = nullptr);
    ~GetFileInfo() override;

private:
    //文件名称
    QLabel *labelfilename;
    QLineEdit *qlineeditfilename;
    QPushButton *qpushbuttongetfilename;

    //文件大小
    QLabel *labelfilesize;
    QLineEdit *qlineeditfilesize;

    //文件创建时间
    QLabel *labelfilecreatetime;
    QLineEdit *qlineeditfilecreatetime;

    //文件最后修改时间
    QLabel *labelfilemodifytime;
    QLineEdit *qlineeditfilemodifytime;

    //文件访问时间
    QLabel *labelfileaccesstime;
    QLineEdit *qlineeditfileaccesstime;

    //文件属性以及复选按钮
    QLabel *qlabelfileattribute;
    QCheckBox *qcheckboxisfile;
    QCheckBox *qcheckboxishide;
    QCheckBox *qcheckboxisreadable;
    QCheckBox *qcheckboxiswrite;
    QCheckBox *qcheckboxisexecute;

    QPushButton *qpushbuttongetfileattributeinfo;

//声明槽函数
private slots:
    void getfilepathandname();
    void getfileattributeinfo();

};
#endif // GETFILEINFO_H
