/********************************************************************************
** Form generated from reading UI file 'start.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Start
{
public:
    QLabel *label;

    void setupUi(QDialog *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName(QString::fromUtf8("Start"));
        Start->resize(920, 640);
        label = new QLabel(Start);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 921, 641));
        label->setPixmap(QPixmap(QString::fromUtf8("img/WeatherImg.jpg")));

        retranslateUi(Start);

        QMetaObject::connectSlotsByName(Start);
    } // setupUi

    void retranslateUi(QDialog *Start)
    {
        Start->setWindowTitle(QApplication::translate("Start", "Dialog", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
