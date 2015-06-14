// this class will control our serial communications
#include <QSerialPort>
#include "serialcommunication.h"
#include "mainwindow.h"
QSerialPort serial;
QByteArray data;
SerialCommunication::SerialCommunication() {
}

SerialCommunication::~SerialCommunication() {

}

bool SerialCommunication::SerialConnect(QString PortName) { // serial connect
    if (!serial.isOpen()) {
        serial.setPortName(PortName);
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        serial.open(QIODevice::ReadWrite);
        if (serial.isWritable()) {
            return true;
        }
    }
    return false;
}

bool SerialCommunication::SerialDisconnect() { // serial disconnect
    if (serial.isOpen()) {
        serial.close();
        return true;
    }
    return false;
}

void SerialCommunication::OledDisplay(QString Text) { // display text to oled
    data = "";
    data.append("/" + Text + "\n");
    if (serial.isOpen())
        serial.write(data);
}

void SerialCommunication::LCDDisplay(QString Text) { // display text to lcd
    data = "";
    data.append("/" + Text + "#");
    if (serial.isOpen())
        serial.write(data);
}

