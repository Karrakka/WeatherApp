#include "mainwindow.h"
#include "weather.h"
#include "downloader.h"
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    for (int i = 0; i < 100000; i++)
    {
        qApp->processEvents();
    }
    resize(600,400);
    setMinimumSize(500,400);

    picture = new QTextEdit(this);
    picture->setReadOnly(true);
    picture->setTabChangesFocus(true);

    today = new QTextEdit(this);
    today->setReadOnly(true);
    today->setTabChangesFocus(true);

    nextDay = new QTextEdit(this);
    nextDay->setReadOnly(true);
    nextDay->setTabChangesFocus(true);

    nextNextDay = new QTextEdit(this);
    nextNextDay->setReadOnly(true);
    nextNextDay->setTabChangesFocus(true);

    nextNextNextDay = new QTextEdit(this);
    nextNextNextDay->setReadOnly(true);
    nextNextNextDay->setTabChangesFocus(true);

    predictionQuality1Day = new QTextEdit(this);
    predictionQuality1Day->setReadOnly(true);
    predictionQuality1Day->setText("quality1");
    predictionQuality1Day->setTabChangesFocus(true);

    predictionQuality2Days = new QTextEdit(this);
    predictionQuality2Days->setReadOnly(true);
    predictionQuality2Days->setText("quality2");
    predictionQuality2Days->setTabChangesFocus(true);

    predictionQuality3Days = new QTextEdit(this);
    predictionQuality3Days->setReadOnly(true);
    predictionQuality3Days->setText("quality3");
    predictionQuality3Days->setTabChangesFocus(true);

    auto mainLayout = new QVBoxLayout();
    auto weatherLayout = new QGridLayout();

    weatherLayout->addWidget(predictionQuality1Day,1,0);
    weatherLayout->addWidget(predictionQuality2Days,2,0);
    weatherLayout->addWidget(predictionQuality3Days,3,0);
    weatherLayout->addWidget(picture,1,1,3,3);
    weatherLayout->addWidget(today,0,0);
    weatherLayout->addWidget(nextDay,0,1);
    weatherLayout->addWidget(nextNextDay,0,2);
    weatherLayout->addWidget(nextNextNextDay,0,3);
    mainLayout->addLayout(weatherLayout);

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
    currentWeather.date = currentDate.toString("dd.MM.yyyy");
    currentWeather.time = QDateTime::currentDateTime().time().toString();
    currentWeather.weatherData.city = currentWeatherDoc.object().value("name").toString();
    currentWeather.weatherData.region = systemInfo.value("country").toString();
    currentWeather.weatherData.temperature = QString::number(mainInfo.value("temp").toDouble() -273);

    Weather forecastWeather[3];

    docArray = QJsonValue(forecastWeatherDoc.object().value("list")).toArray();
    int j=0;
    for (int i=6; i<=22; i+=8)
    {
        forecastMainInfo = docArray.at(i).toObject().value("main").toObject();
        forecastWeather[j].weatherData.temperature = QString::number(forecastMainInfo.value("temp").toDouble() -273);
        j++;
    }
    today->setText("Сегодня: "+ currentWeather.weatherData.temperature + "°C");
    nextDay->setText("Завтра: "+ forecastWeather[0].weatherData.temperature + "°C");
    nextNextDay->setText("Послезавтра: "+ forecastWeather[1].weatherData.temperature + "°C");
    nextNextNextDay->setText("Послепослезавтра: "+ forecastWeather[2].weatherData.temperature+"°C");

    QDate _1day = QDateTime::currentDateTime().date().addDays(1);
    QDate _2days = QDateTime::currentDateTime().date().addDays(2);
    QDate _3days = QDateTime::currentDateTime().date().addDays(3);

    QFile qualityFile("quality.json");
    if (qualityFile.exists())
    {
        qualityFile.open(QIODevice::ReadOnly|QFile::Text);
        QJsonDocument testDoc =QJsonDocument::fromJson(QByteArray(qualityFile.readAll()),&docError);
        QJsonArray testArray =QJsonValue(testDoc.object().value("main")).toArray();
        for (int i=0; i<3; i++)
        {
            QJsonObject testObject = testArray.at(i).toObject();
            if (testObject.value("date").toString("dd.MM.yyyy")=="26.06.2019")
            {
                qDebug()<<"День совпал";
            }
        }

    }
    else
    {
        qualityFile.open(QIODevice::WriteOnly|QFile::Text);

        QVariantMap qualityMap1Day;
        qualityMap1Day.insert("date",_1day.toString("dd.MM.yyyy"));
        qualityMap1Day.insert("temp",forecastWeather[0].weatherData.temperature);

        QVariantMap qualityMap2Days;
        qualityMap2Days.insert("date",_2days.toString("dd.MM.yyyy"));
        qualityMap2Days.insert("temp",forecastWeather[1].weatherData.temperature);

        QVariantMap qualityMap3Days;
        qualityMap3Days.insert("date",_3days.toString("dd.MM.yyyy"));
        qualityMap3Days.insert("temp",forecastWeather[2].weatherData.temperature);

        QJsonObject qualityJson1Day =QJsonObject::fromVariantMap(qualityMap1Day);
        QJsonObject qualityJson2Days =QJsonObject::fromVariantMap(qualityMap2Days);
        QJsonObject qualityJson3Days =QJsonObject::fromVariantMap(qualityMap3Days);

        QJsonArray qualityArray;

        qualityArray.append(qualityJson1Day);
        qualityArray.append(qualityJson2Days);
        qualityArray.append(qualityJson3Days);

        QJsonDocument qualityDoc;
        qualityDoc.setArray(qualityArray);
        qualityFile.write("{\"main\":" + qualityDoc.toJson() + "}");
    }

    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    this->destroy();

}

