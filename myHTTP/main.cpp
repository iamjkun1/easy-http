#include "mainwindow.h"

#include <QApplication>
//简单网页浏览器。显示链接网址，，实现一般页面文件的下载，并且显示下载进度
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
