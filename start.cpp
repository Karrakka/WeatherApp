#include "start.h"
#include "ui_start.h"
#include "mainwindow.h"

Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000);
}
Start::~Start()
{
    delete ui;
}
void Start::slotTimerAlarm()
{
    timer_count++;
    if (timer_count==3)
    {
        this->close();
    }
}
