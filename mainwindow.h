#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "arduin.h"
#include "machine.h"
#include "ui_mainwindow.h"

#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>

#include <QSerialPort>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();
    void afficherMachines();  // New function to refresh the table view
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    void on_pb_pdf_clicked();
    void on_pb_tri_clicked();
    void on_pb_search_clicked();
    void on_pb_stat_clicked();
    void on_pb_imp_clicked();
    void on_toggleThemeButton_clicked();
    //////////


    void openSerialPort();               // New function to open serial port for Arduino
    void readSerialData();               // New function to read data from Arduino via serial
         // Function triggered by RFID check (button or action)

public slots:
    bool checkIfRFIDExists(const QString &rfidID); // Function to check if RFID exists in the DB

private:
    Ui::MainWindow *ui;
    Machine m;

    QPalette darkPalette;
    QPalette lightPalette;

    QSqlDatabase db;         // Database connection for Oracle
    QSerialPort *serial;     // Declare a QSerialPort member to handle serial communication
};

#endif // MAINWINDOW_H
