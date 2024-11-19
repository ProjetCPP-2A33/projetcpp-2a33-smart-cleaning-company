#ifndef CLIENT_H
#define CLIENT_H

#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QVariant>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <QStackedWidget>

#include <QFileDialog>
#include <QPainter>
#include <QPdfWriter>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

#include <QRegularExpression>


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
    bool supprimer(int);
    bool modifier(int,QString,QString,int,QString,QString,int);
    QSqlQueryModel * tri();
    QSqlQueryModel * recherche(int, QString,QString,QString);
    bool exporterPDF(const QString &nomFichier, QAbstractItemModel *model);

};

#endif // CLIENT_H
