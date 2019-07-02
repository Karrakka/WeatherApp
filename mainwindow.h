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
#include <QTimer>
#include <QLayout>
#include <QTextEdit>
#include <QApplication>
#include <QtMath>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QInputDialog>
class MainWindow : public QMainWindow
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
    QTextEdit *predictionQuality[3];
    QLabel *picture = nullptr;
    QFile currentWeatherFile;
    QFile forecastWeatherFile;
    QWidget *mainWidget;
    QMenuBar *menuBar;
    QMenu *weatherMenu;
    QAction *aboutAction;
    QAction *cityAction;
private slots:
    void onAboutClicked();
    void onCityClicked();
};

#endif // MAINWINDOW_H
