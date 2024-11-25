#include "clientwindow.h"
#include <QApplication>
#include "connection.h"
#include <ArduinoClient.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;

    bool test=c.createconnect();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    /*SerialCommunication serialComm;
    serialComm.setupSerial("COM7", 9600);  // Replace with your port

    QObject::connect(&serialComm, &SerialCommunication::dataReceived,
                     [](const QString &data){
                         qDebug() << "Received from Arduino:" << data;
                     });

    // Send data example
    serialComm.sendData("Hello Arduino!");*/



    return a.exec();
}
