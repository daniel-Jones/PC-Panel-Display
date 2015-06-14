#ifndef INIFUNCTIONS_H
#define INIFUNCTIONS_H
#include <QtCore>

class IniFunctions
{
public:
    IniFunctions();
    ~IniFunctions();
    QString IniFileName;
    QString TempFile;
    QString ReadIni(QString Option);
    void WriteIni(QString Option, QString Value);
    QString ToReturn;
};

#endif // INIFUNCTIONS_H

