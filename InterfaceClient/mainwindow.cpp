#include "mainwindow.h"
#include "ui_mainwindow.h"
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->switch1, &QPushButton::clicked, this, &MainWindow::page2Wid);
    connect(ui->switch2, &QPushButton::clicked, this, &MainWindow::page2Wid);
    connect(ui->switch3, &QPushButton::clicked, this, &MainWindow::page2Wid);
    connect(ui->retour, &QPushButton::clicked, this, &MainWindow::page1Wid);

    connect(ui->ajout, &QPushButton::clicked, this, &MainWindow::ajouterClient);
    connect(ui->supp, &QPushButton::clicked, this, &MainWindow::supprimerClient);
    connect(ui->mod, &QPushButton::clicked, this, &MainWindow::modifierClient);
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::afficher);
    connect(ui->tri, &QPushButton::clicked, this, &MainWindow::tri);
    connect(ui->rech, &QPushButton::clicked, this, &MainWindow::recherche);
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
    int id=ui->recherche->text().toInt();

    QSqlQueryModel *model=client.recherche(id);

    if(model)
    {
        ui->tab->setModel(model);

        QMessageBox::information(nullptr, QObject::tr("Succée!"),
                                 QObject::tr("Recherche Effectuée. \n"
                                             "Clickez ici pour sortir."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                              QObject::tr("Recherche non effectuée. \n"
                                          "Clickez ici pour sortir."), QMessageBox::Cancel);
    }
}
