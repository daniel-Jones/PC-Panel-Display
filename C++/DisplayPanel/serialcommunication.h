#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H
#include <QSerialPort>
#include <QSerialPortInfo>

#include "mainwindow.h"

class SerialCommunication
{
public:
    SerialCommunication();
    ~SerialCommunication();
    QString PortName;
    static bool SerialConnect(QString PortName);
    static bool SerialDisconnect();
    static void OledDisplay(QString Text);
    static void LCDDisplay(QString Text);
};

#endif // SERIALCOMMUNICATION_H
