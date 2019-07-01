#include "downloader.h"
Downloader::Downloader()
{
    weatherNetworkManager = new QNetworkAccessManager(this);

    connect(weatherNetworkManager,&QNetworkAccessManager::finished,this,&Downloader::onForecastReply);
    connect(weatherNetworkManager,&QNetworkAccessManager::finished,this,&Downloader::onWeatherReply);

    QSettings citySetting("City");
    QString city =citySetting.value("city","Томск").toString();
    weatherRequest.setUrl(QUrl("http://api.openweathermap.org/data/2.5/weather?q="+city+"&appid=5fa020e093bac007d546bbea0df938e0"));
    forecastRequest.setUrl(QUrl("http://api.openweathermap.org/data/2.5/forecast?q="+city+"&appid=5fa020e093bac007d546bbea0df938e0"));

    weatherNetworkManager->get(weatherRequest);
    weatherNetworkManager->get(forecastRequest);
}
Downloader::~Downloader()
{
}
void Downloader::onWeatherReply(QNetworkReply *reply)
{
    if (reply->request()==weatherRequest)
    {
    QFile file;
    file.setFileName("weather.json");
    file.open(QIODevice::WriteOnly|QFile::Text);
    file.write(reply->readAll());
    file.close();
    reply->deleteLater();
    }
}
void Downloader::onForecastReply(QNetworkReply *reply)
{
    if (reply->request()==forecastRequest)
    {
    QFile file;
    file.setFileName("forecast.json");
    file.open(QIODevice::WriteOnly|QFile::Text);
    file.write(reply->readAll());
    file.close();
    reply->deleteLater();
    }
}
