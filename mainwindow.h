#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
#include <QStandardItem>
#include <QJsonDocument>
#include <QString>
#include <QVBoxLayout>
#include <QTimer>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QJsonDocument currentWeatherDoc;
    QJsonDocument forecastWeatherDoc;
    QJsonObject systemInfo;
    QJsonObject mainInfo;
    QJsonObject forecastMainInfo;
    QJsonParseError docError;
    QJsonArray docArray;
    QLabel *_textLabel = nullptr;
    QFile currentWeatherFile;
    QFile forecastWeatherFile;

};

#endif // MAINWINDOW_H
