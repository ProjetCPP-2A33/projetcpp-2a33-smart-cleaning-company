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
#include "client.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include <QPrinter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    arduino() // Initialiser l'Arduino ici
{
    ui->setupUi(this);
    int ret = arduino.connect_arduino(); // Essayer de connecter à Arduino dans le constructeur
    if (ret == 0) {
        qDebug() << "Le port série est ouvert avec succès.";
    } else {
        qDebug() << "Échec de l'ouverture du port série.";
    }

    setupConnections();
    //mahdiiiiiiiiiiiiiiiiiiiiiiiiii
    afficherMachines();  // Display existing machines when the app starts



    // Connect the Tri par ID button to the sorting function

    connect(ui->pb_tri, &QPushButton::clicked, this, &MainWindow::on_pb_tri_clicked);
    connect(ui->pb_search, &QPushButton::clicked, this, &MainWindow::on_pb_search_clicked);
    connect(ui->pb_stat, &QPushButton::clicked, this, &MainWindow::on_pb_stat_clicked);

    // Theme setup (Dark/Light)
    darkPalette.setColor(QPalette::Window, QColor(30, 30, 30));            // Dark background
    darkPalette.setColor(QPalette::WindowText, Qt::black);                // Text color: white
    darkPalette.setColor(QPalette::Base, QColor(45, 45, 45));             // Base color (input fields, etc.)
    darkPalette.setColor(QPalette::AlternateBase, QColor(60, 60, 60));    // Alternate base for selection or item backgrounds
    darkPalette.setColor(QPalette::ToolTipBase, QColor(50, 50, 50));      // Tooltip background
    darkPalette.setColor(QPalette::ToolTipText, Qt::black);               // Tooltip text color
    darkPalette.setColor(QPalette::Text, Qt::green);                      // General text color
    darkPalette.setColor(QPalette::Button, QColor(50, 50, 50));           // Button background color
    darkPalette.setColor(QPalette::ButtonText, Qt::black);                // Button text color
    darkPalette.setColor(QPalette::Highlight, QColor(0, 128, 255));       // Highlight color (e.g., selected items)
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);           // Highlighted text color
    darkPalette.setColor(QPalette::Text, QColor(255, 255, 255));

    // Light Mode Palette Setup
    lightPalette.setColor(QPalette::Window, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::AlternateBase, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ToolTipBase, Qt::white);
    lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(200, 200, 200));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);

    // Initially set dark theme
    QApplication::setPalette(darkPalette);



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
void MainWindow::on_bclient_clicked()
{
    ui->stackedWidgetpp->setCurrentWidget(ui->pageclientpp);
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
void MainWindow::on_bmachine_clicked()
{
    ui->stackedWidgetpp->setCurrentWidget(ui->pagemachine);
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
    QString sid = "";
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

    // Traiter l'ID de l'employé
    processEmployeID(employeID);
}

void MainWindow::processEmployeID(const QString &employeID)
{
    // Vérifier si l'ID de l'employé existe dans la base de données en utilisant CARDUID
    QString employeeCardCode = getEmployeeCardCodeFromDatabase(employeID);
    QString result_poste;

    if (!employeeCardCode.isEmpty()) {
        // Si l'ID existe, récupérer le nom et le prénom de l'employé
        QString employeID = getemployeIDFromDatabase(employeeCardCode).toUpper();
        QString employeposte = getemployeposteFromDatabase(employeeCardCode).toUpper();

        result_poste = "POSTE:" + employeposte + ", ID: " + employeID;

        ui->labelResult->setText("Welcome, " + result_poste);   // Afficher sur le QLabel
        QByteArray employeeFullNameData = result_poste.toUtf8();
        arduino.write_to_arduino(employeeFullNameData); // Envoyer au Arduino
    } else {
        result_poste = "ERROR: Card Not Found";  // Message d'erreur si l'ID n'est pas trouvé
        ui->labelResult->setText("Access Denied: " + result_poste); // Afficher le message d'erreur sur le QLabel
        QByteArray errorMessage = result_poste.toUtf8();
        arduino.write_to_arduino(errorMessage); // Envoyer le message d'erreur à Arduino
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

    return employeeCardCode;
}

QString MainWindow::getemployeposteFromDatabase(const QString &employeeCardCode)
{
    QString employeposte;
    QSqlQuery query;
    query.prepare("SELECT POSTE FROM EMPLOYE WHERE CARDUID = :employeeCardCode");
    query.bindValue(":employeeCardCode", employeeCardCode);

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
        return employeposte;
    }

    if (query.next()) {
        employeposte = query.value(0).toString(); // Récupérer le poste
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
        qDebug() << "Query execution error:" << query.lastError().text();
        return employeID;
    }

    if (query.next()) {
        employeID = query.value(0).toString(); // Récupérer l'ID
    }

    return employeID;
}

void MainWindow::on_pushButtonverifer_clicked()
{
    verifyEmployeID();  // Vérification de l'ID de l'employé
}
//salimmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
void MainWindow::setupConnections()
{
    connect(ui->ajout, &QPushButton::clicked, this, &MainWindow::ajouterClient);
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::afficher);
    connect(ui->supp, &QPushButton::clicked, this, &MainWindow::supprimerClient);
    connect(ui->mod, &QPushButton::clicked, this, &MainWindow::modifierClient);
    connect(ui->tri, &QPushButton::clicked, this, &MainWindow::tri);
    connect(ui->rech, &QPushButton::clicked, this, &MainWindow::recherche);
    connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::expPDF);
    connect(ui->envoyer, &QPushButton::clicked, this, &MainWindow::sendEmail);
    connect(ui->affgraph, &QPushButton::clicked, this, &MainWindow::stat);
    connect(ui->calcred, &QPushButton::clicked, this, &MainWindow::PtMrc);
    //f
    connect(ui->switch1, &QPushButton::clicked, this, &MainWindow::page2Wid);
    connect(ui->bstat, &QPushButton::clicked, this, &MainWindow::page3Wid);
    connect(ui->retour, &QPushButton::clicked, this, &MainWindow::page1Wid);
    connect(ui->mailing, &QPushButton::clicked, this, &MainWindow::page4Wid);
    connect(ui->quitter, &QPushButton::clicked, this, &MainWindow::page1Main);
    connect(ui->quittermachine, &QPushButton::clicked, this, &MainWindow::page1Main);


    connect(ui->retour1, &QPushButton::clicked, this, &MainWindow::page1Wid);
    connect(ui->retour2, &QPushButton::clicked, this, &MainWindow::page1Wid);


}
void MainWindow::page1Wid()
{
    ui->stack->setCurrentWidget(ui->afficher);
}

void MainWindow::page2Wid()
{
    ui->stack->setCurrentWidget(ui->gerer);
}
void MainWindow::page4Wid()
{
    ui->stack->setCurrentWidget(ui->mail_2);
}
void MainWindow::page3Wid()
{
    ui->stack->setCurrentWidget(ui->stat);
}
void MainWindow::page1Main()
{
    ui->stackedWidgetpp->setCurrentWidget(ui->menup);
}
void MainWindow::ajouterClient()
{

    int id=ui->idc->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int numTel=ui->numtel->text().toInt();
    QString mail=ui->mail->text();
    QString typeAff=ui->typeaff->text();
    int nbrAff=ui->nbraff->text().toInt();

    if(verif(id,numTel,mail,nbrAff))
    {
        Client c(id,nom,prenom,numTel,mail,typeAff,nbrAff);

        bool test=c.ajouter();
        if(test)
        {
            ui->tab->setModel(client.afficher());

            QMessageBox::information(nullptr, QObject::tr("Succée!"),
                                     QObject::tr("Client Ajouté. \n"
                                                 "Clickez ici pour sortir."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                                  QObject::tr("Client pas ajouté. \n"
                                              "Clickez ici pour sortir."), QMessageBox::Cancel);
        }
    }

}
void MainWindow::afficher()
{
    ui->tab->setModel(client.afficher());
}
bool MainWindow::verif(int id,int numTel,QString mail,int nbrAff)
{

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur de saisie", "L'ID doit être un entier positif.");
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM client WHERE idC = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "Erreur de saisie", "Cet ID est déjà utilisé.");
            return false;
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'ID.");
        return false;
    }

    string num=to_string(numTel);
    if (numTel <= 0 || num.size()<8 || num.size()>8) {
        QMessageBox::warning(this, "Erreur de saisie", "le numero de tel doit être un entier positif de 8 chiffres.");
        return false;
    }

    query.prepare("SELECT COUNT(*) FROM client WHERE numTel = :numTel");
    query.bindValue(":numTel", numTel);
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "Erreur de saisie", "Cet numero de tel est déjà utilisé.");
            return false;
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification du numero de tel.");
        return false;
    }

    QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    if (!emailRegex.match(mail).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "L'adresse e-mail n'est pas valide.");
        return false;
    }

    // Email uniqueness check
    QSqlQuery emailQuery;
    emailQuery.prepare("SELECT COUNT(*) FROM client WHERE mail = :email");
    emailQuery.bindValue(":email", mail);
    if (emailQuery.exec() && emailQuery.next()) {
        int emailCount = emailQuery.value(0).toInt();
        if (emailCount > 0) {
            QMessageBox::warning(this, "Erreur de saisie", "Cet e-mail est déjà utilisé.");
            return false;
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'e-mail.");
        return false;
    }

    if (nbrAff <= 0) {
        QMessageBox::warning(this, "Erreur de saisie", "le nbr d'affaire doit être un entier positif.");
        return false;
    }
    return true;
}
void MainWindow::supprimerClient()
{
    int id=ui->idc->text().toInt();
    bool test=client.supprimer(id);

    if(test)
    {
        ui->tab->setModel(client.afficher());

        QMessageBox::information(nullptr, QObject::tr("Succée!"),
                                 QObject::tr("Client supprimé. \n"
                                             "Clickez ici pour sortir."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                              QObject::tr("Suppression non effectuée. \n"
                                          "Clickez ici pour sortir."), QMessageBox::Cancel);
    }
}

void MainWindow::modifierClient()
{
    int id=ui->idc->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int numTel=ui->numtel->text().toInt();
    QString mail=ui->mail->text();
    QString typeAff=ui->typeaff->text();
    int nbrAff=ui->nbraff->text().toInt();

    if(verif1(id,numTel,mail,nbrAff))
    {
        Client c(id,nom,prenom,numTel,mail,typeAff,nbrAff);
        bool test=client.modifier(id,nom,prenom,numTel,mail,typeAff,nbrAff);

        if(test)
        {
            ui->tab->setModel(client.afficher());

            QMessageBox::information(nullptr, QObject::tr("Succée!"),
                                     QObject::tr("Client modifié. \n"
                                                 "Clickez ici pour sortir."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                                  QObject::tr("Modification non effectuée. \n"
                                              "Clickez ici pour sortir."), QMessageBox::Cancel);
        }
    }
}
bool MainWindow::verif1(int id,int numTel,QString mail,int nbrAff)
{
    QSqlQuery query;

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur de saisie", "L'ID doit être un entier positif.");
        return false;
    }

    string num=to_string(numTel);
    if (numTel <= 0 || num.size()<8 || num.size()>8) {
        QMessageBox::warning(this, "Erreur de saisie", "le numero de tel doit être un entier positif de 8 chiffres.");
        return false;
    }

    query.prepare("SELECT COUNT(*) FROM client WHERE numTel = :numTel AND idC != :id");
    query.bindValue(":numTel", numTel);
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "Erreur de saisie", "Cet numero de tel est déjà utilisé.");
            return false;
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification du numero de tel.");
        return false;
    }

    QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    if (!emailRegex.match(mail).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "L'adresse e-mail n'est pas valide.");
        return false;
    }

    // Email uniqueness check
    QSqlQuery emailQuery;
    emailQuery.prepare("SELECT COUNT(*) FROM client WHERE mail = :email AND idC != :id");
    emailQuery.bindValue(":email", mail);
    emailQuery.bindValue(":id", id);
    if (emailQuery.exec() && emailQuery.next()) {
        int emailCount = emailQuery.value(0).toInt();
        if (emailCount > 0) {
            QMessageBox::warning(this, "Erreur de saisie", "Cet e-mail est déjà utilisé.");
            return false;
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'e-mail.");
        return false;
    }

    if (nbrAff <= 0) {
        QMessageBox::warning(this, "Erreur de saisie", "le nbr d'affaire doit être un entier positif.");
        return false;
    }
    return true;
}

void MainWindow::tri()
{
    QSqlQueryModel *model=client.tri();

    if(model)
    {
        ui->tab->setModel(model);

        QMessageBox::information(nullptr, QObject::tr("Succée!"),
                                 QObject::tr("Table triée. \n"
                                             "Clickez ici pour sortir."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                              QObject::tr("Tri non effectuée. \n"
                                          "Clickez ici pour sortir."), QMessageBox::Cancel);
    }
}

void MainWindow::recherche()
{
    QString combo = ui->combo->currentText(); // Get selected combo value
    int id = -1;                              // Default value for ID
    QString nom, prenom;                      // Default empty values for name and surname

    // Handle input based on the selected criterion
    if (combo == "Id") {
        if (ui->recherche->text().isEmpty()) {
            QMessageBox::warning(this, QObject::tr("Erreur!"),
                                 QObject::tr("Veuillez entrer un ID valide."),
                                 QMessageBox::Cancel);
            return;
        }
        id = ui->recherche->text().toInt();
    } else if (combo == "Nom") {
        if (ui->recherche->text().isEmpty()) {
            QMessageBox::warning(this, QObject::tr("Erreur!"),
                                 QObject::tr("Veuillez entrer un nom valide."),
                                 QMessageBox::Cancel);
            return;
        }
        nom = ui->recherche->text();
    } else if (combo == "Prénom") {
        if (ui->recherche->text().isEmpty()) {
            QMessageBox::warning(this, QObject::tr("Erreur!"),
                                 QObject::tr("Veuillez entrer un prénom valide."),
                                 QMessageBox::Cancel);
            return;
        }
        prenom = ui->recherche->text();
    }

    // Call Client::recherche with parameters
    QSqlQueryModel* model = client.recherche(id, nom, prenom, combo);

    if (model) {
        ui->tab->setModel(model);

        QMessageBox::information(this, QObject::tr("Succès!"),
                                 QObject::tr("Recherche effectuée.\n"
                                             "Cliquez ici pour sortir."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, QObject::tr("Erreur!"),
                              QObject::tr("Recherche non effectuée.\n"
                                          "Cliquez ici pour sortir."),
                              QMessageBox::Cancel);
    }
}
void MainWindow::expPDF()
{
    // Ouvrir une boîte de dialogue pour sélectionner le chemin de sauvegarde du PDF
    QString nomFichier = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");
    if (!nomFichier.isEmpty()) {
        Client emp;

        // Récupérer les données du client
        QSqlQueryModel *model = emp.afficher();

        // Vérifier si les données existent
        if (model->rowCount() == 0) {
            QMessageBox::warning(this, "Aucune donnée", "Aucun client à exporter.");
            delete model; // Libération de la mémoire
            return;
        }

        // Exporter vers PDF
        bool exportSuccess = emp.exporterPDF(nomFichier, model);

        // Libération de mémoire
        delete model;

        if (exportSuccess) {
            QMessageBox::information(this, "Exportation PDF", "Exportation vers PDF réussie !");
        } else {
            QMessageBox::critical(this, "Erreur d'exportation", "L'exportation vers PDF a échoué.");
        }
    }
}

//mail
void MainWindow::sendEmail() {
    // Récupérer les informations saisies par l'utilisateur
    QString recipient = ui->mail_3->text(); // Email du destinataire

    if (recipient.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir l'adresse email du destinataire.");
        return;
    }

    // Validation de l'adresse email avec QRegularExpression
    QRegularExpression emailRegex("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    QRegularExpressionMatch match = emailRegex.match(recipient);
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Erreur", "L'adresse email saisie est invalide.");
        return;
    }

    // Initialiser le manager réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Préparer la requête HTTP vers l'API Postmark
    QNetworkRequest request(QUrl("https://api.postmarkapp.com/email"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-Postmark-Server-Token", "ac1040c0-cc8f-4c7e-b031-aceade2c28e3"); // Votre token API

    // Construire le contenu de l'email
    QJsonObject emailObject;
    emailObject["From"] = "salim.benbrahim@esprit.tn"; // Adresse email expéditeur (vérifiée dans Postmark)
    emailObject["To"] = recipient; // Adresse email du destinataire
    emailObject["Subject"] = "Email de test depuis Qt et Postmark"; // Sujet de l'email
    emailObject["TextBody"] = "Bonjour,\nCeci est un test envoyé avec Qt et Postmark."; // Contenu texte de l'email

    QJsonDocument emailDoc(emailObject);

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, emailDoc.toJson());

    // Gérer la réponse de l'API
    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(nullptr, "Succès", "Email envoyé avec succès !");
        } else {
            QMessageBox::critical(nullptr, "Erreur", "Échec de l'envoi de l'email : " + reply->errorString());
        }
        reply->deleteLater();
    });
}
void MainWindow::stat()
{
    // Créer une scène et la vue pour afficher le graphique
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graph->setScene(scene);  // Assurez-vous que graphicsView est un QGraphicsView dans votre UI

    QSqlQuery query("SELECT typeAffaire, COUNT(*) AS count FROM client GROUP BY typeAffaire");

    // Paramètres de positionnement pour les barres
    int barWidth = 50;
    int spaceBetweenBars = 40;
    int xPosition = 50; // Position X initiale pour les barres
    QStringList categories;

    // Récupérer les résultats de la requête et préparer les données pour le graphique
    while (query.next()) {
        QString typeAffaire = query.value("typeAffaire").toString();
        int count = query.value("count").toInt();

        // Créer une barre (QGraphicsRectItem) pour chaque typeAffaire
        QGraphicsRectItem *bar = new QGraphicsRectItem(xPosition, 300 - count * 5, barWidth, count * 5);  // Hauteur proportionnelle à count
        bar->setBrush(Qt::blue);  // Choisissez la couleur de la barre

        // Ajouter la barre à la scène
        scene->addItem(bar);

        // Ajouter un texte pour afficher le typeAffaire sous la barre
        QGraphicsTextItem *textItem = new QGraphicsTextItem(typeAffaire);
        textItem->setPos(xPosition, 310);  // Position du texte sous la barre
        scene->addItem(textItem);

        // Ajouter le nom du typeAffaire à la liste des catégories
        categories.append(typeAffaire);

        // Mettre à jour la position pour la prochaine barre
        xPosition += barWidth + spaceBetweenBars;
    }

    // Ajuster la vue
    ui->graph->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::PtMrc()
{
    int pm=0;

    QSqlQuery query;

    int id = ui->idred->text().toInt();

    query.prepare("SELECT nbrAffaire from client WHERE idC = :id");
    query.bindValue(":id",id);

    if (query.exec()) {
        if (query.next()) {
            int nbrAffaire = query.value("nbrAffaire").toInt();
            if(nbrAffaire<3)
            {
                pm=0;
            }
            else if((nbrAffaire==3) || (nbrAffaire==4))
            {
                pm=10;
            }
            else if((nbrAffaire==5) || (nbrAffaire==6) || (nbrAffaire==7))
            {
                pm=15;
            }
            else
            {
                pm=20;
            }
            ui->reduction->setText(QString("Réduction de %1 %").arg(pm));
        }
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Erreur!"),
                              QObject::tr("Erreur.\n"
                                          "Cliquez ici pour sortir."),
                              QMessageBox::Cancel);
    }
}

//MAHDIIIIIIIIIIIIIIIIIIIIIIIIIIIi
void MainWindow::afficherMachines() {
    Machine machine;
    QSqlQueryModel *model = machine.afficher();
    ui->tab_aff->setModel(model);  // Set the model to display machines in tab_aff
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id_M = ui->le_id_M->text().toInt();
    QString etatM = ui->le_etatM->text();
    int responsableM = ui->le_responsableM->text().toInt();  // Convert this field to int
    QString descriptionM = ui->le_descriptionM->text();
    QString emplacementM = ui->le_emplacementM->text();

    // Pass `responsableM` as an int to the constructor
    Machine m(id_M, etatM, responsableM, descriptionM, emplacementM);
    bool test = m.ajouter();

    if (test) {
        QMessageBox::information(this, "Succès", "Machine ajoutée avec succès.");
        afficherMachines();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la machine.");
    }
}

void MainWindow::on_pb_supprimer_clicked() {
    int id_M = ui->le_id_sup->text().toInt();  // Get the machine ID to delete

    // Step 1: Check if the ID exists in the database
    QSqlQuery query;
    query.prepare("SELECT * FROM machine WHERE id_M = :id_M");
    query.bindValue(":id_M", id_M);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'ID.");
        return;
    }

    // If the ID doesn't exist in the database
    if (!query.next()) {
        QMessageBox::warning(this, "ID Introuvable", "L'ID n'existe pas dans la base de données.");
        return;
    }

    // Step 2: ID exists, now delete it
    Machine m;
    bool test = m.supprimer(id_M);  // Call the supprimer method to delete the machine

    // Step 3: If delete was successful, refresh the table and show a success message
    if (test) {
        afficherMachines();  // Refresh the display after deleting the machine
        QMessageBox::information(this, "Succès", "Machine supprimée avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression de la machine.");
    }
}

void MainWindow::on_pb_modifier_clicked() {
    int id_M = ui->le_id_mod->text().toInt();  // Get the machine ID to modify
    QString etatM = ui->le_etatMod->text();    // Get the state of the machine
    int responsableM = ui->le_responsableMod->text().toInt();  // Convert to int for responsible person ID
    QString descriptionM = ui->le_descriptionMod->text();  // Get the description of the machine
    QString emplacementM = ui->le_emplacementMod->text();  // Get the location of the machine

    // Step 1: Check if the ID exists in the database
    QSqlQuery query;
    query.prepare("SELECT * FROM machine WHERE id_M = :id_M");
    query.bindValue(":id_M", id_M);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'ID.");
        return;
    }

    // If the ID doesn't exist in the database
    if (!query.next()) {
        QMessageBox::warning(this, "ID Introuvable", "L'ID n'existe pas dans la base de données.");
        return;
    }

    // Step 2: ID exists, now update the machine details
    Machine m(id_M, etatM, responsableM, descriptionM, emplacementM);
    bool test = m.modifier(id_M);  // Call the modifier method to update the machine details

    // Step 3: If update was successful, refresh the table and show a success message
    if (test) {
        afficherMachines();  // Refresh the display after modifying the machine
        QMessageBox::information(this, "Succès", "Machine modifiée avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la machine.");
    }
}

void MainWindow::on_pb_pdf_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

    // Check if the user entered a filename
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "No file selected", "Please select a file to save the PDF.");
        return;
    }

    // Ensure the file has a .pdf extension
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    // Create a QPrinter object for PDF output
    QPrinter printer(QPrinter::PrinterMode::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    // Prepare a text document for the PDF content
    QTextDocument doc;

    // Start building the HTML content for the PDF
    QString htmlContent = "<h1>Machine Report</h1><table border='1' cellpadding='5'><tr>"
                          "<th>ID</th><th>Etat</th><th>Responsable</th><th>Description</th><th>Emplacement</th></tr>";

    // Access the model of the QTableView
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tab_aff->model());

    if (!model) {
        QMessageBox::warning(this, "Error", "Unable to access the data model.");
        return;
    }

    // Loop through the rows of the model and extract the data
    int rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // Extract data from each column in the row
        QString id_M = model->data(model->index(row, 0)).toString();  // Column 0 (ID)
        QString etatM = model->data(model->index(row, 1)).toString();  // Column 1 (Etat)
        QString responsableM = model->data(model->index(row, 2)).toString();  // Column 2 (Responsable)
        QString descriptionM = model->data(model->index(row, 3)).toString();  // Column 3 (Description)
        QString emplacementM = model->data(model->index(row, 4)).toString();  // Column 4 (Emplacement)

        // Add the row data to the HTML table
        htmlContent += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>")
                           .arg(id_M)
                           .arg(etatM)
                           .arg(descriptionM)
                           .arg(responsableM)
                           .arg(emplacementM);
    }

    // Close the table tag
    htmlContent += "</table>";

    // Set the HTML content to the QTextDocument
    doc.setHtml(htmlContent);

    // Render the document to the printer (PDF)
    doc.print(&printer);

    // Show a message box confirming PDF creation
    QMessageBox::information(this, "PDF Saved", "The PDF has been saved to " + fileName);
}

void MainWindow::on_pb_tri_clicked() {
    // Create a query to select all machines sorted by ID
    QSqlQuery query;
    query.prepare("SELECT * FROM machine ORDER BY id_M ASC");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec du tri des machines par ID.");
        return;
    }

    // Create a model to display the sorted data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Set the sorted model to the table view
    ui->tab_aff->setModel(model);
}

void MainWindow::on_pb_search_clicked() {
    QString searchTerm = ui->le_search->text();  // Get the search input from the user

    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Empty Input", "Please enter an ID to search.");
        return;
    }

    // Query to search for machine by ID
    QSqlQuery query;
    query.prepare("SELECT * FROM machine WHERE id_M = :id_M");
    query.bindValue(":id_M", searchTerm);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to fetch data from the database.");
        return;
    }

    // Check if results were found
    if (query.next()) {
        // Create a model to display the search result
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tab_aff->setModel(model);  // Set the model to the table view
    } else {
        QMessageBox::information(this, "No Results", "No machine found with the provided ID.");
    }
}

/*void MainWindow::on_pb_stat_clicked() {
    // Query to get the total number of machines in the database
    QSqlQuery totalQuery;
    totalQuery.prepare("SELECT COUNT(*) FROM machine");

    if (!totalQuery.exec()) {
        QMessageBox::critical(this, "Error", "Unable to fetch total machine count.");
        return;
    }

    totalQuery.next();  // Move to the first (and only) row
    int totalMachines = totalQuery.value(0).toInt();

    // Query to get the number of machines in a specific state (e.g., "Operational")
    QString state = "en panne";  // You can make this dynamic based on user input
    QSqlQuery stateQuery;
    stateQuery.prepare("SELECT COUNT(*) FROM machine WHERE etatM = :state");
    stateQuery.bindValue(":state", state);

    if (!stateQuery.exec()) {
        QMessageBox::critical(this, "Error", "Unable to fetch machine count by state.");
        return;
    }

    stateQuery.next();  // Move to the first (and only) row
    int machinesInState = stateQuery.value(0).toInt();

    // Display the stats in a QMessageBox
    QString message = QString("Total Machines: %1\nMachines in state '%2': %3")
                          .arg(totalMachines)
                          .arg(state)
                          .arg(machinesInState);

    QMessageBox::information(this, "Machine Statistics", message);
}*/


void MainWindow::on_pb_stat_clicked()
{
    // Create a new model for executing SQL queries
    QSqlQueryModel *model = new QSqlQueryModel();

    // Query for different statuses (you can adjust these based on your actual database schema)
    model->setQuery("SELECT * FROM machine WHERE etatM = 'en panne'");
    float panneCount = model->rowCount();  // Count how many machines are 'en panne'

    model->setQuery("SELECT * FROM machine WHERE etatM = 'maintenance'");
    float maintenanceCount = model->rowCount();  // Count how many machines are in 'maintenance'

    model->setQuery("SELECT * FROM machine WHERE etatM = 'batterie faible'");
    float batterieCount = model->rowCount();  // Count how many machines have 'batterie faible'

    model->setQuery("SELECT * FROM machine WHERE etatM = 'active'");
    float activeCount = model->rowCount();  // Count how many machines are 'active'

    // Calculate the total number of machines
    float totalCount = panneCount + maintenanceCount + batterieCount + activeCount;

    // Create strings to display as labels with percentages
    QString panneLabel = QString("en panne: %1%").arg(QString::number((panneCount * 100) / totalCount, 'f', 2));
    QString maintenanceLabel = QString("maintenance: %1%").arg(QString::number((maintenanceCount * 100) / totalCount, 'f', 2));
    QString batterieLabel = QString("batterie Faible: %1%").arg(QString::number((batterieCount * 100) / totalCount, 'f', 2));
    QString activeLabel = QString("active: %1%").arg(QString::number((activeCount * 100) / totalCount, 'f', 2));

    // Create a pie chart series and add the data
    QPieSeries *series = new QPieSeries();
    series->append(panneLabel, panneCount);
    series->append(maintenanceLabel, maintenanceCount);
    series->append(batterieLabel, batterieCount);
    series->append(activeLabel, activeCount);

    // Make slices clickable and show labels
    if (panneCount != 0) {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (maintenanceCount != 0) {
        QPieSlice *slice = series->slices().at(1);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (batterieCount != 0) {
        QPieSlice *slice = series->slices().at(2);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (activeCount != 0) {
        QPieSlice *slice = series->slices().at(3);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }

    // Create a chart and add the series to it
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Machines: Total = " + QString::number(totalCount));

    // Create a chart view to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1300, 800);
    chartView->showMaximized();
}


void MainWindow::on_pb_imp_clicked()
{
    m.imprimerTableau(ui->tab_aff);
}

void MainWindow::on_toggleThemeButton_clicked()
{
    static bool isDarkMode = false;  // Track the current theme state

    if (isDarkMode) {
        // Switch to light mode
        QApplication::setPalette(lightPalette);
        isDarkMode = false;
    } else {
        // Switch to dark mode
        QApplication::setPalette(darkPalette);
        isDarkMode = true;
    }
}

