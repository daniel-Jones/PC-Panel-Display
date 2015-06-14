#ifndef WEATHERSETTINGS_H
#define WEATHERSETTINGS_H
#include "inifunctions.h"

#include <QWidget>

namespace Ui {
class WeatherSettings;
}

class WeatherSettings : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherSettings(QWidget *parent = 0);
    ~WeatherSettings();
    IniFunctions ini;

private slots:
    void on_DoneButton_clicked();

private:
    Ui::WeatherSettings *ui;
};

#endif // WEATHERSETTINGS_H
