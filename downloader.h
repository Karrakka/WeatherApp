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
    QNetworkAccessManager* networkManager;
    QNetworkRequest request;
    QNetworkReply *reply;

private slots:

    void onReply(QNetworkReply*);
};

#endif // DOWNLOADER_H
