#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "machine.h"

#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
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

private:
    Ui::MainWindow *ui;
    Machine m;

    QPalette darkPalette;
    QPalette lightPalette;
};
#endif // MAINWINDOW_H
