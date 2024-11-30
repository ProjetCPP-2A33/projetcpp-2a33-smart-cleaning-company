#include "Arduino.h"
#include <QDebug>
#include <QSerialPort>


Arduino::Arduino()
{
    //data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
    return serial;
}

int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "Arduino port name is:" << arduino_port_name;
                serial->setPortName(arduino_port_name);
                if (serial->open(QSerialPort::ReadWrite)) {
                    serial->setPortName("COM8");
                    serial->setBaudRate(QSerialPort::Baud9600);
                    serial->setDataBits(QSerialPort::Data8);
                    serial->setParity(QSerialPort::NoParity);
                    serial->setStopBits(QSerialPort::OneStop);
                    serial->setFlowControl(QSerialPort::NoFlowControl);
                    return 0; // Success
                } else {
                    qDebug() << "Failed to open serial port for Arduino.";
                    return 1; // Failed to open serial port
                }
            }
        }
    }
    qDebug() << "Arduino not found.";
    return -1; // Arduino not found
}
int Arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        qDebug() << "Arduino serial port closed.";
        return 0;
    }
    return 1;
}
/*QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
        data=serial->readAll();
        return data;
    }
}

void Arduino::write_to_arduino( QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}*/
void Arduino::write_to_arduino(const QByteArray &data)
{
    if (serial->isWritable()) {
        serial->write(data);
        qDebug() << "Data sent to Arduino:" << data;
    } else {
        qDebug() << "Couldn't write to serial!";
    }
}


