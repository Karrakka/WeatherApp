#ifndef START_H
#define START_H

#include <QDialog>
#include <mainwindow.h>
#include <QTimer>
#include <QTime>
namespace Ui {
class Start;
}

class Start : public QDialog
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
private slots:

    void slotTimerAlarm();
private:
    Ui::Start *ui;

public:
    QTimer *timer;
    int timer_count=0;
};

#endif // START_H
