#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFileDialog>
#include<QFile>
#include <QDebug>

#ifdef __cplusplus
extern "C"
{
#endif
    #include"SDL.h"
    #include "libavformat/avformat.h"//封装格式
    #include "libavcodec/avcodec.h"//编码
    #include "libavutil/avutil.h"//
    #include "libswscale/swscale.h"//像素处理

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openVideoFile_clicked();

private:
    Ui::MainWindow *ui;
    AVFormatContext *inputctx;
};
#endif // MAINWINDOW_H
