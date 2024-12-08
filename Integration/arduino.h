#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Arduino
{
public:
    Arduino();  // Constructeur
    int connect_arduino();  // Connexion à l'Arduino
    int close_arduino();  // Fermeture de la connexion
    void write_to_arduino(const QByteArray &data,int i);  // Écriture de données vers l'Arduino
    QByteArray read_from_arduino();  // Lecture de données depuis l'Arduino (à implémenter)

    // Accesseurs
    QSerialPort* getserial();  // Retourne le pointeur vers le port série
    QString getarduino_port_name();  // Retourne le nom du port série
    //salimmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
     void BuzzSignal(int count);

private:
    static const quint16 arduino_uno_vendor_id = 0x2341;  // Identifiant du vendeur
    static const quint16 arduino_uno_product_id = 0x0043;  // Identifiant du produit
    QString arduino_port_name;  // Nom du port série
    bool arduino_is_available;  // Indique si l'Arduino est disponible
    QSerialPort* serial;  // Pointeur vers l'objet QSerialPort
};

#endif // ARDUINO_H

