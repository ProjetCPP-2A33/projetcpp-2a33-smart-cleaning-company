#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "produit.h"
#include <QSqlQuery>
#include <QDebug>
#include "connection.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QNetworkAccessManager>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include "arduino.h"
#include <QSerialPort>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Arduino A;
    int ret=A.connect_arduino();
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    produit p;

    QString nomproduit = ui->inputnomp->text();
    QString typep = ui->boxtype->currentText();
    int quantite = ui->inputquantite->text().toInt();
    int prix = ui->inputprixp->text().toInt();

    produit pajout(typep, nomproduit, prix, quantite);
    if (pajout.ajouterProduit(pajout)) {
        QMessageBox::information(this, "Succès", "Produit ajouté avec succès!");
        ui->inputnomp->clear();
        ui->boxtype->clear();
        ui->inputquantite->clear();
        ui->inputprixp->clear();
        qDebug() << "Produit ajouté avec succès!";
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du produit.");
        qDebug() << "Échec de l'ajout dans la base";
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pageafficherproduits);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pagemodifierproduit);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pageajoutproduit);
}
void MainWindow::on_pushButtonkhedmakol_clicked()
{
    ui->stackedWidgetpp->setCurrentWidget(ui->pageproduit);
}
void MainWindow::on_pushButtonexit_clicked()
{
    ui->stackedWidgetpp->setCurrentWidget(ui->menup);
}

void MainWindow::on_bouttonconfirmermodification_clicked()
{
    produit p;
    int idp = ui->idproduitmodifie->text().toInt();
    QString nomp = ui->inputnommodif->text();
    int prix = ui->inputprixmodif->text().toInt();
    int quantite = ui->inputquantitemodif->text().toInt();
    QString type = ui->inputtypemodi->text();

    if (p.modifierProduit(idp, type, nomp, prix, quantite)) {
        QMessageBox::information(this, "Modification", "Produit modifié");
        ui->tableauproduits->setModel(p.afficherProduits());
        historique("Modification Produit",nomp,"produit modifié ");


    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du produit");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pagesupprimerproduit);
}

void MainWindow::on_bouttonajouterproduit_clicked()
{

    QString quantite = ui->inputquantite->text();
    QString nom = ui->inputnomp->text();
    QString prixp = ui->inputprixp->text();
    QString typep = ui->boxtype->currentText();
    qDebug() << "User selected:" << typep ;

    if (typep.isEmpty()) {
        QMessageBox::warning(this, "Erreur controle de saisie", "Veuillez saisir le type du produit");
        return;
    }
    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Erreur controle de saisie", "Veuillez saisir le nom du produit");
        return;
    }
    if (prixp.isEmpty()) {
        QMessageBox::warning(this, "Erreur controle de saisie", "Veuillez saisir le prix");
        return;
    }
    if (quantite.isEmpty()) {
        QMessageBox::warning(this, "Erreur controle de saisie", "Veuillez saisir la quantite");
        return;
    }

    bool isInt;
    int quantiteInt = quantite.toInt(&isInt);
    if (!isInt || quantiteInt <= 0) {
        QMessageBox::warning(this, "erreur controle de saisie", "La quantité doit être un nombre entier positif.");
        return;
    }

    int prix = prixp.toInt(&isInt);
    if (!isInt || prix <= 0) {
        QMessageBox::warning(this, "erreur controle de saisie", "Le prix doit être un nombre entier positif.");
        return;
    }

    produit produitAjout(typep, nom, quantiteInt, prix);
    if (produitAjout.ajouterProduit(produitAjout)) {
        QMessageBox::information(this, "Succès", "Produit ajouté avec succès!");
        historique("Ajout Produit",nom,"produit ajouté ");

        ui->tableauproduits->setModel(produit().afficherProduits());
        ui->boxtype->clear();
        ui->inputquantite->clear();
        ui->inputnomp->clear();
        ui->inputprixp->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "echec de l'ajout du produit.");
    }
}

void MainWindow::on_bouttonpageafficherproduit_clicked()
{
    produit p;
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pageafficherproduits);
    ui->tableauproduits->setModel(p.afficherProduits());
    historique("Affichage","PRODUITS","Lister PRODUITS");

}

void MainWindow::on_bouttonpagemodifierproduit_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pagemodifierproduit);
}
void MainWindow::on_bouttonpagestatistique_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pagestatistique);

    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QPieSeries *series = new QPieSeries();

    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM PRODUIT WHERE TYPEP = 'naturel'");
    int naturelCount = query.next() ? query.value(0).toInt() : 0;
    qDebug()<<"naturel="<<naturelCount;
    query.exec("SELECT COUNT(*) FROM PRODUIT WHERE TYPEP = 'chimique'");
    int chimiqueCount = query.next() ? query.value(0).toInt() : 0;
    qDebug()<<"chimique="<<chimiqueCount;



    int totalCount = chimiqueCount + naturelCount;
    qDebug()<<"Total="<<totalCount;


    QPieSlice *chimiqueSlice = series->append("chimique", chimiqueCount);
    QPieSlice *naturelSlice = series->append("naturel", naturelCount);

    chimiqueSlice->setExploded();
    chimiqueSlice->setExplodeDistanceFactor(0.3);

    naturelSlice->setExploded();
    naturelSlice->setExplodeDistanceFactor(0.3);

    chimiqueSlice->setLabelVisible();
    chimiqueSlice->setPen(QPen(QColor(0, 0, 0)));
    chimiqueSlice->setBrush(QColor(0,0,0));

    naturelSlice->setLabelVisible();
    naturelSlice->setPen(QPen(QColor(217,217,217), 2));
    naturelSlice->setBrush(QColor(217,217,217));

    chimiqueSlice->setLabel(QString("chimique: %1%").arg(static_cast<double>(chimiqueCount) / totalCount * 100, 0, 'f', 1));
    naturelSlice->setLabel(QString("naturel: %1%").arg(static_cast<double>(naturelCount) / totalCount * 100, 0, 'f', 1));

    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->pagestatistique->setLayout(layout);
    if(!ui->pagestatistique->layout()){
        ui->pagestatistique->setLayout(new QVBoxLayout());
    }
    ui->pagestatistique->layout()->addWidget(chartView);
}
void MainWindow::on_bouttonpagesupprimer_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pagesupprimerproduit);
}

void MainWindow::on_bouttonpageajouter_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pageajoutproduit);
}
void MainWindow::on_bouttonpagearduino_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pagearduino);
}

void MainWindow::on_bouttonsupprimerproduit_clicked()
{
    produit p;
    int idp = ui->idproduitsupprime->text().toInt();
    if (p.supprimerProduit(idp)) {
        QMessageBox::information(this, "Succès", "Produit supprimé");
        ui->tableauproduits->setModel(p.afficherProduits());
        historique("Suppression","","ID PRODUIT "+idp);

        ui->idproduitsupprime->clear();
    }
}

void MainWindow::on_bouttonrecherchetableau_clicked()
{
    produit p;
    QString recherche = ui->inputrecherchetableau->text();

    QSqlQueryModel *model = p.rechercheparnomproduit(recherche);

    if (model) {
        ui->tableauproduits->setModel(model);
        historique("Recherche",recherche,"Nom Recherché"+recherche);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche.");
    }
}

void MainWindow::on_triparnom_clicked()
{
    produit p;
    QSqlQueryModel *model = p.trierProduitsParNom();
    ui->tableauproduits->setModel(model);
}

void MainWindow::on_bouttonidproduitmodif_clicked()
{
    produit p;
    int idp = ui->idproduitmodifie->text().toInt();
    if (idp <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID produit valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT typep, nomp, prixp, quantite FROM Produit WHERE idp = :idp");
    query.bindValue(":idp", idp);

    if (query.exec() && query.next()) {
        QString typep = query.value("typep").toString();
        QString nomp = query.value("nomp").toString();
        int prixp = query.value("prixp").toInt();
        int quantite = query.value("quantite").toInt();

        ui->inputnommodif->setText(nomp);
        ui->inputtypemodi->setText(typep);
        ui->inputquantitemodif->setText(QString::number(quantite));
        ui->inputprixmodif->setText(QString::number(prixp));
    } else {
        QMessageBox::information(this, "Erreur", "ID introuvable");
    }
}
void MainWindow::on_pushButton_pdf_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer le fichier PDF"), "", tr("PDF Files (*.pdf)"));
    if (fileName.isEmpty()) return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize::A4);
    writer.setResolution(300);

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF pour l'écriture."));
        return;
    }

    // Titre centré en haut de la page
    QFont titleFont("Arial", 16, QFont::Bold);
    painter.setFont(titleFont);

    // Créer un rectangle couvrant la largeur de la page pour centrer le texte
    QRect titleRect(0, 100, writer.width(), 100);  // Rectangle centré en haut avec une hauteur de 100
    painter.drawText(titleRect, Qt::AlignCenter, tr("Liste des produits"));
    int yOffset = 300;

    // Récupérer le modèle de données
    QAbstractItemModel *model = ui->tableauproduits->model();
    if (model) {
        int rowCount = model->rowCount();
        int columnCount = model->columnCount();

        int xOffset = 10;
        int columnWidth = 300;
        int rowHeight = 100;
        int columnSpacing = 10;

        // Couleur pour toutes les cellules et les en-têtes
        QColor cellColor(217, 217, 217);  // Couleur modifiée (rgb(217, 217, 217))
        painter.setBrush(QBrush(cellColor));

        // Police et couleur pour les en-têtes
        painter.setFont(QFont("Arial", 8, QFont::Bold));
        painter.setPen(Qt::white);
        for (int col = 0; col < columnCount; ++col) {
            QRect headerRect(xOffset + col * (columnWidth + columnSpacing), yOffset, columnWidth, rowHeight);
            painter.drawRect(headerRect);
            painter.drawText(headerRect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
        }

        yOffset += rowHeight;

        // Police pour les cellules de données
        painter.setFont(QFont("Arial", 12));
        painter.setPen(Qt::white);
        for (int row = 0; row < rowCount; ++row) {
            for (int col = 0; col < columnCount; ++col) {
                QRect cellRect(xOffset + col * (columnWidth + columnSpacing), yOffset, columnWidth, rowHeight);
                painter.drawRect(cellRect);
                painter.drawText(cellRect, Qt::AlignCenter | Qt::TextWordWrap, model->data(model->index(row, col)).toString());
            }
            yOffset += rowHeight;
        }
    }

    painter.end();
    QMessageBox::information(this, tr("Succès"), tr("Le fichier PDF a été généré avec succès."));
    historique("Export PDF",fileName,"Fichier exporté"+fileName);

}
void MainWindow::on_pushButton_stat_clicked() {

}
void MainWindow::on_validationsms_clicked()
{
    // Collecter les informations de l'utilisateur (destinataire et message)
    QString destinataire = QInputDialog::getText(this, "Numéro de destinataire", "Entrez le numéro de téléphone (avec indicatif international, ex: +123456789):");
    if (destinataire.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone est requis.");
        return;
    }

    QString message = QInputDialog::getText(this, "Message", "Entrez le message à envoyer :");
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le message ne peut pas être vide.");
        return;
    }

    // Appeler la fonction pour envoyer le SMS
    envoyerSMS(destinataire, message);
    historique("Validation SMS ",message,"Validation SMS  "+destinataire);

}

void MainWindow::envoyerSMS(const QString &destinataire, const QString &message)
{

    QString authToken = "";
    QString from = "+12512418286"; // Numéro Twilio vérifié

    // URL de l'API Twilio
    QString url = QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(sid);

    // Créer les données pour la requête
    QByteArray postData;
    postData.append("To=" + QUrl::toPercentEncoding(destinataire));
    postData.append("&From=" + QUrl::toPercentEncoding(from));
    postData.append("&Body=" + QUrl::toPercentEncoding(message));

    // Préparer la requête HTTP
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Ajouter l'en-tête d'autorisation (Basic Auth)
    QString authHeader = QString("%1:%2").arg(sid).arg(authToken).toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + authHeader.toUtf8());

    // Envoyer la requête
    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, &QNetworkAccessManager::finished, this, &MainWindow::onSmsReplyFinished);
    networkAccessManager->post(request, postData);
}

void MainWindow::onSmsReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // Traiter la réponse JSON en cas de succès
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject responseObject = jsonResponse.object();
        QString sid = responseObject.value("sid").toString();

        QMessageBox::information(this, "Succès", QString("SMS envoyé avec succès. SID: %1").arg(sid));
    } else {
        // Afficher un message d'erreur en cas de problème
        QMessageBox::critical(this, "Erreur", QString("Échec de l'envoi du SMS : %1").arg(reply->errorString()));
    }

    reply->deleteLater(); // Libérer la mémoire
}

void MainWindow::on_bouttonpagehistorique_clicked()
{
    ui->stackedwidgetprincipale->setCurrentWidget(ui->pagehistorique);

    QString filePath = QCoreApplication::applicationDirPath() + "/historique.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur","fichier historique vide");
        return;
    }

    QTextStream in(&file);
    QString historiqueContent = in.readAll();
    file.close();

    ui->textHistorique->setPlainText(historiqueContent);
}

void MainWindow::historique(const QString &action, const QString &nomProduit, const QString &details) {
    QString filePath = QCoreApplication::applicationDirPath() + "/historique.txt";

    QFile file(filePath);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "fichier historique vide");
        return;
    }

    QTextStream out(&file);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    out << timestamp << " - Action: " << action << " - Produit: " << nomProduit << " - " << details << "\n";
    file.close();
}
void MainWindow::loadHistoriqueFile()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/historique.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Erreur", "Fichier Historique vide");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    ui->textHistorique->setPlainText(content);
}

// Slot pour vérifier l'ID de l'employé saisi dans le QLineEdit
void MainWindow::verifyEmployeID()
{
    QString employeID = ui->lineEditEmployeeID->text();  // Récupérer l'ID de l'employé depuis le QLineEdit

    if (employeID.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID d'employé.");
        return;
    }
    // Convertir l'UID saisi en un nombre
    /* quint64 numericID = convertUIDtoNumber(employeeID);
    QString employeeCardCode = QString::number(numericID);  // Convertir le nombre en QString pour l'utiliser dans SQL*/

    // Traiter l'ID de l'employé
    processEmployeID(employeID);
}

void MainWindow::processEmployeID(const QString &employeID)
{
    Arduino A ;
    // Vérifier si l'ID de l'employé existe dans la base de données en utilisant CARDUID
    QString employeeCardCode = getEmployeeCardCodeFromDatabase(employeID);
    QString result_poste;

    if (!employeeCardCode.isEmpty()) {
        // Si l'ID existe, récupérer le nom et le prénom de l'employé
         QString employeID = getemployeIDFromDatabase(employeeCardCode).toUpper();
        QString employeposte = getemployeposteFromDatabase(employeeCardCode).toUpper();



        result_poste = "POSTE:" + employeposte + ",ID: " + employeID;

        ui->labelResult->setText("Welcome, " + result_poste);   // Afficher sur le QLabel
        QByteArray employeeFullNameData = result_poste.toUtf8();
        A.write_to_arduino(employeeFullNameData); // Envoyer au Arduino
    } else {
        result_poste = "ERROR: Card Not Found";  // Message d'erreur si l'ID n'est pas trouvé
        ui->labelResult->setText("Access Denied: " + result_poste); // Afficher le message d'erreur sur le QLabel
        QByteArray errorMessage = result_poste.toUtf8();
        A.write_to_arduino(errorMessage); // Envoyer le message d'erreur à Arduino
    }
}


QString MainWindow::getEmployeeCardCodeFromDatabase(const QString &employeID)
{
    QString employeeCardCode;

    QSqlQuery query;
    query.prepare("SELECT CARDUID FROM EMPLOYE WHERE CARDUID = :employeID");
    query.bindValue(":employeID", employeID.trimmed());
    qDebug() << "Executing query:" << query.lastQuery();

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
        return employeeCardCode;
    }

    if (query.next()) {
        employeeCardCode = query.value(0).toString();
        qDebug() << "UID trouvé :" << employeeCardCode;
    } else {
        qDebug() << "Aucun UID trouvé pour :" << employeID;
    }

    return employeeCardCode; // Corrigé : retour à la bonne position
}

 QString MainWindow::getemployeposteFromDatabase (const QString &employeeCardCode)
{
    QString employeposte;

    QSqlQuery query;
    query.prepare("SELECT POSTE FROM EMPLOYE WHERE CARDUID = :employeeCardCode");
    query.bindValue(":employeeCardCode", employeeCardCode);

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError();
        return employeposte;
    }

    if (query.next()) {
        employeposte = query.value(0).toString(); // Récupérer le nom
    }

    return employeposte;
}

QString MainWindow::getemployeIDFromDatabase(const QString &employeeCardCode)
{
    QString employeID;

    QSqlQuery query;
    query.prepare("SELECT IDE FROM EMPLOYE WHERE CARDUID = :employeeCardCode");
    query.bindValue(":employeeCardCode", employeeCardCode);

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError();
        return employeID;
    }

    if (query.next()) {
        employeID = query.value(0).toString(); // Récupérer le prénom
    }

    return employeID;
}

void MainWindow::on_pushButtonverifer_clicked()
{
    Arduino A;
    int ret=A.connect_arduino();
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    // QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(readDataFromArduino()));

    // Appeler la méthode qui vérifie l'ID de l'employé
    verifyEmployeID();  // Cette fonction doit être définie dans ton code comme tu l'as fait précédemment
}

