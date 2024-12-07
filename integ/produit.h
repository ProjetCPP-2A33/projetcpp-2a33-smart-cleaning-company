#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>
#include <QSqlQueryModel>
#include <QList>

class produit
{
private:
    int idp;
    QString typep;
    QString nomp;
    int prixp;
    int quantite;

public:
    // Constructeurs
    produit();
    produit(const QString& typep, const QString& nomp, int prixp, int quantite);

    // Getters
    QString getNomProduit() const { return nomp; }
    int getPrix() const { return prixp; }
    int getQuantite() const { return quantite; }
    QString getTypeP() const { return typep; }

    // Setters
    void setNomProduit(const QString& p) { nomp = p; }
    void setPrix(int prix) { prixp = prix; }
    void setTypeP(const QString& type) { typep = type; }
    void setQuantite(int qtd) { quantite = qtd; }

    // CRUD
    bool ajouterProduit(produit p);
    QSqlQueryModel* afficherProduits();
    bool supprimerProduit(int idp);
    bool modifierProduit(int idp, const QString& typep, const QString& nomp, int prixp, int quantite);
    QSqlQueryModel* trierProduitsParNom();
    QSqlQueryModel* rechercheparnomproduit(const QString& cle);


};

#endif // PRODUIT_H
