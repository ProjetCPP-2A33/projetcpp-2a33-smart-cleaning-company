#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include "ArduinoClient.h"

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
    void ajouterClient();
    void supprimerClient();
    bool verif(int id,int numTel,QString mail,int nbrAff);
    void modifierClient();
    bool verif1(int id,int numTel,QString mail,int nbrAff);
    void afficher();
    void tri();
    void recherche();
    void expPDF();
    void sendEmail();
    void stat();
    void PtMrc(); //to fix
    void verifId();

    void page1Main();
    void page2Main();
    void page3Main();

    void page1Wid();
    void page2Wid();
    void page3Wid();
    void page4Wid();
    void page5Wid();

private:
    Ui::MainWindow *ui;
    Client client;
    SerialCommunication *arduino;

    void setupConnections();
};
#endif // CLIENTWINDOW_H
