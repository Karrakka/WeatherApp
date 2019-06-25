#include "downloader.h"
Downloader::Downloader()
{
    weatherNetworkManager = new QNetworkAccessManager(this);
    forecastNetworkManager = new QNetworkAccessManager(this);

    connect(forecastNetworkManager,&QNetworkAccessManager::finished,this,&Downloader::onForecastReply);
    connect(weatherNetworkManager,&QNetworkAccessManager::finished,this,&Downloader::onWeatherReply);

    weatherRequest.setUrl(QUrl("http://api.openweathermap.org/data/2.5/weather?id=1489425&appid=5fa020e093bac007d546bbea0df938e0"));
    forecastRequest.setUrl(QUrl("http://api.openweathermap.org/data/2.5/forecast?id=1489425&appid=5fa020e093bac007d546bbea0df938e0"));

    weatherNetworkManager->get(weatherRequest);
    forecastNetworkManager->get(forecastRequest);
}
Downloader::~Downloader()
{
}
void Downloader::onWeatherReply(QNetworkReply *reply)
{
    QFile file;
    file.setFileName("weather.json");
    file.open(QIODevice::WriteOnly|QFile::Text);
    file.write(reply->readAll());
    file.close();
    reply->deleteLater();
}
void Downloader::onForecastReply(QNetworkReply *reply)
{
    QFile file;
    file.setFileName("forecast.json");
    file.open(QIODevice::WriteOnly|QFile::Text);
    file.write(reply->readAll());
    file.close();
    reply->deleteLater();
}
