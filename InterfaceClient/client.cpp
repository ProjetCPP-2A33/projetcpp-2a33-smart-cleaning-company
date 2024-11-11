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

    query.prepare("INSERT INTO client (idC, nom, prénom, numTel, mail, typeAffaire, nbrAffaire) "
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

    model->setQuery("SELECT * FROM client");

    return model;
}

bool Client::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("DELETE FROM client WHERE idC = :idC");

    query.bindValue(":idC", res);

    return query.exec();
}

bool Client::modifier(int id,QString nom,QString prenom,int numTel,QString mail,QString typeAff,int nbrAff)
{
    QSqlQuery query;

    query.prepare("UPDATE client SET nom= :nom, prénom= :prenom, numTel= :numTel, mail= :mail, typeAffaire= :typeAff, nbrAffaire= :nbrAff WHERE idC= :id");

    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":numTel",numTel);
    query.bindValue(":mail",mail);
    query.bindValue(":typeAff",typeAff);
    query.bindValue(":nbrAff",nbrAff);

    return query.exec();
}

QSqlQueryModel* Client::tri()
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM client ORDER BY nbrAffaire ASC");

    return model->query().isActive() ? model: nullptr;
}

QSqlQueryModel* Client::recherche(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM client WHERE idC = :id");
    query.bindValue(":id", id);

    bool test=query.exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    if (test) {
        model->setQuery(std::move(query));  // Move the query
        return model;
    } else {
        delete model;
        return nullptr;
    }
}

