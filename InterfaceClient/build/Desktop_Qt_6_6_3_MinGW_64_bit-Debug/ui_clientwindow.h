/********************************************************************************
** Form generated from reading UI file 'clientwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWINDOW_H
#define UI_CLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *mainstack;
    QWidget *menu;
    QPushButton *clientB;
    QPushButton *produitsB;
    QPushButton *machinesB;
    QWidget *client;
    QWidget *widget_3;
    QWidget *widget;
    QPushButton *rech;
    QLineEdit *recherche;
    QComboBox *combo;
    QStackedWidget *stack;
    QWidget *afficher;
    QTableView *tab;
    QPushButton *refresh;
    QPushButton *pdf;
    QLineEdit *idred;
    QLabel *label_8;
    QLabel *reduction;
    QPushButton *calcred;
    QWidget *gerer;
    QPushButton *ajout;
    QPushButton *mod;
    QPushButton *supp;
    QLineEdit *idc;
    QLineEdit *nom;
    QLineEdit *prenom;
    QLineEdit *numtel;
    QLineEdit *mail;
    QLineEdit *typeaff;
    QLineEdit *nbraff;
    QLabel *label_7;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *retour;
    QWidget *stat;
    QGraphicsView *graph;
    QPushButton *affgraph;
    QPushButton *retour1;
    QWidget *mail1;
    QLabel *label_9;
    QLineEdit *mail_3;
    QPushButton *envoyer;
    QPushButton *retour2;
    QWidget *temp;
    QLineEdit *temp1;
    QPushButton *temprech;
    QPushButton *pushButton_5;
    QWidget *icon_only;
    QPushButton *switch1;
    QPushButton *quitter;
    QPushButton *tri;
    QPushButton *menu1;
    QPushButton *bstat;
    QPushButton *profil;
    QPushButton *mailing;
    QPushButton *tempb;
    QWidget *produits;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(926, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainstack = new QStackedWidget(centralwidget);
        mainstack->setObjectName("mainstack");
        mainstack->setGeometry(QRect(20, 20, 881, 501));
        menu = new QWidget();
        menu->setObjectName("menu");
        clientB = new QPushButton(menu);
        clientB->setObjectName("clientB");
        clientB->setGeometry(QRect(140, 180, 141, 61));
        produitsB = new QPushButton(menu);
        produitsB->setObjectName("produitsB");
        produitsB->setGeometry(QRect(360, 180, 141, 61));
        machinesB = new QPushButton(menu);
        machinesB->setObjectName("machinesB");
        machinesB->setGeometry(QRect(580, 180, 141, 61));
        mainstack->addWidget(menu);
        client = new QWidget();
        client->setObjectName("client");
        widget_3 = new QWidget(client);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(140, 30, 711, 431));
        widget = new QWidget(widget_3);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, -1, 711, 91));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 170);"));
        rech = new QPushButton(widget);
        rech->setObjectName("rech");
        rech->setGeometry(QRect(420, 40, 81, 18));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../Icons for qt/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        rech->setIcon(icon);
        recherche = new QLineEdit(widget);
        recherche->setObjectName("recherche");
        recherche->setGeometry(QRect(230, 40, 171, 20));
        combo = new QComboBox(widget);
        combo->addItem(QString());
        combo->addItem(QString());
        combo->addItem(QString());
        combo->setObjectName("combo");
        combo->setGeometry(QRect(130, 40, 81, 22));
        stack = new QStackedWidget(widget_3);
        stack->setObjectName("stack");
        stack->setGeometry(QRect(20, 110, 591, 291));
        afficher = new QWidget();
        afficher->setObjectName("afficher");
        tab = new QTableView(afficher);
        tab->setObjectName("tab");
        tab->setGeometry(QRect(50, 40, 521, 181));
        refresh = new QPushButton(afficher);
        refresh->setObjectName("refresh");
        refresh->setGeometry(QRect(20, 10, 80, 18));
        pdf = new QPushButton(afficher);
        pdf->setObjectName("pdf");
        pdf->setGeometry(QRect(140, 10, 80, 18));
        idred = new QLineEdit(afficher);
        idred->setObjectName("idred");
        idred->setGeometry(QRect(140, 240, 113, 20));
        label_8 = new QLabel(afficher);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(120, 240, 16, 16));
        reduction = new QLabel(afficher);
        reduction->setObjectName("reduction");
        reduction->setGeometry(QRect(310, 240, 141, 21));
        calcred = new QPushButton(afficher);
        calcred->setObjectName("calcred");
        calcred->setGeometry(QRect(240, 270, 80, 18));
        stack->addWidget(afficher);
        gerer = new QWidget();
        gerer->setObjectName("gerer");
        ajout = new QPushButton(gerer);
        ajout->setObjectName("ajout");
        ajout->setGeometry(QRect(300, 80, 80, 18));
        mod = new QPushButton(gerer);
        mod->setObjectName("mod");
        mod->setGeometry(QRect(300, 110, 80, 18));
        supp = new QPushButton(gerer);
        supp->setObjectName("supp");
        supp->setGeometry(QRect(300, 140, 80, 18));
        idc = new QLineEdit(gerer);
        idc->setObjectName("idc");
        idc->setGeometry(QRect(60, 20, 113, 20));
        nom = new QLineEdit(gerer);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(60, 60, 113, 20));
        prenom = new QLineEdit(gerer);
        prenom->setObjectName("prenom");
        prenom->setGeometry(QRect(60, 100, 113, 20));
        numtel = new QLineEdit(gerer);
        numtel->setObjectName("numtel");
        numtel->setGeometry(QRect(60, 140, 113, 20));
        mail = new QLineEdit(gerer);
        mail->setObjectName("mail");
        mail->setGeometry(QRect(60, 180, 113, 20));
        typeaff = new QLineEdit(gerer);
        typeaff->setObjectName("typeaff");
        typeaff->setGeometry(QRect(60, 220, 113, 20));
        nbraff = new QLineEdit(gerer);
        nbraff->setObjectName("nbraff");
        nbraff->setGeometry(QRect(60, 260, 113, 20));
        label_7 = new QLabel(gerer);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 60, 37, 12));
        label = new QLabel(gerer);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 37, 12));
        label_2 = new QLabel(gerer);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 100, 37, 12));
        label_3 = new QLabel(gerer);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 140, 37, 12));
        label_4 = new QLabel(gerer);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 180, 37, 21));
        label_5 = new QLabel(gerer);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 220, 51, 16));
        label_6 = new QLabel(gerer);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 260, 41, 20));
        retour = new QPushButton(gerer);
        retour->setObjectName("retour");
        retour->setGeometry(QRect(470, 240, 80, 18));
        stack->addWidget(gerer);
        stat = new QWidget();
        stat->setObjectName("stat");
        graph = new QGraphicsView(stat);
        graph->setObjectName("graph");
        graph->setGeometry(QRect(10, 10, 561, 241));
        affgraph = new QPushButton(stat);
        affgraph->setObjectName("affgraph");
        affgraph->setGeometry(QRect(510, 260, 80, 18));
        retour1 = new QPushButton(stat);
        retour1->setObjectName("retour1");
        retour1->setGeometry(QRect(420, 260, 80, 18));
        stack->addWidget(stat);
        mail1 = new QWidget();
        mail1->setObjectName("mail1");
        label_9 = new QLabel(mail1);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 30, 111, 21));
        mail_3 = new QLineEdit(mail1);
        mail_3->setObjectName("mail_3");
        mail_3->setGeometry(QRect(140, 30, 171, 20));
        envoyer = new QPushButton(mail1);
        envoyer->setObjectName("envoyer");
        envoyer->setGeometry(QRect(350, 30, 80, 18));
        retour2 = new QPushButton(mail1);
        retour2->setObjectName("retour2");
        retour2->setGeometry(QRect(480, 260, 80, 18));
        stack->addWidget(mail1);
        temp = new QWidget();
        temp->setObjectName("temp");
        temp1 = new QLineEdit(temp);
        temp1->setObjectName("temp1");
        temp1->setGeometry(QRect(100, 50, 171, 20));
        temprech = new QPushButton(temp);
        temprech->setObjectName("temprech");
        temprech->setGeometry(QRect(310, 50, 81, 18));
        temprech->setIcon(icon);
        stack->addWidget(temp);
        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(620, 90, 81, 71));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../logo app/logo_sans_slogan-removebg-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon1);
        pushButton_5->setIconSize(QSize(70, 70));
        icon_only = new QWidget(client);
        icon_only->setObjectName("icon_only");
        icon_only->setGeometry(QRect(10, 30, 131, 431));
        icon_only->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 170);"));
        switch1 = new QPushButton(icon_only);
        switch1->setObjectName("switch1");
        switch1->setGeometry(QRect(20, 140, 91, 18));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../Icons for qt/user-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        switch1->setIcon(icon2);
        quitter = new QPushButton(icon_only);
        quitter->setObjectName("quitter");
        quitter->setGeometry(QRect(20, 360, 91, 18));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../../Icons for qt/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        quitter->setIcon(icon3);
        tri = new QPushButton(icon_only);
        tri->setObjectName("tri");
        tri->setGeometry(QRect(20, 170, 91, 18));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../../Icons for qt/layers.png"), QSize(), QIcon::Normal, QIcon::Off);
        tri->setIcon(icon4);
        menu1 = new QPushButton(icon_only);
        menu1->setObjectName("menu1");
        menu1->setGeometry(QRect(40, 40, 51, 18));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../../Icons for qt/align-justify.png"), QSize(), QIcon::Normal, QIcon::Off);
        menu1->setIcon(icon5);
        bstat = new QPushButton(icon_only);
        bstat->setObjectName("bstat");
        bstat->setGeometry(QRect(20, 200, 91, 18));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../../Icons for qt/chart-histogram.png"), QSize(), QIcon::Normal, QIcon::Off);
        bstat->setIcon(icon6);
        profil = new QPushButton(icon_only);
        profil->setObjectName("profil");
        profil->setGeometry(QRect(20, 330, 91, 18));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../../../Icons for qt/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        profil->setIcon(icon7);
        mailing = new QPushButton(icon_only);
        mailing->setObjectName("mailing");
        mailing->setGeometry(QRect(20, 230, 91, 18));
        mailing->setIcon(icon6);
        tempb = new QPushButton(icon_only);
        tempb->setObjectName("tempb");
        tempb->setGeometry(QRect(20, 260, 91, 18));
        tempb->setIcon(icon6);
        mainstack->addWidget(client);
        produits = new QWidget();
        produits->setObjectName("produits");
        mainstack->addWidget(produits);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 926, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        mainstack->setCurrentIndex(1);
        stack->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        clientB->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        produitsB->setText(QCoreApplication::translate("MainWindow", "Produits", nullptr));
        machinesB->setText(QCoreApplication::translate("MainWindow", "Machines", nullptr));
        rech->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        recherche->setText(QString());
        combo->setItemText(0, QCoreApplication::translate("MainWindow", "Id", nullptr));
        combo->setItemText(1, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        combo->setItemText(2, QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));

        refresh->setText(QCoreApplication::translate("MainWindow", "Actualiser", nullptr));
        pdf->setText(QCoreApplication::translate("MainWindow", "PDF", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Id:", nullptr));
        reduction->setText(QString());
        calcred->setText(QCoreApplication::translate("MainWindow", "Calculer R\303\251d.", nullptr));
        ajout->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        mod->setText(QCoreApplication::translate("MainWindow", "Modier", nullptr));
        supp->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IdC", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "numTel", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Mail", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "type Affaire", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "nbr Affaire", nullptr));
        retour->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        affgraph->setText(QCoreApplication::translate("MainWindow", "Afficher stat", nullptr));
        retour1->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "E-Mail destinataire:", nullptr));
        envoyer->setText(QCoreApplication::translate("MainWindow", "Envoyer", nullptr));
        retour2->setText(QCoreApplication::translate("MainWindow", "Retour", nullptr));
        temp1->setText(QString());
        temprech->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        pushButton_5->setText(QString());
        switch1->setText(QCoreApplication::translate("MainWindow", "G\303\251rer Clients", nullptr));
        quitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        tri->setText(QCoreApplication::translate("MainWindow", "Tri par nbr Affaire", nullptr));
        menu1->setText(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        bstat->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        profil->setText(QCoreApplication::translate("MainWindow", "Profil", nullptr));
        mailing->setText(QCoreApplication::translate("MainWindow", "Mailing", nullptr));
        tempb->setText(QCoreApplication::translate("MainWindow", "Temp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
