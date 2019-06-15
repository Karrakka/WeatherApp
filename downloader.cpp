#include "downloader.h"

Downloader::Downloader(){

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onReply(QNetworkReply*)));

    request.setUrl(QUrl("http://api.openweathermap.org/data/2.5/weather?id=1489425&appid=5fa020e093bac007d546bbea0df938e0"));

    networkManager->get(request);
}
Downloader::~Downloader()
{
    delete networkManager;
}
void Downloader::onReply(QNetworkReply *reply)
{
    QFile file;
    file.setFileName("weather.json");
    file.open(QIODevice::WriteOnly|QFile::Text);
    file.write(reply->readAll());
    file.close();

}
