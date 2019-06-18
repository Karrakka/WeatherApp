#include "mainwindow.h"
#include "start.h"
#include "downloader.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    Downloader Download;
    Start StartWindow;
    StartWindow.show();
    QThread::msleep(3000);
    StartWindow.close();
    MainWindow MainWindow;
    MainWindow.show();
    return a.exec();
}
