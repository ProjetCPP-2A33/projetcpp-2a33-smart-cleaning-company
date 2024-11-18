#include "Connection.h"
connection::connection()
{}

bool connection::createconnection()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("cpp");
    db.setUserName("mahdi");//inserer nom de l'utilisateur
    db.setPassword("mahdi");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;



    return  test;
}
void connection::closeConnection(){db.close();}

