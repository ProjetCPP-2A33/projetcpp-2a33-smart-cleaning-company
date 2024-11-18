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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label_3;
    QLineEdit *le_etatM;
    QLineEdit *le_responsableM;
    QLineEdit *le_emplacementM;
    QLineEdit *le_descriptionM;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *le_id_M;
    QLabel *label_8;
    QPushButton *pb_ajouter;
    QWidget *tab_2;
    QTableView *tab_etudiant;
    QWidget *tab_3;
    QLabel *label_10;
    QLineEdit *le_id_sup;
    QPushButton *pb_supprimer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(130, 10, 441, 471));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 10, 451, 441));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 180, 81, 16));
        le_etatM = new QLineEdit(groupBox);
        le_etatM->setObjectName("le_etatM");
        le_etatM->setGeometry(QRect(140, 70, 113, 20));
        le_responsableM = new QLineEdit(groupBox);
        le_responsableM->setObjectName("le_responsableM");
        le_responsableM->setGeometry(QRect(140, 120, 113, 20));
        le_emplacementM = new QLineEdit(groupBox);
        le_emplacementM->setObjectName("le_emplacementM");
        le_emplacementM->setGeometry(QRect(140, 220, 113, 20));
        le_descriptionM = new QLineEdit(groupBox);
        le_descriptionM->setObjectName("le_descriptionM");
        le_descriptionM->setGeometry(QRect(140, 180, 113, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 91, 16));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 130, 101, 16));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 80, 47, 13));
        le_id_M = new QLineEdit(groupBox);
        le_id_M->setObjectName("le_id_M");
        le_id_M->setGeometry(QRect(140, 30, 113, 20));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 30, 91, 16));
        pb_ajouter = new QPushButton(groupBox);
        pb_ajouter->setObjectName("pb_ajouter");
        pb_ajouter->setGeometry(QRect(110, 290, 75, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tab_etudiant = new QTableView(tab_2);
        tab_etudiant->setObjectName("tab_etudiant");
        tab_etudiant->setGeometry(QRect(60, 30, 321, 331));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_10 = new QLabel(tab_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(30, 60, 101, 16));
        le_id_sup = new QLineEdit(tab_3);
        le_id_sup->setObjectName("le_id_sup");
        le_id_sup->setGeometry(QRect(150, 60, 141, 20));
        pb_supprimer = new QPushButton(tab_3);
        pb_supprimer->setObjectName("pb_supprimer");
        pb_supprimer->setGeometry(QRect(120, 160, 121, 23));
        tabWidget->addTab(tab_3, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Ajouter machine", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "DescriptionM", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "EmplacementM", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "ResponsableM", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "EtatM", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Id_M", nullptr));
        pb_ajouter->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Ajouter un Fournisseur", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Afficher la liste des  Fournisseurs", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "ID_Machine", nullptr));
        pb_supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Supprimer un Fournisseur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
