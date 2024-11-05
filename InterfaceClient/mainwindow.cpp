#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->ajout, &QPushButton::clicked, this, &MainWindow::onAddClient);
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::onShowClients);
}

void MainWindow::onAddClient()
{
    if(client.ajouter())
    {
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

void MainWindow::onShowClients()
{
    QSqlQueryModel *model = client.afficher();

    client.afficherTableWidget(ui->qtab, model);

}
