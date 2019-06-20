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
#include <QLayout>
#include <QTextEdit>
#include <QHBoxLayout>
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
    QTextEdit *today = nullptr;
    QTextEdit *nextDay = nullptr;
    QTextEdit *nextNextDay = nullptr;
    QTextEdit *nextNextNextDay = nullptr;
    QTextEdit *predictionQuality1Day = nullptr;
    QTextEdit *predictionQuality2Days = nullptr;
    QTextEdit *predictionQuality3Days = nullptr;
    QFile currentWeatherFile;
    QFile forecastWeatherFile;
};

#endif // MAINWINDOW_H
