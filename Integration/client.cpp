#include "client.h"
#include <QSqlQuery>
#include <QSqlError>


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

QSqlQueryModel* Client::recherche(int id, QString nom, QString prenom, QString combo) {
    QSqlQuery query;

    if(combo== "Id")
    {
        query.prepare("SELECT * FROM client WHERE idC = :id");
        query.bindValue(":id", id);
    }

    else if(combo== "Nom")
    {
        query.prepare("SELECT * FROM client WHERE nom = :nom");
        query.bindValue(":nom", nom);
    }

    else if(combo== "Prénom")
    {
        query.prepare("SELECT * FROM client WHERE prénom = :prenom");
        query.bindValue(":prenom", prenom);
    }

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
bool Client::exporterPDF(const QString &nomFichier, QAbstractItemModel *model) {
    QPdfWriter pdfWriter(nomFichier);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        qDebug() << "Erreur lors de l'initialisation du QPainter pour le PDF.";
        return false;
    }

    // Set PDF parameters
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));

    // Title
    painter.drawText(2500, 1100, "Liste des Clients (ID et Noms)");

    // Table coordinates and cell dimensions
    int startX = 200;
    int startY = 1800;
    int cellWidth = 1100;
    int cellHeight = 450;

    // Table headers: "ID Employé" and "Nom"
    QStringList headers = {"ID Client", "Nom"};
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawText(startX + col * cellWidth, startY, cellWidth, cellHeight, Qt::AlignCenter, headers[col]);
    }

    // Display data: ID and Name
    int rowCount = model->rowCount();
    painter.setFont(QFont("Arial", 10));
    for (int row = 0; row < rowCount; ++row) {
        QColor bgColor = (row % 2 == 0) ? Qt::lightGray : Qt::white;

        // Draw ID (column 0) and Name (column 1)
        QString idData = model->data(model->index(row, 0)).toString();  // Column 0 is "ID"
        QString nameData = model->data(model->index(row, 1)).toString();  // Column 1 is "Nom"

        // ID cell
        QRect idCellRect(startX, startY + (row + 1) * cellHeight, cellWidth, cellHeight);
        painter.fillRect(idCellRect, bgColor);
        painter.drawText(idCellRect, Qt::AlignCenter, idData);
        painter.drawRect(idCellRect);

        // Name cell
        QRect nameCellRect(startX + cellWidth, startY + (row + 1) * cellHeight, cellWidth, cellHeight);
        painter.fillRect(nameCellRect, bgColor);
        painter.drawText(nameCellRect, Qt::AlignCenter, nameData);
        painter.drawRect(nameCellRect);
    }

    painter.end();
    QMessageBox::information(nullptr, "PDF Créé", "Un fichier PDF a été créé.");
    return true;
}
/*bool Client::checkID(const QString &employeID) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE CARDUID = :employeID");
    query.bindValue(":employeID", employeID.trimmed());

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;  // If count > 0, ID exists
    }

    return false;
}*/

