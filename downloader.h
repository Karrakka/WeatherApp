#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QFile>
class Downloader: public QObject
{
    Q_OBJECT

public:

    Downloader();
    ~Downloader();
    QNetworkAccessManager* weatherNetworkManager;
    QNetworkRequest weatherRequest;

    QNetworkAccessManager* forecastNetworkManager;
    QNetworkRequest forecastRequest;

    QNetworkReply *reply;

private slots:

    void onWeatherReply(QNetworkReply*);
    void onForecastReply(QNetworkReply*);
};

#endif // DOWNLOADER_H
