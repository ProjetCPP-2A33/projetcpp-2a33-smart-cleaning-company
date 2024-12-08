#include "Arduino.h"
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

Arduino::Arduino()
    : serial(nullptr), arduino_is_available(false)
{
    arduino_port_name = "COM8"; // Vous pouvez rendre cela dynamique si besoin
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort* Arduino::getserial()
{
    return serial;
}

int Arduino::connect_arduino() {
    // Recherche de l'Arduino dans les ports disponibles
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        // Vérifie si le port a un identifiant de vendeur et un identifiant de produit
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            // Vérifie si l'identifiant de l'Arduino correspond
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_product_id) {

                arduino_is_available = true; // L'Arduino est disponible
                arduino_port_name = serial_port_info.portName(); // Nom du port Arduino
                qDebug() << "Arduino trouvé sur le port:" << arduino_port_name;

                // Initialisation du port série
                serial = new QSerialPort(); // Utilisez un pointeur intelligent si possible
                serial->setPortName(arduino_port_name);
                serial->setBaudRate(QSerialPort::Baud9600);
                serial->setDataBits(QSerialPort::Data8);
                serial->setParity(QSerialPort::NoParity);
                serial->setStopBits(QSerialPort::OneStop);
                serial->setFlowControl(QSerialPort::NoFlowControl);

                // Tentative d'ouverture du port série
                if (serial->open(QIODevice::ReadWrite)) {
                    qDebug() << "Port série ouvert avec succès!";
                    return 0; // Succès
                } else {
                    qDebug() << "Échec de l'ouverture du port série:" << serial->errorString();
                    delete serial; // Libération de la mémoire en cas d'échec
                    serial = nullptr; // Mettre à jour le pointeur
                    return 1; // Échec lors de l'ouverture
                }
            }
        }
    }

    // Si l'Arduino n'est pas trouvé
    qDebug() << "Arduino non trouvé.";
    return -1; // Arduino introuvable
}

int Arduino::close_arduino()
{
    if (serial) { // Vérifiez que le pointeur n'est pas nul
        if (serial->isOpen()) {
            QString portName = serial->portName(); // Capture le nom du port avant de le fermer
            serial->close();
            delete serial; // Libérer la mémoire
            serial = nullptr; // Mettre à jour le pointeur
            qDebug() << "Arduino serial port closed:" << portName;
            return 0; // Succès
        }
        qDebug() << "Le port série n'était pas ouvert. Rien à fermer.";
    }
    return 1; // Erreur : le port n'était pas ouvert ou le pointeur était nul
}

void Arduino::write_to_arduino(const QByteArray &data) {
    if (serial) { // Assurez-vous que serial n'est pas nul
        if (serial->isOpen()) {
            if (serial->isWritable()) {
                serial->write(data);
                qDebug() << "Données envoyées à l'Arduino:" << data;
            } else {
                qDebug() << "Le port série n'est pas accessible en écriture:" << serial->errorString();
            }
        } else {
            qDebug() << "Le port série n'est pas ouvert.";
        }
    } else {
        qDebug() << "Le pointeur du port série est nul.";
    }
}

