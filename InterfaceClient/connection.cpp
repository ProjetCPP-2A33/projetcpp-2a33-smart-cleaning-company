#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("CPP_Project");//inserer le nom de la source de données
    db.setUserName("Salim");//inserer nom de l'utilisateur
    db.setPassword("salim123");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
}

void Connection::closeConnection(){db.close();}
