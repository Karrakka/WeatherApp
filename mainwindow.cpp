#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    resize(600,400);
    setMinimumSize(500,400);
    _textLabel = new QLabel(this);
    _textLabel->setAlignment(Qt::AlignCenter);
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(_textLabel);
    QFile file;
    //globPath =QFileDialog::getOpenFileName(nullptr,"","C:/","*.json");
    file.setFileName("weather.json");
    file.open(QIODevice::ReadOnly|QFile::Text);
    weatherDoc =QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
    file.close();    
    mainInfo = weatherDoc.object().value("main").toObject();
    systemInfo = weatherDoc.object().value("sys").toObject();
    QString city = weatherDoc.object().value("name").toString();
    QString country = systemInfo.value("country").toString();
    QString temperature = QString::number(mainInfo.value("temp").toDouble() -273);
    _textLabel->setText(city +" " + country + " " + temperature);
    setLayout(mainLayout);
}
MainWindow::~MainWindow()
{
    this->destroy();
}

