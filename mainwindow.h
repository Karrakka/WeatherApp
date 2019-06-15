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

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QJsonDocument weatherDoc;
    QJsonObject systemInfo;
    QJsonObject mainInfo;
    QJsonParseError docError;

private slots:

private:
    QLabel *_textLabel = nullptr;
    QStandardItemModel *model = nullptr;
};

#endif // MAINWINDOW_H
