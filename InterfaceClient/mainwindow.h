#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <client.h>

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
    void page1Wid();
    void page2Wid();

private:
    Ui::MainWindow *ui;
    Client client;

    void setupConnections();
};
#endif // MAINWINDOW_H
