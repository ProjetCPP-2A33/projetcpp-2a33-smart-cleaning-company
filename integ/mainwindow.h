#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSqlQuery>
#include <QPen>
#include <QLayoutItem>
#include <QMessageBox>
#include <QNetworkReply>
#include "produit.h"
#include "arduino.h"
#include <QSerialPort>
#include "client.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_stat_clicked();


    void on_bouttonconfirmermodification_clicked();


    void on_bouttonajouterproduit_clicked();
    void on_bouttonpagestatistique_clicked();

    void on_bouttonpageafficherproduit_clicked();

    void on_bouttonpagemodifierproduit_clicked();

    void on_bouttonpagesupprimer_clicked();

    void on_bouttonpageajouter_clicked();

    void on_bouttonsupprimerproduit_clicked();

    void on_bouttonrecherchetableau_clicked();

    void on_triparnom_clicked();

    void on_bouttonidproduitmodif_clicked();
    void on_pushButton_pdf_clicked();

    void on_validationsms_clicked();
    void envoyerSMS(const QString &destinataire, const QString &message);
    void onSmsReplyFinished(QNetworkReply *reply);
    void historique(const QString &typeevenement, const QString &nomproduit, const QString &extrainfo);
    void loadHistoriqueFile();
    void on_bouttonpagehistorique_clicked();
     void on_bouttonpagearduino_clicked();
    void on_pushButtonverifer_clicked();
     void on_pushButtonkhedmakol_clicked();
     void on_pushButtonexit_clicked();
    void verifyEmployeID();
      void on_bclient_clicked();
    void processEmployeID(const QString &employeID);
    QString getEmployeeCardCodeFromDatabase(const QString &employeID);
    QString getemployeposteFromDatabase(const QString &employeeCardCode);
    QString getemployeIDFromDatabase(const QString &employeeCardCode);
    //salim
     void ajouterClient();
      void afficher();
      void supprimerClient();
      void modifierClient();
       bool verif1(int id,int numTel,QString mail,int nbrAff);
       void tri();
       void recherche();
       bool verif(int id,int numTel,QString mail,int nbrAff);
      void page1Wid();
      void page2Wid();
      void expPDF();
      void sendEmail();
       void page4Wid();
      void stat();
      void PtMrc(); //to fix
       void page3Wid();
        void page1Main();



private:
    Ui::MainWindow *ui;
     QSerialPort *serialPort;
     Arduino arduino;
      void setupConnections();
     Client client;

};
#endif // MAINWINDOW_H
