/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
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
    QWidget *widget_3;
    QWidget *widget;
    QPushButton *rech;
    QLineEdit *recherche;
    QStackedWidget *stack;
    QWidget *page;
    QTableView *tab;
    QPushButton *refresh;
    QWidget *page_2;
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
    QPushButton *pushButton_5;
    QWidget *icon_only;
    QPushButton *switch1;
    QPushButton *switch2;
    QPushButton *switch3;
    QPushButton *quitter;
    QPushButton *tri;
    QPushButton *menu;
    QPushButton *stat;
    QPushButton *profil;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(926, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(190, 0, 711, 431));
        widget = new QWidget(widget_3);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, -1, 711, 91));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 170);"));
        rech = new QPushButton(widget);
        rech->setObjectName("rech");
        rech->setGeometry(QRect(400, 40, 81, 18));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../Icons for qt/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        rech->setIcon(icon);
        recherche = new QLineEdit(widget);
        recherche->setObjectName("recherche");
        recherche->setGeometry(QRect(220, 40, 171, 20));
        stack = new QStackedWidget(widget_3);
        stack->setObjectName("stack");
        stack->setGeometry(QRect(20, 110, 591, 281));
        page = new QWidget();
        page->setObjectName("page");
        tab = new QTableView(page);
        tab->setObjectName("tab");
        tab->setGeometry(QRect(50, 40, 521, 221));
        refresh = new QPushButton(page);
        refresh->setObjectName("refresh");
        refresh->setGeometry(QRect(20, 10, 80, 18));
        stack->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        ajout = new QPushButton(page_2);
        ajout->setObjectName("ajout");
        ajout->setGeometry(QRect(300, 80, 80, 18));
        mod = new QPushButton(page_2);
        mod->setObjectName("mod");
        mod->setGeometry(QRect(300, 110, 80, 18));
        supp = new QPushButton(page_2);
        supp->setObjectName("supp");
        supp->setGeometry(QRect(300, 140, 80, 18));
        idc = new QLineEdit(page_2);
        idc->setObjectName("idc");
        idc->setGeometry(QRect(60, 20, 113, 20));
        nom = new QLineEdit(page_2);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(60, 60, 113, 20));
        prenom = new QLineEdit(page_2);
        prenom->setObjectName("prenom");
        prenom->setGeometry(QRect(60, 100, 113, 20));
        numtel = new QLineEdit(page_2);
        numtel->setObjectName("numtel");
        numtel->setGeometry(QRect(60, 140, 113, 20));
        mail = new QLineEdit(page_2);
        mail->setObjectName("mail");
        mail->setGeometry(QRect(60, 180, 113, 20));
        typeaff = new QLineEdit(page_2);
        typeaff->setObjectName("typeaff");
        typeaff->setGeometry(QRect(60, 220, 113, 20));
        nbraff = new QLineEdit(page_2);
        nbraff->setObjectName("nbraff");
        nbraff->setGeometry(QRect(60, 260, 113, 20));
        label_7 = new QLabel(page_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 60, 37, 12));
        label = new QLabel(page_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 37, 12));
        label_2 = new QLabel(page_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 100, 37, 12));
        label_3 = new QLabel(page_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 140, 37, 12));
        label_4 = new QLabel(page_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 180, 37, 21));
        label_5 = new QLabel(page_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 220, 51, 16));
        label_6 = new QLabel(page_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 260, 41, 20));
        retour = new QPushButton(page_2);
        retour->setObjectName("retour");
        retour->setGeometry(QRect(470, 240, 80, 18));
        stack->addWidget(page_2);
        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(620, 90, 81, 71));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../logo app/logo_sans_slogan-removebg-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon1);
        pushButton_5->setIconSize(QSize(70, 70));
        icon_only = new QWidget(centralwidget);
        icon_only->setObjectName("icon_only");
        icon_only->setGeometry(QRect(60, 0, 131, 431));
        icon_only->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 170);"));
        switch1 = new QPushButton(icon_only);
        switch1->setObjectName("switch1");
        switch1->setGeometry(QRect(20, 140, 91, 18));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../Icons for qt/user-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        switch1->setIcon(icon2);
        switch2 = new QPushButton(icon_only);
        switch2->setObjectName("switch2");
        switch2->setGeometry(QRect(20, 170, 91, 18));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../../Icons for qt/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        switch2->setIcon(icon3);
        switch3 = new QPushButton(icon_only);
        switch3->setObjectName("switch3");
        switch3->setGeometry(QRect(20, 200, 91, 18));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../../Icons for qt/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        switch3->setIcon(icon4);
        quitter = new QPushButton(icon_only);
        quitter->setObjectName("quitter");
        quitter->setGeometry(QRect(20, 360, 91, 18));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../../Icons for qt/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        quitter->setIcon(icon5);
        tri = new QPushButton(icon_only);
        tri->setObjectName("tri");
        tri->setGeometry(QRect(20, 230, 91, 18));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../../Icons for qt/layers.png"), QSize(), QIcon::Normal, QIcon::Off);
        tri->setIcon(icon6);
        menu = new QPushButton(icon_only);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(40, 40, 51, 18));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../../../Icons for qt/align-justify.png"), QSize(), QIcon::Normal, QIcon::Off);
        menu->setIcon(icon7);
        stat = new QPushButton(icon_only);
        stat->setObjectName("stat");
        stat->setGeometry(QRect(20, 260, 91, 18));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("../../../Icons for qt/chart-histogram.png"), QSize(), QIcon::Normal, QIcon::Off);
        stat->setIcon(icon8);
        profil = new QPushButton(icon_only);
        profil->setObjectName("profil");
        profil->setGeometry(QRect(20, 330, 91, 18));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("../../../Icons for qt/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        profil->setIcon(icon9);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 926, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        rech->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        recherche->setText(QString());
        refresh->setText(QCoreApplication::translate("MainWindow", "Actualiser", nullptr));
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
        pushButton_5->setText(QString());
        switch1->setText(QCoreApplication::translate("MainWindow", "Ajouter Client", nullptr));
        switch2->setText(QCoreApplication::translate("MainWindow", "Supprimer Client", nullptr));
        switch3->setText(QCoreApplication::translate("MainWindow", "Modifier Client", nullptr));
        quitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        tri->setText(QCoreApplication::translate("MainWindow", "Tri par nbr Affaire", nullptr));
        menu->setText(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        stat->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        profil->setText(QCoreApplication::translate("MainWindow", "Profil", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
