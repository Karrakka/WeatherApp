#include "start.h"
#include "mainwindow.h"
Start::Start(QWidget *parent) :
    QDialog(parent)
{
    resize(600,400);
    setMinimumSize(500,400);
}
Start::~Start()
{
    this->destroy();
}

