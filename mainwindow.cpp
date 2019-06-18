#include "mainwindow.h"
#include "weather.h"
#include "downloader.h"
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    resize(600,400);
    setMinimumSize(500,400);
    _textLabel = new QLabel(this);
    _textLabel->setAlignment(Qt::AlignCenter);
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(_textLabel);

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

    _textLabel->setText(currentWeather.weatherData.city
                        + "\n" + currentWeather.weatherData.region
                        + "\n Сейчас: " + currentWeather.weatherData.temperature
                        + " °C\n Завтра: " + forecastWeather[0].weatherData.temperature
                        + " °C\n Послеавтра: " + forecastWeather[1].weatherData.temperature
                        + " °C\n Послепослезавтра: " + forecastWeather[2].weatherData.temperature
                        + " °C\n" + currentWeather.date
                        + "\n" + currentWeather.time);
    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    this->destroy();

}

