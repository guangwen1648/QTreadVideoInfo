#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openVideoFile_clicked()
{
    QString strFile;
    strFile = QFileDialog::getOpenFileName(this,"please choose an image file", "","Image FIle(*mp4)");

    FILE *fp = NULL;
    const char *filepath;
    std::string str = strFile.toStdString();
    filepath = str.c_str();
    av_register_all();
    avformat_network_init();
    inputctx = avformat_alloc_context();

    if(avformat_open_input(&inputctx,filepath,NULL,NULL)!=0)
    {
        qDebug()<<"打开视频流失败";
        return;
    }

    if(avformat_find_stream_info(inputctx,NULL)<0)
    {
        qDebug()<<"获取文件信息失败";
        return;
    }

    int videoindex = -1;
    for(int i = 0;i < inputctx->nb_streams;i++)
    {
        if(inputctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoindex = i;
            break;
        }

    }

    if(videoindex == -1)
    {
        qDebug()<<"没有发现视频流";
        return;
    }

    QString textString = QString::asprintf("inputctx->nb_streams   数据流数量:%d\n",inputctx->nb_streams);
    textString += QString::asprintf("videoindex   视频数据流索引:%d\n",videoindex);
    textString += QString::asprintf("pCodecCtx->width   宽:%d  像素\n",inputctx->streams[videoindex]->codec->width);
    textString += QString::asprintf("pCodecCtx->height   高:%d  像素\n",inputctx->streams[videoindex]->codec->height);
    textString += QString::asprintf("Total bit_rate   总比特率:%lld  kbps\n",inputctx->bit_rate/1000);
    textString += QString::asprintf("bit_rate   比特率:%lld  kbps\n",inputctx->streams[videoindex]->codec->bit_rate/1000);
    textString += QString::asprintf("inputctx->streams[videoindex]->nb_frames   帧数量:%d \n",inputctx->streams[videoindex]->nb_frames);
    //textString += QString::asprintf("inputctx->nb_streams   帧数量:%d \n",inputctx->nb_streams);
    textString += QString::asprintf("inputctx->duration   时长:%lld 个 timebase\n",inputctx->streams[videoindex]->duration);
    textString += QString::asprintf("timebase   时间基数:%d/%d  \n",inputctx->streams[videoindex]->time_base.num,inputctx->streams[videoindex]->time_base.den);
    textString += QString::asprintf("帧率   :%d 帧/秒 \n",inputctx->streams[videoindex]->avg_frame_rate.num);
    int timesec = (inputctx->streams[videoindex]->duration)/(inputctx->streams[videoindex]->time_base.den);
    textString += QString::asprintf("转换后的时长为:%d s\n",timesec);
    textString += QString::asprintf("转换格式时长为:  %2d:%2d:%2d  \n",timesec/3600,timesec%3600/60,timesec%60);
    textString += QString::asprintf("inputctx->filename   文件路径:\n%s\n",inputctx->filename);
    textString += QString::asprintf("inputctx->start_time   :%lld\n",inputctx->start_time);
    textString += QString::asprintf("Maximum size of the data read from input for determining   :%d\n",inputctx->probesize);
    textString += QString::asprintf("inputctx->nb_chapters   :%d\n",inputctx->nb_chapters);

    ui->textEdit->setText(textString);

}
