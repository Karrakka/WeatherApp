#include "mainwindow.h"
#include "weather.h"
#include "downloader.h"
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    resize(600,400);
    setMinimumSize(500,400);

    today = new QTextEdit(this);
    today->setReadOnly(true);

    nextDay = new QTextEdit(this);
    nextDay->setReadOnly(true);

    nextNextDay = new QTextEdit(this);
    nextNextDay->setReadOnly(true);

    nextNextNextDay = new QTextEdit(this);
    nextNextNextDay->setReadOnly(true);

    predictionQuality1Day = new QTextEdit(this);
    predictionQuality1Day->setReadOnly(true);
    predictionQuality1Day->setText("quality1");

    predictionQuality2Days = new QTextEdit(this);
    predictionQuality2Days->setReadOnly(true);
    predictionQuality2Days->setText("quality2");

    predictionQuality3Days = new QTextEdit(this);
    predictionQuality3Days->setReadOnly(true);
    predictionQuality3Days->setText("quality3");

    auto mainLayout = new QVBoxLayout();
    auto weatherLayout = new QHBoxLayout();
    mainLayout->addLayout(weatherLayout);
    mainLayout->addWidget(predictionQuality1Day);
    mainLayout->addWidget(predictionQuality2Days);
    mainLayout->addWidget(predictionQuality3Days);
    weatherLayout->addWidget(today);
    weatherLayout->addWidget(nextDay);
    weatherLayout->addWidget(nextNextDay);
    weatherLayout->addWidget(nextNextNextDay);

    //globPath =QFileDialog::getOpenFileName(nullptr,"","C:/","*.json");
    currentWeatherFile.setFileName("weather.json");
    currentWeatherFile.open(QIODevice::ReadOnly|QFile::Text);
    currentWeatherDoc =QJsonDocument::fromJson(QByteArray(currentWeatherFile.readAll()),&docError);
    currentWeatherFile.close();

    forecastWeatherFile.setFileName("forecast.json");    
    forecastWeatherFile.open(QIODevice::ReadOnly|QFile::Text);
    forecastWeatherDoc =QJsonDocument::fromJson(QByteArray(forecastWeatherFile.readAll()),&docError);
    forecastWeatherFile.close();

    Weather currentWeather;
    QDate currentDate = QDateTime::currentDateTime().date();
    mainInfo = currentWeatherDoc.object().value("main").toObject();
    systemInfo = currentWeatherDoc.object().value("sys").toObject();
    currentWeather.date = currentDate.toString("d.MM.yyyy");
    currentWeather.time = QDateTime::currentDateTime().time().toString();
    currentWeather.weatherData.city = currentWeatherDoc.object().value("name").toString();
    currentWeather.weatherData.region = systemInfo.value("country").toString();
    currentWeather.weatherData.temperature = QString::number(mainInfo.value("temp").toDouble() -273);

    Weather forecastWeather[3];

    docArray = QJsonValue(forecastWeatherDoc.object().value("list")).toArray();
    int j=0;
    for (int i=6;i<=22;i+=8)
    {
        forecastMainInfo = docArray.at(i).toObject().value("main").toObject();
        forecastWeather[j].weatherData.temperature = QString::number(forecastMainInfo.value("temp").toDouble() -273);
        j++;
    }
    today->setText("Сегодня: "+ currentWeather.weatherData.temperature + "°C");
    nextDay->setText("Завтра: "+ forecastWeather[0].weatherData.temperature + "°C");
    nextNextDay->setText("Послезавтра: "+ forecastWeather[1].weatherData.temperature + "°C");
    nextNextNextDay->setText("Послепослезавтра: "+ forecastWeather[2].weatherData.temperature+"°C");

    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    this->destroy();

}

