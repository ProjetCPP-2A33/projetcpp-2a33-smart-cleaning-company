#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->tab->setModel(client.afficher());

    setupConnections();
}

void MainWindow::page1Wid()
{
    ui->stack->setCurrentWidget(ui->page);
}

void MainWindow::page2Wid()
{
    ui->stack->setCurrentWidget(ui->page_2);
}

void MainWindow::page3Wid()
{
    ui->stack->setCurrentWidget(ui->page_3);
}

void MainWindow::page4Wid()
{
    ui->stack->setCurrentWidget(ui->page_4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->switch1, &QPushButton::clicked, this, &MainWindow::page2Wid);
    connect(ui->retour, &QPushButton::clicked, this, &MainWindow::page1Wid);
    connect(ui->retour1, &QPushButton::clicked, this, &MainWindow::page1Wid);
    connect(ui->retour2, &QPushButton::clicked, this, &MainWindow::page1Wid);
    connect(ui->bstat, &QPushButton::clicked, this, &MainWindow::page3Wid);
    connect(ui->mailing, &QPushButton::clicked, this, &MainWindow::page4Wid);

    connect(ui->ajout, &QPushButton::clicked, this, &MainWindow::ajouterClient);
    connect(ui->supp, &QPushButton::clicked, this, &MainWindow::supprimerClient);
    connect(ui->mod, &QPushButton::clicked, this, &MainWindow::modifierClient);
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::afficher);
    connect(ui->tri, &QPushButton::clicked, this, &MainWindow::tri);
    connect(ui->rech, &QPushButton::clicked, this, &MainWindow::recherche);
    connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::expPDF);
    connect(ui->affgraph, &QPushButton::clicked, this, &MainWindow::stat);
    connect(ui->calcred, &QPushButton::clicked, this, &MainWindow::PtMrc);
    connect(ui->envoyer, &QPushButton::clicked, this, &MainWindow::sendEmail);

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

void MainWindow::afficher()
{
    ui->tab->setModel(client.afficher());
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

