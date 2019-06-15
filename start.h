#ifndef START_H
#define START_H

#include <QDialog>

class Start : public QDialog
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
};

#endif // START_H
