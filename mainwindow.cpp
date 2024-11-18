#include "mainwindow.h"
#include "qsqlquery.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlQuery>

#include <QtWidgets/QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtSql/QSqlQueryModel>
#include <QtCore/QDebug>

#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    afficherMachines();  // Display existing machines when the app starts

    // Connect the Tri par ID button to the sorting function
    connect(ui->pb_tri, &QPushButton::clicked, this, &MainWindow::on_pb_tri_clicked);
    connect(ui->pb_search, &QPushButton::clicked, this, &MainWindow::on_pb_search_clicked);
    connect(ui->pb_stat, &QPushButton::clicked, this, &MainWindow::on_pb_stat_clicked);

    darkPalette.setColor(QPalette::Window, QColor(30, 30, 30));            // Dark background
    darkPalette.setColor(QPalette::WindowText, Qt::black);                // Text color: white
    darkPalette.setColor(QPalette::Base, QColor(45, 45, 45));             // Base color (input fields, etc.)
    darkPalette.setColor(QPalette::AlternateBase, QColor(60, 60, 60));    // Alternate base for selection or item backgrounds
    darkPalette.setColor(QPalette::ToolTipBase, QColor(50, 50, 50));      // Tooltip background
    darkPalette.setColor(QPalette::ToolTipText, Qt::black);               // Tooltip text color
    darkPalette.setColor(QPalette::Text, Qt::green);                      // General text color
    darkPalette.setColor(QPalette::Button, QColor(50, 50, 50));           // Button background color
    darkPalette.setColor(QPalette::ButtonText, Qt::black);                // Button text color
    darkPalette.setColor(QPalette::Highlight, QColor(0, 128, 255));       // Highlight color (e.g., selected items)
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);           // Highlighted text color
    darkPalette.setColor(QPalette::Text, QColor(255, 255, 255));



    // Light Mode Palette Setup
    lightPalette.setColor(QPalette::Window, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::AlternateBase, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ToolTipBase, Qt::white);
    lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(200, 200, 200));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);


    // Initially set dark theme
    QApplication::setPalette(darkPalette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::afficherMachines() {
    Machine machine;
    QSqlQueryModel *model = machine.afficher();
    ui->tab_aff->setModel(model);  // Set the model to display machines in tab_aff
}

void MainWindow::on_pb_ajouter_clicked() {
    int id_M = ui->le_id_M->text().toInt();
    QString etatM = ui->le_etatM->text();
    int responsableM = ui->le_responsableM->text().toInt();  // Convert this field to int
    QString descriptionM = ui->le_descriptionM->text();
    QString emplacementM = ui->le_emplacementM->text();

    // Pass `responsableM` as an int to the constructor
    Machine m(id_M, etatM, responsableM, descriptionM, emplacementM);
    bool test = m.ajouter();

    if (test) {
        QMessageBox::information(this, "Succès", "Machine ajoutée avec succès.");
        afficherMachines();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la machine.");
    }
}

void MainWindow::on_pb_supprimer_clicked() {
    int id_M = ui->le_id_sup->text().toInt();  // Get the machine ID to delete

    // Step 1: Check if the ID exists in the database
    QSqlQuery query;
    query.prepare("SELECT * FROM machine WHERE id_M = :id_M");
    query.bindValue(":id_M", id_M);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'ID.");
        return;
    }

    // If the ID doesn't exist in the database
    if (!query.next()) {
        QMessageBox::warning(this, "ID Introuvable", "L'ID n'existe pas dans la base de données.");
        return;
    }

    // Step 2: ID exists, now delete it
    Machine m;
    bool test = m.supprimer(id_M);  // Call the supprimer method to delete the machine

    // Step 3: If delete was successful, refresh the table and show a success message
    if (test) {
        afficherMachines();  // Refresh the display after deleting the machine
        QMessageBox::information(this, "Succès", "Machine supprimée avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression de la machine.");
    }
}

void MainWindow::on_pb_modifier_clicked() {
    int id_M = ui->le_id_mod->text().toInt();  // Get the machine ID to modify
    QString etatM = ui->le_etatMod->text();    // Get the state of the machine
    int responsableM = ui->le_responsableMod->text().toInt();  // Convert to int for responsible person ID
    QString descriptionM = ui->le_descriptionMod->text();  // Get the description of the machine
    QString emplacementM = ui->le_emplacementMod->text();  // Get the location of the machine

    // Step 1: Check if the ID exists in the database
    QSqlQuery query;
    query.prepare("SELECT * FROM machine WHERE id_M = :id_M");
    query.bindValue(":id_M", id_M);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'ID.");
        return;
    }

    // If the ID doesn't exist in the database
    if (!query.next()) {
        QMessageBox::warning(this, "ID Introuvable", "L'ID n'existe pas dans la base de données.");
        return;
    }

    // Step 2: ID exists, now update the machine details
    Machine m(id_M, etatM, responsableM, descriptionM, emplacementM);
    bool test = m.modifier(id_M);  // Call the modifier method to update the machine details

    // Step 3: If update was successful, refresh the table and show a success message
    if (test) {
        afficherMachines();  // Refresh the display after modifying the machine
        QMessageBox::information(this, "Succès", "Machine modifiée avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la machine.");
    }
}

void MainWindow::on_pb_pdf_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

    // Check if the user entered a filename
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "No file selected", "Please select a file to save the PDF.");
        return;
    }

    // Ensure the file has a .pdf extension
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    // Create a QPrinter object for PDF output
    QPrinter printer(QPrinter::PrinterMode::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    // Prepare a text document for the PDF content
    QTextDocument doc;

    // Start building the HTML content for the PDF
    QString htmlContent = "<h1>Machine Report</h1><table border='1' cellpadding='5'><tr>"
                          "<th>ID</th><th>Etat</th><th>Responsable</th><th>Description</th><th>Emplacement</th></tr>";

    // Access the model of the QTableView
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tab_aff->model());

    if (!model) {
        QMessageBox::warning(this, "Error", "Unable to access the data model.");
        return;
    }

    // Loop through the rows of the model and extract the data
    int rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // Extract data from each column in the row
        QString id_M = model->data(model->index(row, 0)).toString();  // Column 0 (ID)
        QString etatM = model->data(model->index(row, 1)).toString();  // Column 1 (Etat)
        QString responsableM = model->data(model->index(row, 2)).toString();  // Column 2 (Responsable)
        QString descriptionM = model->data(model->index(row, 3)).toString();  // Column 3 (Description)
        QString emplacementM = model->data(model->index(row, 4)).toString();  // Column 4 (Emplacement)

        // Add the row data to the HTML table
        htmlContent += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>")
                           .arg(id_M)
                           .arg(etatM)
                           .arg(descriptionM)
                           .arg(responsableM)
                           .arg(emplacementM);
    }

    // Close the table tag
    htmlContent += "</table>";

    // Set the HTML content to the QTextDocument
    doc.setHtml(htmlContent);

    // Render the document to the printer (PDF)
    doc.print(&printer);

    // Show a message box confirming PDF creation
    QMessageBox::information(this, "PDF Saved", "The PDF has been saved to " + fileName);
}

void MainWindow::on_pb_tri_clicked() {
    // Create a query to select all machines sorted by ID
    QSqlQuery query;
    query.prepare("SELECT * FROM machine ORDER BY id_M ASC");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec du tri des machines par ID.");
        return;
    }

    // Create a model to display the sorted data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Set the sorted model to the table view
    ui->tab_aff->setModel(model);
}

void MainWindow::on_pb_search_clicked() {
    QString searchTerm = ui->le_search->text();  // Get the search input from the user

    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Empty Input", "Please enter an ID to search.");
        return;
    }

    // Query to search for machine by ID
    QSqlQuery query;
    query.prepare("SELECT * FROM machine WHERE id_M = :id_M");
    query.bindValue(":id_M", searchTerm);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to fetch data from the database.");
        return;
    }

    // Check if results were found
    if (query.next()) {
        // Create a model to display the search result
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tab_aff->setModel(model);  // Set the model to the table view
    } else {
        QMessageBox::information(this, "No Results", "No machine found with the provided ID.");
    }
}

/*void MainWindow::on_pb_stat_clicked() {
    // Query to get the total number of machines in the database
    QSqlQuery totalQuery;
    totalQuery.prepare("SELECT COUNT(*) FROM machine");

    if (!totalQuery.exec()) {
        QMessageBox::critical(this, "Error", "Unable to fetch total machine count.");
        return;
    }

    totalQuery.next();  // Move to the first (and only) row
    int totalMachines = totalQuery.value(0).toInt();

    // Query to get the number of machines in a specific state (e.g., "Operational")
    QString state = "en panne";  // You can make this dynamic based on user input
    QSqlQuery stateQuery;
    stateQuery.prepare("SELECT COUNT(*) FROM machine WHERE etatM = :state");
    stateQuery.bindValue(":state", state);

    if (!stateQuery.exec()) {
        QMessageBox::critical(this, "Error", "Unable to fetch machine count by state.");
        return;
    }

    stateQuery.next();  // Move to the first (and only) row
    int machinesInState = stateQuery.value(0).toInt();

    // Display the stats in a QMessageBox
    QString message = QString("Total Machines: %1\nMachines in state '%2': %3")
                          .arg(totalMachines)
                          .arg(state)
                          .arg(machinesInState);

    QMessageBox::information(this, "Machine Statistics", message);
}*/


void MainWindow::on_pb_stat_clicked()
{
    // Create a new model for executing SQL queries
    QSqlQueryModel *model = new QSqlQueryModel();

    // Query for different statuses (you can adjust these based on your actual database schema)
    model->setQuery("SELECT * FROM machine WHERE etatM = 'en panne'");
    float panneCount = model->rowCount();  // Count how many machines are 'en panne'

    model->setQuery("SELECT * FROM machine WHERE etatM = 'maintenance'");
    float maintenanceCount = model->rowCount();  // Count how many machines are in 'maintenance'

    model->setQuery("SELECT * FROM machine WHERE etatM = 'batterie faible'");
    float batterieCount = model->rowCount();  // Count how many machines have 'batterie faible'

    model->setQuery("SELECT * FROM machine WHERE etatM = 'active'");
    float activeCount = model->rowCount();  // Count how many machines are 'active'

    // Calculate the total number of machines
    float totalCount = panneCount + maintenanceCount + batterieCount + activeCount;

    // Create strings to display as labels with percentages
    QString panneLabel = QString("en panne: %1%").arg(QString::number((panneCount * 100) / totalCount, 'f', 2));
    QString maintenanceLabel = QString("maintenance: %1%").arg(QString::number((maintenanceCount * 100) / totalCount, 'f', 2));
    QString batterieLabel = QString("batterie Faible: %1%").arg(QString::number((batterieCount * 100) / totalCount, 'f', 2));
    QString activeLabel = QString("active: %1%").arg(QString::number((activeCount * 100) / totalCount, 'f', 2));

    // Create a pie chart series and add the data
    QPieSeries *series = new QPieSeries();
    series->append(panneLabel, panneCount);
    series->append(maintenanceLabel, maintenanceCount);
    series->append(batterieLabel, batterieCount);
    series->append(activeLabel, activeCount);

    // Make slices clickable and show labels
    if (panneCount != 0) {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (maintenanceCount != 0) {
        QPieSlice *slice = series->slices().at(1);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (batterieCount != 0) {
        QPieSlice *slice = series->slices().at(2);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (activeCount != 0) {
        QPieSlice *slice = series->slices().at(3);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }

    // Create a chart and add the series to it
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Machines: Total = " + QString::number(totalCount));

    // Create a chart view to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1300, 800);
    chartView->showMaximized();
}


void MainWindow::on_pb_imp_clicked()
{
    m.imprimerTableau(ui->tab_aff);
}

void MainWindow::on_toggleThemeButton_clicked()
{
    static bool isDarkMode = false;  // Track the current theme state

    if (isDarkMode) {
        // Switch to light mode
        QApplication::setPalette(lightPalette);
        isDarkMode = false;
    } else {
        // Switch to dark mode
        QApplication::setPalette(darkPalette);
        isDarkMode = true;
    }
}
