#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide(); //隐藏进度条
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));

}

//界面:显示
void MainWindow::replyFinished(QNetworkReply *reply) {

    QString all = reply->readAll();
    ui->textBrowser->setText(all);
    reply->deleteLater();
}

//网络请求
void MainWindow::startRequest(QUrl url){

    reply = manager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDateReadProgress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
//    connect(reply, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

void MainWindow::httpReadyRead(){

    if(file)
        file->write(reply->readAll());
}

void MainWindow::updateDateReadProgress(qint64 bytesRead, qint64 totalBytes){


    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

//下载完成后，隐藏进度条，删除reply和file对象
void MainWindow::httpFinished(){

    ui->progressBar->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}


void MainWindow::on_pushButton_clicked()
{

    url = ui->lineEdit->text();
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    file = new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly)){

        qDebug()<<"file open error";
        delete file;
        file = 0;
        return;
    }

    startRequest(url);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}

