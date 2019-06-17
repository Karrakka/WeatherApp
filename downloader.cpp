#include "downloader.h"

Downloader::Downloader(){

    weatherNetworkManager = new QNetworkAccessManager(this);
    forecastNetworkManager = new QNetworkAccessManager(this);

    connect(weatherNetworkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onWeatherReply(QNetworkReply*)));
    connect(forecastNetworkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onForecastReply(QNetworkReply*)));

    weatherRequest.setUrl(QUrl("http://api.openweathermap.org/data/2.5/weather?id=1489425&appid=5fa020e093bac007d546bbea0df938e0"));
    forecastRequest.setUrl(QUrl("http://api.openweathermap.org/data/2.5/forecast?id=1489425&appid=5fa020e093bac007d546bbea0df938e0"));

    weatherNetworkManager->get(weatherRequest);
    forecastNetworkManager->get(forecastRequest);
}
Downloader::~Downloader()
{
    delete weatherNetworkManager;
    delete forecastNetworkManager;
}
void Downloader::onWeatherReply(QNetworkReply *reply)
{
    QFile file;
    file.setFileName("weather.json");
    file.open(QIODevice::WriteOnly|QFile::Text);
    file.write(reply->readAll());
    file.close();

}
void Downloader::onForecastReply(QNetworkReply *reply)
{
    QFile file;
    file.setFileName("forecast.json");
    file.open(QIODevice::WriteOnly|QFile::Text);
    file.write(reply->readAll());
    file.close();

}
