#include "machine.h"
#include "qtableview.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QSqlQueryModel>

#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTableView>
#include <QDialog>


Machine::Machine() {
    id_M = 0;
    etatM = "";
    responsableM = 0;
    descriptionM = "";
    emplacementM = "";
}

Machine::Machine(int id, QString etat, int responsable, QString description, QString emplacement) {
    this->id_M = id;
    this->etatM = etat;
    this->responsableM = responsable;
    this->descriptionM = description;
    this->emplacementM = emplacement;
}

// Getter and Setter methods
int Machine::getId_M() const {
    return id_M;
}

QString Machine::getEtatM() const {
    return etatM;
}

int Machine::getResponsableM() const {
    return responsableM;
}

QString Machine::getDescriptionM() const {
    return descriptionM;
}

QString Machine::getEmplacementM() const {
    return emplacementM;
}

void Machine::setId_M(int id) {
    this->id_M = id;
}

void Machine::setEtatM(QString etat) {
    this->etatM = etat;
}

void Machine::setResponsableM(int responsable) {
    this->responsableM = responsable;
}

void Machine::setDescriptionM(QString description) {
    this->descriptionM = description;
}

void Machine::setEmplacementM(QString emplacement) {
    this->emplacementM = emplacement;
}

// CRUD methods

bool Machine::ajouter() {
    QSqlQuery query;

    // Preparing the query with placeholders
    query.prepare("INSERT INTO machine (id_M, etatM, responsableM, descriptionM, emplacementM) "
                  "VALUES (:id_M, :etatM, :responsableM, :descriptionM, :emplacementM)");

    // Binding values from the UI fields
    query.bindValue(":id_M", id_M);
    query.bindValue(":etatM", etatM);
    query.bindValue(":responsableM", responsableM);
    query.bindValue(":descriptionM", descriptionM);
    query.bindValue(":emplacementM", emplacementM);

    // Execute the query and check if it succeeded
    if (!query.exec()) {
        // Print the error message if query execution fails
        qDebug() << "Erreur lors de l'ajout de la machine : " << query.lastError().text();
        return false;
    }

    return true; // Successful insertion
}




bool Machine::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM machine WHERE id_M = :id_M");
    query.bindValue(":id_M", id);

    // Debugging: print the query before executing it
    qDebug() << "Executing delete query: " << query.lastQuery();

    if (!query.exec()) {
        // Print the error if query execution fails
        qDebug() << "Error deleting machine: " << query.lastError().text();
        return false;
    }

    return true;  // Successfully deleted
}



bool Machine::modifier(int id) {
    QSqlQuery query;

    query.prepare("UPDATE machine SET etatM = :etatM, responsableM = :responsableM, "
                  "descriptionM = :descriptionM, emplacementM = :emplacementM WHERE id_M = :id_M");

    query.bindValue(":id_M", id);
    query.bindValue(":etatM", etatM);
    query.bindValue(":responsableM", responsableM);
    query.bindValue(":descriptionM", descriptionM);
    query.bindValue(":emplacementM", emplacementM);

    return query.exec();
}

QSqlQueryModel* Machine::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM machine");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Responsable"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Emplacement"));
    return model;
}


void Machine::imprimerTableau(QTableView *tableView)
{
    // Create a printer object with high resolution
    QPrinter printer(QPrinter::HighResolution);

    // Set the page size to A4
    printer.setPageSize(QPageSize::A4);  // Set the page size to A4

    // Optionally, set the page orientation if needed (Portrait or Landscape)
    printer.setPageOrientation(QPageLayout::Portrait);  // Or QPrinter::Landscape if needed

    // Show the print dialog
    QPrintDialog printDialog(&printer, nullptr);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter;

        // Begin painting on the printer
        if (painter.begin(&printer)) {
            // Render the table to the painter
            tableView->render(&painter);

            // End the painter session
            painter.end();
        }
    }
}
