#ifndef QFILESDIALOG_H
#define QFILESDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>  //水平布局
#include <QVBoxLayout>  //垂直布局

#include <QFileDialog>

class QFilesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QFilesDialog(QWidget *parent = nullptr);
    ~QFilesDialog() override;

private:
    QLabel* FileNameLabel;
    QLineEdit* FileNameLineEdit;
    QPushButton* FileButton;
    QLabel* FileSizeLabel;
    QLineEdit* FileSizeLabelLineEdit;
    QPushButton* GetFileInfoButton;

private slots:
    void GetFileInfo();//用于打开文件
    void GetFileSizeFunc();//用于获取文件大小
};
#endif // QFILESDIALOG_H
