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

    QJsonDocument currentWeatherDoc;
    QJsonDocument forecastWeatherDoc;
    QJsonObject systemInfo;
    QJsonObject mainInfo;
    QJsonObject forecastMainInfo;
    QJsonParseError docError;
    QJsonArray docArray;

private slots:

private:
    QTimer *timer;
    QLabel *_textLabel = nullptr;
    QStandardItemModel *model = nullptr;
};

#endif // MAINWINDOW_H
