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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget_3;
    QWidget *widget;
    QPushButton *rechexec;
    QLineEdit *recherche;
    QStackedWidget *stack;
    QWidget *page;
    QPushButton *refresh;
    QTableWidget *qtab;
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
        rechexec = new QPushButton(widget);
        rechexec->setObjectName("rechexec");
        rechexec->setGeometry(QRect(400, 40, 31, 18));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../Icons for qt/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        rechexec->setIcon(icon);
        recherche = new QLineEdit(widget);
        recherche->setObjectName("recherche");
        recherche->setGeometry(QRect(220, 40, 171, 20));
        stack = new QStackedWidget(widget_3);
        stack->setObjectName("stack");
        stack->setGeometry(QRect(20, 110, 591, 281));
        page = new QWidget();
        page->setObjectName("page");
        refresh = new QPushButton(page);
        refresh->setObjectName("refresh");
        refresh->setGeometry(QRect(10, 10, 31, 20));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../Icons for qt/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        refresh->setIcon(icon1);
        qtab = new QTableWidget(page);
        if (qtab->columnCount() < 7)
            qtab->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        qtab->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        qtab->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        qtab->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        qtab->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        qtab->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        qtab->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        qtab->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        if (qtab->rowCount() < 3)
            qtab->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        qtab->setItem(2, 0, __qtablewidgetitem7);
        qtab->setObjectName("qtab");
        qtab->setGeometry(QRect(40, 40, 541, 211));
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
        label_5->setGeometry(QRect(10, 220, 37, 12));
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../logo app/logo_sans_slogan-removebg-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon2);
        pushButton_5->setIconSize(QSize(70, 70));
        icon_only = new QWidget(centralwidget);
        icon_only->setObjectName("icon_only");
        icon_only->setGeometry(QRect(60, 0, 131, 431));
        icon_only->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 170);"));
        switch1 = new QPushButton(icon_only);
        switch1->setObjectName("switch1");
        switch1->setGeometry(QRect(20, 140, 91, 18));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../../Icons for qt/user-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        switch1->setIcon(icon3);
        switch2 = new QPushButton(icon_only);
        switch2->setObjectName("switch2");
        switch2->setGeometry(QRect(20, 170, 91, 18));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../../Icons for qt/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        switch2->setIcon(icon4);
        switch3 = new QPushButton(icon_only);
        switch3->setObjectName("switch3");
        switch3->setGeometry(QRect(20, 200, 91, 18));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../../Icons for qt/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        switch3->setIcon(icon5);
        quitter = new QPushButton(icon_only);
        quitter->setObjectName("quitter");
        quitter->setGeometry(QRect(20, 360, 91, 18));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../../Icons for qt/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        quitter->setIcon(icon6);
        tri = new QPushButton(icon_only);
        tri->setObjectName("tri");
        tri->setGeometry(QRect(20, 230, 91, 18));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../../../Icons for qt/layers.png"), QSize(), QIcon::Normal, QIcon::Off);
        tri->setIcon(icon7);
        menu = new QPushButton(icon_only);
        menu->setObjectName("menu");
        menu->setGeometry(QRect(40, 40, 51, 18));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("../../../Icons for qt/align-justify.png"), QSize(), QIcon::Normal, QIcon::Off);
        menu->setIcon(icon8);
        stat = new QPushButton(icon_only);
        stat->setObjectName("stat");
        stat->setGeometry(QRect(20, 260, 91, 18));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("../../../Icons for qt/chart-histogram.png"), QSize(), QIcon::Normal, QIcon::Off);
        stat->setIcon(icon9);
        profil = new QPushButton(icon_only);
        profil->setObjectName("profil");
        profil->setGeometry(QRect(20, 330, 91, 18));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("../../../Icons for qt/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        profil->setIcon(icon10);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 926, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stack->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        rechexec->setText(QString());
        recherche->setText(QCoreApplication::translate("MainWindow", "Recherche.....", nullptr));
        refresh->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = qtab->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "idC", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = qtab->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = qtab->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = qtab->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "numTel", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = qtab->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Mail", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = qtab->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "typeAffaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = qtab->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "nbrAffaire", nullptr));

        const bool __sortingEnabled = qtab->isSortingEnabled();
        qtab->setSortingEnabled(false);
        qtab->setSortingEnabled(__sortingEnabled);

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
