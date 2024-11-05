#include "client.h"

Client::Client()
{

}

Client::Client(int id,QString nom,QString prenom,int numTel,QString mail,QString typeAff,int nbrAff)
{
    this->idC=id;
    this->nom=nom;
    this->prenom=prenom;
    this->numTel=numTel;
    this->mail=mail;
    this->typeAff=typeAff;
    this->nbrAff=nbrAff;
}

bool Client::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO clients (idC, nom, prenom, numTel, mail, typeAff, nbrAff) "
                  "VALUES (:idC, :nom, :prenom, :numTel, :mail, :typeAff, :nbrAff)");

    query.bindValue(":idC", idC);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numTel", numTel);
    query.bindValue(":mail", mail);
    query.bindValue(":typeAff", typeAff);
    query.bindValue(":nbrAff", nbrAff);

    return query.exec();
}

QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT idC, nom, prenom, numTel, mail, typeAff, nbrAff FROM clients");

    return model;
}

void Client::afficherTableWidget(QTableWidget *tableWidget, QSqlQueryModel *model)
{
    tableWidget->setRowCount(model->rowCount());
    tableWidget->setColumnCount(model->columnCount());

    for (int col = 0; col < model->columnCount(); ++col) {
        tableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString()));
    }

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            tableWidget->setItem(row, col, item);
        }
    }
}

bool Client::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM clients WHERE idC = :idC");

    query.bindValue(":idC", id);

    return query.exec();
}

