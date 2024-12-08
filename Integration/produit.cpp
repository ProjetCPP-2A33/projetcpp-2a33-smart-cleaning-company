#include "produit.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include <QSqlError>

// Constructeurs
produit::produit(const QString& typep, const QString& nomp, int prixp, int quantite)
    : typep(typep), nomp(nomp), prixp(prixp), quantite(quantite)
{}

produit::produit()
{}

// Ajouter produit
bool produit::ajouterProduit(produit p) {
    QSqlQuery query;
    query.prepare("INSERT INTO Produit (typep, nomp, prixp, quantite) "
                  "VALUES (:typep, :nomp, :prixp, :quantite)");
    query.bindValue(":typep", typep);
    query.bindValue(":nomp", nomp);
    query.bindValue(":prixp", prixp);
    query.bindValue(":quantite", quantite);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion:" << query.lastError().text();
        return false;
    }
    return true;
}

// Afficher produits
QSqlQueryModel* produit::afficherProduits() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Produit");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur requête:" << model->lastError().text();
    } else {
        qDebug() << model->rowCount() << " enregistrements trouvés";
    }

    return model;
}

// Supprimer produit
bool produit::supprimerProduit(int idp) {
    QSqlQuery query;
    query.prepare("DELETE FROM Produit WHERE idp = :idp");
    query.bindValue(":idp", idp);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
    return true;
}

// Modifier produit
bool produit::modifierProduit(int idp, const QString& typep, const QString& nomp, int prixp, int quantite) {
    QSqlQuery query;
    query.prepare("UPDATE Produit SET typep = :typep, nomp = :nomp, prixp = :prixp, quantite = :quantite WHERE idp = :idp");
    query.bindValue(":idp", idp);
    query.bindValue(":typep", typep);
    query.bindValue(":nomp", nomp);
    query.bindValue(":prixp", prixp);
    query.bindValue(":quantite", quantite);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour:" << query.lastError().text();
        return false;
    }
    return true;
}

// Trier produits
QSqlQueryModel* produit::trierProduitsParNom() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Produit ORDER BY prixp ASC");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la requête de tri:" << model->lastError().text();
    }
    return model;
}

// recherche par nom produit
QSqlQueryModel* produit::rechercheparnomproduit(const QString& cle) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM Produit WHERE nomp LIKE :recherche ");
    query.bindValue(":recherche", "%" + cle + "%");
    query.exec();
    model->setQuery(std::move(query));
    return model;
}



