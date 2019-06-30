#include "mainwindow.h"
#include "downloader.h"
#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Downloader Download;
    QSplashScreen *startScreen = new QSplashScreen;
    startScreen->setPixmap(QPixmap(":/img/Weather.jpg"));
    startScreen->setFixedSize(600,400);
    startScreen->show();
    QTimer::singleShot(3000,startScreen,&QSplashScreen::close);
    MainWindow MainWindow;
    QTimer::singleShot(3000,&MainWindow,&MainWindow::show);
    return a.exec();
}
