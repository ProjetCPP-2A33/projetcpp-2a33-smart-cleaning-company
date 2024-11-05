#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>

using namespace std;

class Client
{
    int idC;
    QString nom;
    QString prenom;
    int numTel;
    QString mail;
    QString typeAff;
    int nbrAff;
public:
    //Constructors
    Client();
    Client(int,QString,QString,int,QString,QString,int);

    //Getters
    int getIdc(){return idC;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getNumtel(){return numTel;}
    QString getMail(){return mail;}
    QString getTypeaff(){return typeAff;}
    int getNbraff(){return nbrAff;}

    //Setters
    void setIdc(int id){idC=id;}
    void setNom(QString n){nom=n;}
    void setPrenom(QString p){prenom=p;}
    void setNumTel(int num){numTel=num;}
    void setMail(QString m){mail=m;}
    void setTypeaff(QString t){typeAff=t;}
    void setNbraff(int n){nbrAff=n;}

    //Fonctionnalités de base relatives à l'entité Client
    bool ajouter();
    QSqlQueryModel * afficher();
    void afficherTableWidget(QTableWidget *tableWidget, QSqlQueryModel *model);
    bool supprimer(int);

};

#endif // CLIENT_H
