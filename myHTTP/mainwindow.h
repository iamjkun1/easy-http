#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QNetworkReply;
class QNetworkAccessManager;
#include <QUrl>
class QFile;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QNetworkAccessManager *manager;

private slots:
     void replyFinished(QNetworkReply *);
     void httpFinished();
     void httpReadyRead();
     void updateDateReadProgress(qint64, qint64);
     void on_pushButton_clicked();
public:
     void startRequest(QUrl url);


private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;
    QUrl url;
    QFile *file;


};
#endif // MAINWINDOW_H
