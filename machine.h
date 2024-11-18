#ifndef MACHINE_H
#define MACHINE_H

#include "qtableview.h"
#include <QString>
#include <QSqlQueryModel>

class Machine {
public:
    Machine();  // Constructor declaration
    Machine(int, QString, int, QString, QString);  // Parameterized constructor

    // Getter and Setter methods
    int getId_M() const;
    QString getEtatM() const;
    int getResponsableM() const;
    QString getDescriptionM() const;
    QString getEmplacementM() const;

    void setId_M(int);
    void setEtatM(QString);
    void setResponsableM(int);
    void setDescriptionM(QString);
    void setEmplacementM(QString);
    void imprimerTableau(QTableView *tableView);

    // CRUD methods
    bool ajouter();
    bool modifier(int);
    QSqlQueryModel* afficher();
    bool supprimer(int);


private:
    int id_M;
    QString etatM;
    int responsableM;
    QString descriptionM;
    QString emplacementM;


};

#endif // MACHINE_H
