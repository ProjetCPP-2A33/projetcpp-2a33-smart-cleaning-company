#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test = c.createconnect();
    if (!test) {
        QMessageBox::critical(nullptr, QObject::tr("Base de données fermée"),
                              QObject::tr("Échec de la connexion. Cliquez pour quitter."),
                              QMessageBox::Cancel);
        return -1;
    }

    w.show();
    return a.exec();
}
