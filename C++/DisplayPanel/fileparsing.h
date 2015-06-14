#ifndef FILEPARSING_H
#define FILEPARSING_H
#include "inifunctions.h"

class FileParsing
{
public:
    FileParsing();
    ~FileParsing();
    QString ParseWeather();
    IniFunctions ini;
    QList<QString> Forecast;
};

#endif // FILEPARSING_H
