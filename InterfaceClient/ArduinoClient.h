#ifndef ARDUINOCLIENT_H
#define ARDUINOCLIENT_H

#include <client.h>

class SerialCommunication : public QObject
{
    Q_OBJECT

public:
    explicit SerialCommunication(QObject *parent = nullptr);
    ~SerialCommunication();

    void setupSerial(const QString &portName, int baudRate);
    void sendData(const QString &data);
    void BuzzSignal(int count);

signals:
    void dataReceived(const QString &data);

private slots:
    void readData();

private:
    QSerialPort *serial;
};

#endif // ARDUINOCLIENT_H
