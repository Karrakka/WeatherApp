#include "mainwindow.h"
#include <QApplication>
#include "start.h"
#include <QLabel>
#include <QPixmap>
int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow w;
    Start w2;
    w.show();
    w2.show();
    return a.exec();
}
