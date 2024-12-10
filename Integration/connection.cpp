#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_cpp2a33");
    db.setUserName("fraj");
    db.setPassword("produit");

    if (db.open())
        test=true;
    return  test;
}
