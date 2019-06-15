#include "mainwindow.h"
#include "start.h"
#include "downloader.h"
#include <QApplication>
#include <QThread>
int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    Downloader Download;
    MainWindow MainWindow;
    Start StartWindow;
    StartWindow.show();
    QThread::msleep(3000);
    StartWindow.close();
    MainWindow.show();
    return a.exec();
}
