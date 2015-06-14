#include "weathersettings.h"
#include "ui_weathersettings.h"
#include "mainwindow.h"

WeatherSettings::WeatherSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherSettings) {
    ui->setupUi(this);
    ui->LocationName->setText(ini.ReadIni("location"));
}

WeatherSettings::~WeatherSettings() {
    delete ui;
}

void WeatherSettings::on_DoneButton_clicked() { // set our location
    if (ui->LocationName->text() != "")
        ini.WriteIni("location", ui->LocationName->text());
    this->close();
}
