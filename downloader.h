#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
class Downloader: public QObject
{
    Q_OBJECT

public:

    Downloader();
    ~Downloader();

private:

    QNetworkAccessManager* weatherNetworkManager;
    QNetworkRequest weatherRequest;
    QNetworkRequest forecastRequest;
    QNetworkReply *reply;

private slots:

    void onWeatherReply(QNetworkReply*);
    void onForecastReply(QNetworkReply*);
};

#endif // DOWNLOADER_H
