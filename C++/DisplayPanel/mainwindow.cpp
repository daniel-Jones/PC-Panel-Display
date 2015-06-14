#include <QSerialPortInfo>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialcommunication.h"
#include "weathersettings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    DebugLog("Display Controller started");
    // disable some buttons etc
    ui->DisconnectButton->setEnabled(false);
    ui->ConnectButton->setEnabled(false);
    ui->DisplayButton->setEnabled(false);
    ui->LCDDisplayButton->setEnabled(false);
    ui->UploadWeatherButton->setEnabled(false);
    // we will first populate our serial list
    PopulateSerialList();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::DebugLog(QString Text) { // displays debug information
    ui->DebugOutput->append(Text);
}

void MainWindow::PopulateSerialList() { // this function will populate our serial port list
    for (int x = 0; x < QSerialPortInfo::availablePorts().size(); x++) {
        ui->SerialList->addItem(QSerialPortInfo::availablePorts().at(x).portName());
    }
    if (!ui->SerialList->size().isEmpty()) {
        ui->ConnectButton->setEnabled(true);
        DebugLog("Serial port list populated..");
    }
    else
        DebugLog("No serial port found!");
}

void MainWindow::on_ConnectButton_clicked() { // serial connect button
    SerialPort = ui->SerialList->currentText();
    if (SerialCommunication::SerialConnect(SerialPort)) { // if true we are connected
        DebugLog("Connection succesful!");
        ui->StatusInfoLabel->setText("<font color=green>Connected</font>");
        ui->DisconnectButton->setEnabled(true);
        ui->ConnectButton->setEnabled(false);
        ui->DisplayButton->setEnabled(true);
        ui->LCDDisplayButton->setEnabled(true);
        ui->UploadWeatherButton->setEnabled(true);
    } else {
        DebugLog("Connection error..");
    }
}

void MainWindow::on_DisconnectButton_clicked() { // serial disconnect button
    if (SerialCommunication::SerialDisconnect()) { // if true we are disconnected
        DebugLog("Disconnected..");
        ui->StatusInfoLabel->setText("<font color=red>Disconnected</font>");
        ui->DisconnectButton->setEnabled(false);
        ui->ConnectButton->setEnabled(true);
        ui->DisplayButton->setEnabled(false);
        ui->LCDDisplayButton->setEnabled(false);
        ui->UploadWeatherButton->setEnabled(false);
    } else { // fail
        DebugLog("Can not disconnect right now..");
    }
}

void MainWindow::on_DisplayButton_clicked() { // displaying text on the oled
    SerialCommunication::OledDisplay(ui->OledDisplay->text());
}

void MainWindow::on_SetupWeatherButton_clicked() { // setup weather dialog
    WeatherSettings* WeatherDialog = new WeatherSettings; // set an object for our new window
    WeatherDialog->show();
}

void MainWindow::on_UploadWeatherButton_clicked() { // upload and parse our weather information
    DebugLog("Getting information for " + ini.ReadIni("location"));
    // we need to (re) download our weather  info in case it has changed
    DebugLog("Downloading weather information..");
    //get.DownloadUrl("ftp://ftp2.bom.gov.au/anon/gen/fwo/IDA00001.dat", QDir::homePath() + "/tempdatadir/weather.txt");
    DebugLog("Downloading done..");
    DebugLog("Parsing file..");
    DebugLog(parse.ParseWeather());
}

void MainWindow::on_LCDDisplayButton_clicked() { // display text to the lcd
    SerialCommunication::LCDDisplay(ui->LCDText->text());
}
