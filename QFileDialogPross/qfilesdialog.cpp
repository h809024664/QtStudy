#include "qfilesdialog.h"

QFilesDialog::QFilesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("QFileDialog类（文件对话框测试）");

    //1:创建控件
    FileNameLabel = new QLabel("文件名称:");
    FileNameLineEdit = new QLineEdit;
    FileButton = new QPushButton("选择...");

    FileSizeLabel = new QLabel("文件大小");
    FileSizeLabelLineEdit = new QLineEdit;

    GetFileInfoButton = new QPushButton("获取文件大小信息");

    //2:排列布局
    QGridLayout *glayout = new QGridLayout;
    glayout->addWidget(FileNameLabel,0,0);
    glayout->addWidget(FileNameLineEdit,0,1);
    glayout->addWidget(FileButton,0,2);

    glayout->addWidget(FileSizeLabel,1,0);
    glayout->addWidget(FileSizeLabelLineEdit,1,1,1,2);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(GetFileInfoButton);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(glayout);
    vlayout->addLayout(hlayout);

    connect(FileButton,SIGNAL(clicked()),this,SLOT(GetFileInfo()));
    connect(GetFileInfoButton,&QPushButton::clicked,this,&QFilesDialog::GetFileSizeFunc);
}

QFilesDialog::~QFilesDialog() = default;

void QFilesDialog::GetFileInfo()
{
    QString strFileName = QFileDialog::getOpenFileName(this,"打开","/","Files(*)");
    FileNameLineEdit->setText(strFileName);
}

void QFilesDialog::GetFileSizeFunc()
{
    //获取文件路径
    QString strFileName = FileNameLineEdit->text();
    QFileInfo fileinfo(strFileName);

    qint64 FileSize = fileinfo.size();
    FileSizeLabelLineEdit->setText(QString::number(FileSize));
}
