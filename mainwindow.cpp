#include "mainwindow.h"
#include "weather.h"
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

    QDate currentDate = QDateTime::currentDateTime().date();
    mainInfo = weatherDoc.object().value("main").toObject();
    systemInfo = weatherDoc.object().value("sys").toObject();
    Weather currentWeather;
    currentWeather.date = currentDate.toString("d.MM.yyyy");
    currentWeather.time = QDateTime::currentDateTime().time().toString();
    currentWeather.weatherData.city = weatherDoc.object().value("name").toString();
    currentWeather.weatherData.region = systemInfo.value("country").toString();
    currentWeather.weatherData.temperature = QString::number(mainInfo.value("temp").toDouble() -273);

    _textLabel->setText(currentWeather.weatherData.city
                        + "\n" + currentWeather.weatherData.region
                        + "\n" + currentWeather.weatherData.temperature
                        + " °C\n" + currentWeather.date
                        + "\n" + currentWeather.time);
    setLayout(mainLayout);
}
MainWindow::~MainWindow()
{
    this->destroy();
}

