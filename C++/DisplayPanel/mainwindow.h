#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialcommunication.h"
#include "inifunctions.h"
#include "downloadfile.h"
#include "fileparsing.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DebugLog(QString Text);
    void PopulateSerialList();
    QString SerialPort;
    IniFunctions ini;
    DownloadFile get;
    FileParsing parse;


private slots:
    void on_ConnectButton_clicked();

    void on_DisconnectButton_clicked();

    void on_DisplayButton_clicked();

    void on_SetupWeatherButton_clicked();

    void on_UploadWeatherButton_clicked();

    void on_LCDDisplayButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
