#include "mainwindow.h"
#include "weather.h"
#include "downloader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new QWidget(this);
    menuBar = new QMenuBar(this);
    weatherMenu = new QMenu("Погода",this);
    aboutAction = weatherMenu->addAction("О программе");
    connect(aboutAction,&QAction::triggered,this,&MainWindow::onAboutClicked);
    cityAction = weatherMenu->addAction("Выбор города");
    connect(cityAction,&QAction::triggered,this,&MainWindow::onCityClicked);
    menuBar->addMenu(weatherMenu);

    for (int i = 0; i < 200000; i++)
    {
        qApp->processEvents();
    }

    resize(600,400);
    setMinimumSize(600,400);
    picture = new QLabel(this);
    picture->setPixmap(QPixmap(":/img/Picture.png"));
    picture->setFixedSize(450,250);
    picture->setMargin(10);

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

    predictionQuality[0] = new QTextEdit(this);
    predictionQuality[0]->setReadOnly(true);
    predictionQuality[0]->setTabChangesFocus(true);
    predictionQuality[0]->setText("Недостаточно данных для оценки качества предсказаний");

    predictionQuality[1] = new QTextEdit(this);
    predictionQuality[1]->setReadOnly(true);
    predictionQuality[1]->setTabChangesFocus(true);
    predictionQuality[1]->setText("Недостаточно данных для оценки качества предсказаний");

    predictionQuality[2] = new QTextEdit(this);
    predictionQuality[2]->setReadOnly(true);
    predictionQuality[2]->setTabChangesFocus(true);
    predictionQuality[2]->setText("Недостаточно данных для оценки качества предсказаний");

    auto mainLayout = new QVBoxLayout();
    auto weatherLayout = new QGridLayout();

    weatherLayout->addWidget(predictionQuality[0],1,0);
    weatherLayout->addWidget(predictionQuality[1],2,0);
    weatherLayout->addWidget(predictionQuality[2],3,0);
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
    currentWeather.date = QDateTime::currentDateTime().date();
    currentWeather.time = QDateTime::currentDateTime().time();
    currentWeather.weatherData.city = currentWeatherDoc.object().value("name").toString();
    currentWeather.weatherData.region = systemInfo.value("country").toString();
    currentWeather.weatherData.temperature = QString::number(qFloor(mainInfo.value("temp").toDouble() -273));

    Weather forecastWeather[3];
    QDate forecastDate = QDateTime::currentDateTime().date().addDays(1);
    docArray = QJsonValue(forecastWeatherDoc.object().value("list")).toArray();
    int j=0;
    QJsonObject dateText;
    QString date;
    for (int i=0; i<docArray.count(); i++)
    {
        dateText = docArray.at(i).toObject();
        date =dateText.value("dt_txt").toString();
        date.remove(10,9);
        if (date==forecastDate.toString("yyyy-MM-dd"))
        {
            forecastDate = forecastDate.addDays(1);
            forecastMainInfo = docArray.at(i+2).toObject().value("main").toObject();
            forecastWeather[j].weatherData.temperature = QString::number(qFloor(forecastMainInfo.value("temp").toDouble() -273));
            j++;
        }
        if (j==3)
            break;
    }

    today->setText("Сегодня: "+ currentWeather.weatherData.temperature + "°C\nТекущий город:"+currentWeather.weatherData.city);
    nextDay->setText("Завтра: "+ forecastWeather[0].weatherData.temperature + "°C");
    nextNextDay->setText("Послезавтра: "+ forecastWeather[1].weatherData.temperature + "°C");
    nextNextNextDay->setText("Послепослезавтра: "+ forecastWeather[2].weatherData.temperature+"°C");

    QDate _1day = QDateTime::currentDateTime().date().addDays(1);
    QDate _2days = QDateTime::currentDateTime().date().addDays(2);
    QDate _3days = QDateTime::currentDateTime().date().addDays(3);
    QString quality;
    QFile qualityFile("quality.json");
    if (qualityFile.exists())
    {
        qualityFile.open(QIODevice::ReadOnly|QFile::Text);
        QJsonDocument qualityDoc =QJsonDocument::fromJson(QByteArray(qualityFile.readAll()),&docError);
        QJsonArray qualityArray =QJsonValue(qualityDoc.object().value("main")).toArray();
        for (int i=0; i<3; i++)
        {
            QJsonObject qualityObject = qualityArray.at(i).toObject();
            if (qualityObject.value("date").toString("dd.MM.yyyy")==currentDate.toString("dd.MM.yyyy"))
            {
                quality=QString::number(qFabs(qualityObject.value("temp").toDouble() - qFloor((mainInfo.value("temp").toDouble() -273))));
                predictionQuality[i]->setText("Предсказание погоды отличается на " + quality + "°C");
            }
        }
        qualityFile.close();
        qualityFile.open(QIODevice::WriteOnly|QFile::Text);
        QVariantMap qualityMap[3];
        QJsonObject qualityJson[3];
        QJsonArray rewriteArray;
        QJsonDocument rewriteDoc;
        for (int i=0;i<3;i++)
        {
            QJsonObject qualityObject = qualityArray.at(i).toObject();
            if (qualityObject.value("date").toString("dd.MM.yyyy")==currentDate.toString("dd.MM.yyyy"))
            {
                qualityMap[i].insert("date",currentDate.addDays(i+1).toString("dd.MM.yyyy"));
                qualityMap[i].insert("temp",forecastWeather[i].weatherData.temperature.toDouble());
                qualityJson[i]=QJsonObject::fromVariantMap(qualityMap[i]);
                rewriteArray.append(qualityJson[i]);
            }
            else
            {
                qualityMap[i].insert("date",qualityObject.value("date").toString("dd.MM.yyyy"));
                qualityMap[i].insert("temp",qualityObject.value("temp").toDouble());
                qualityJson[i]=QJsonObject::fromVariantMap(qualityMap[i]);
                rewriteArray.append(qualityJson[i]);
            }
        }
        rewriteDoc.setArray(rewriteArray);
        qualityFile.write("{\"main\":" + rewriteDoc.toJson() + "}");
        qualityFile.close();
    }
    else
    {
        qualityFile.open(QIODevice::WriteOnly|QFile::Text);

        QVariantMap qualityMap1Day;
        qualityMap1Day.insert("date",_1day.toString("dd.MM.yyyy"));
        qualityMap1Day.insert("temp",forecastWeather[0].weatherData.temperature.toDouble());

        QVariantMap qualityMap2Days;
        qualityMap2Days.insert("date",_2days.toString("dd.MM.yyyy"));
        qualityMap2Days.insert("temp",forecastWeather[1].weatherData.temperature.toDouble());

        QVariantMap qualityMap3Days;
        qualityMap3Days.insert("date",_3days.toString("dd.MM.yyyy"));
        qualityMap3Days.insert("temp",forecastWeather[2].weatherData.temperature.toDouble());

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
        qualityFile.close();
    }
    setMenuBar(menuBar);
    setCentralWidget(mainWidget);
    mainWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    this->destroy();
}
void MainWindow::onAboutClicked()
{
    QMessageBox::about(this,"О приложении","Приложение \"Погода\"");
}
void MainWindow::onCityClicked()
{
    bool isChanged;
    QString city = QInputDialog::getText(this,"Выбор города","Введите город",QLineEdit::Normal,"",&isChanged);
    if(isChanged)
    {
        QSettings citySetting("City");
        citySetting.setValue("city",city);
        QMessageBox::about(this,"","Город будет изменен после перезапуска");
        QFile::remove("quality.json");
    }
    else
        QMessageBox::about(this,"","Отмена");
}
