#include "ArduinoClient.h"
#include <QSerialPort>
#include <QDebug>

SerialCommunication::SerialCommunication(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)) {
}

SerialCommunication::~SerialCommunication() {
    if (serial->isOpen()) {
        serial->close();
    }
}

void SerialCommunication::setupSerial(const QString &portName, int baudRate) {
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to port:" << portName;
        connect(serial, &QSerialPort::readyRead, this, &SerialCommunication::readData);
    } else {
        qDebug() << "Failed to open port:" << portName;
        QMessageBox::critical(nullptr, "Error", "Failed to open the serial port!");
    }
}


void SerialCommunication::sendData(const QString &data) {
    if (serial->isOpen()) {
        serial->write(data.toUtf8());
    }
}

void SerialCommunication::readData() {
    QByteArray data = serial->readAll();
    emit dataReceived(QString::fromUtf8(data));
}

void SerialCommunication::BuzzSignal(int count) {
    if (serial->isOpen()) {
        qDebug() << "Sending buzz signal:" << count;
        serial->write(QString::number(count).toUtf8());
    } else {
        qDebug() << "Serial port is not open!";
    }
}

