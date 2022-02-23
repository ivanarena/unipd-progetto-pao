#include "view.h"
#include "model.h"
#include "parser.h"
#include "jsonparser.h"
#include "controller.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QLineSeries>
#include <QGridLayout>
#include <QApplication>
#include <QStyle>
#include <QVXYModelMapper>
#include <QHeaderView>
#include <QTabWidget>
#include <QToolButton>
#include <QToolBar>
#include <QMenuBar>
#include <QList>
#include <QAbstractButton>
#include <QPushButton>
#include <QVPieModelMapper>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>
#include <QMenu>
#include <QComboBox>
#include <QKeySequence>
#include <iostream>
#include <QFileDialog>
#include <QInputDialog>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include "scene.h"
#include "chart.h"
#include "linechart.h"
#include "barchart.h"

using namespace std;

QChart * View::createPieChart(DataTableModel *model)
{
    QChart *pieChart = new QChart();
    QVPieModelMapper *pieMapper = new QVPieModelMapper();
    pieChart->setTitle("Pie chart");
    pieChart->setAnimationOptions(QChart::AllAnimations);
    QPieSeries *series = new QPieSeries(pieChart);

    pieMapper->setSeries(series);
    pieMapper->setModel(model); //TODO: capire come implementare il piechart con questo set di dati
    pieMapper->setLabelsColumn(0); // a quale colonna associare  label
    pieMapper->setValuesColumn(1); // a quale colonna associare valore
    pieMapper->setFirstRow(0); //da che riga del model inizio
    pieMapper->setRowCount(model->rowCount()); //una riga -> una slice

    pieChart->addSeries(series);
    series->setPieSize(5);
    series->setHoleSize(0.5);

    return pieChart;
}

void View::setToolBar()
{
    chartSelector->addItem("Line Chart");
    chartSelector->addItem("Bar Chart");

    //toolBar->setOrientation(Qt::Vertical);
    toolBar->addSeparator();
    toolBar->addAction(newTab);
    toolBar->addSeparator();
    toolBar->addAction(openModel);
    toolBar->addAction(saveModel);
    toolBar->addSeparator();
    toolBar->addAction(renameHeaders);
    toolBar->addSeparator();
    toolBar->addAction(insertRow);
    toolBar->addAction(removeRow);
    toolBar->addSeparator();
    toolBar->addAction(insertColumn);
    toolBar->addAction(removeColumn);
    toolBar->addSeparator();
    toolBar->addWidget(chartSelector);
    toolBar->addSeparator();

    toolBar->setIconSize(QSize(36, 36));
}

void View::setMenus()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newTab);
    fileMenu->addSeparator();
    fileMenu->addAction(openModel);
    fileMenu->addAction(saveModel);
    fileMenu->addSeparator();
    fileMenu->addAction(exitApp);

    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(renameHeaders);
    editMenu->addSeparator();
    editMenu->addAction(insertRow);
    editMenu->addAction(removeRow);
    editMenu->addSeparator();
    editMenu->addAction(insertColumn);
    editMenu->addAction(removeColumn);
    editMenu->addSeparator();
}

//============================== COSTRUTTORE ===========================================

// IMPORTANTISSIMO!!!!! IMPLEMENTARE UN VETTORE CHE SCORRE I MODELLI E GESTISCE I MODELLI DI OGNI TAB
View::View(QWidget *parent)
    : QWidget(parent), mainLayout(new QGridLayout), tabView(new QTabWidget), toolBar(new QToolBar),
      menuBar(new QMenuBar), fileMenu(new QMenu), editMenu(new QMenu),
      newTab(new QAction(QIcon(":/res/new-file.png"), "New", this)),
      openModel(new QAction(QIcon(":/res/open-file.png"), "Open", this)),
      saveModel(new QAction(QIcon(":/res/save-file.png"), "Save", this)),
      renameHeaders(new QAction(QIcon(":/res/rename-headers.png"), "Rename headers", this)),
      insertRow(new QAction(QIcon(":/res/insert-row.png"), "Insert row", this)),
      removeRow(new QAction(QIcon(":/res/remove-row.png"), "Remove row", this)),
      insertColumn(new QAction(QIcon(":/res/insert-column.png"), "Insert column", this)),
      removeColumn(new QAction(QIcon(":/res/remove-column.png"), "Remove column", this)),
      chartSelector(new QComboBox),
      exitApp(new QAction(QIcon(":/res/exit-app.png"), "Exit", this))
{
    tabView->setTabsClosable(true);

    // QActions shortcuts
    // TODO ADD MORE SHORTCUTS
    QList<QKeySequence> newTabShortcuts;
    newTabShortcuts << QKeySequence::New << QKeySequence::AddTab;
    newTab->setShortcuts(newTabShortcuts);
    openModel->setShortcuts(QKeySequence::Open);
    saveModel->setShortcuts(QKeySequence::SaveAs);
    renameHeaders->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    insertRow->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_J));
    removeRow->setShortcut(QKeySequence(tr("Ctrl+Shift+J")));
    insertColumn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_K));
    removeColumn->setShortcut(QKeySequence(tr("Ctrl+Shift+K")));



    connect(tabView, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(newTab, SIGNAL(triggered()), this, SLOT(newTabDialog()));
    //connect(openModel, SIGNAL(triggered()), this, SLOT(importFile()));
    //connect(saveModel, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(renameHeaders, SIGNAL(triggered()), this, SLOT(renameHeadersDialog()));
    connect(insertRow, SIGNAL(triggered()), this, SLOT(insertRowTriggered()));
    connect(removeRow, SIGNAL(triggered()), this, SLOT(removeRowTriggered()));
    connect(insertColumn, SIGNAL(triggered()), this, SLOT(insertColumnTriggered()));
    connect(removeColumn, SIGNAL(triggered()), this, SLOT(removeColumnTriggered()));
    connect(chartSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCurrentChart(int)));
    // connect(exitApp, SIGNAL(triggered()), this, SLOT(QApplication::quit())); // non funzia

    setToolBar();
    setMenus();

    // VISUALIZER E SELETTORE GRAFICI (DA FARE)
    // TODO: CREARE UNA QLIST DI PUNTATORI A CHARVIEW PER SCORRERE I GRAFICI

    // TOGLIERE LA DEFAULT TAB UNA VOLTA CHE IL PROGETTO È FINITO PERCHÈ È STUPIDO PARTIRE DA UN SAMPLE
    DataTableModel *model = new DataTableModel(4,4);

    LineChart *chart = new LineChart(model);
    Scene *defaultTab = createNewTab(model, chart);
    tabView->addTab(defaultTab, "Table 1");

    mainLayout->addWidget(menuBar, 0, 0);
    mainLayout->addWidget(toolBar, 1, 0);
    mainLayout->addWidget(tabView, 2, 0);
    setLayout(mainLayout);

}


//======================== PUBLIC SLOTS =========================================


Scene *View::createNewTab(DataTableModel *model, QChart *chart)
{
    Scene *scene = new Scene(model, chart);
    tabView->addTab(scene, QString("Table %1").arg((tabView->currentIndex() + 2))); // possible conflicts with openfile
    tabView->setCurrentIndex(tabView->currentIndex() + 1);
    return scene;
}

void View::newTabDialog()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QString rowsLabel = QString("Rows number");
    QLineEdit *rowsInput = new QLineEdit(&dialog);
    QString colsLabel = QString("Columns number");
    QLineEdit *colsInput = new QLineEdit(&dialog);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    form.addRow(new QLabel("Create new table:"));
    form.addRow(new QLabel());
    form.addRow(rowsLabel, rowsInput);
    form.addRow(colsLabel, colsInput);
    form.addRow(new QLabel());
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    int rows, cols;
    bool safe;

    if (dialog.exec() == QDialog::Accepted) {
        rows = rowsInput->text().toInt(&safe, 10);
        cols = colsInput->text().toInt(&safe, 10);
        if (rows && cols)
        {
            DataTableModel *model = new DataTableModel(rows, cols);
            LineChart *chart = new LineChart(model);
            createNewTab(model, chart);
            renameHeadersDialog();
        }
        else dialog.reject();
    }
}

void View::closeTab(const int& index)
{
    if (index == -1) {
        return;
    }

    QWidget* tabItem = tabView->widget(index);
    // Removes the tab at position index from this stack of widgets.
    // The page widget itself is not deleted.
    tabView->removeTab(index);

    delete(tabItem);
    tabItem = nullptr;
}

void View::renameHeadersDialog()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    vector<QVariant> rowsHeaders = static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->getRowsHeaders();
    vector<QVariant> columnsHeaders = static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->getColumnsHeaders();

    vector<QLineEdit *> rowsHeadersInputs;
    vector<QLineEdit *> columnsHeadersInputs;

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    form.addRow(new QLabel("Rename table headers:"));
    form.addRow(new QLabel());
    form.addRow(new QLabel("Rows headers:"));

    int i = 0;
    for (auto it = rowsHeaders.begin(); it != rowsHeaders.end(); it++)
    {
        QString label = QString("%1").arg(i);
        QLineEdit *rowInput = new QLineEdit(&dialog);
        rowInput->setPlaceholderText(QString(it->toString()));
        rowsHeadersInputs.push_back(rowInput);
        form.insertRow(i+3, new QLabel(label), rowInput);
        i++;
    }

    form.addRow(new QLabel());
    form.addRow(new QLabel("Columns headers:"));

    int j = 0;
    for (auto it = columnsHeaders.begin(); it != columnsHeaders.end(); it++)
    {
        QString label = QString("%1").arg(j);
        QLineEdit *colInput = new QLineEdit(&dialog);
        colInput->setPlaceholderText(QString(it->toString()));
        columnsHeadersInputs.push_back(colInput);
        form.insertRow(j+i+5, new QLabel(label), colInput);
        j++;
    }

    form.addRow(new QLabel());
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // TODO: PREVENT SAME HEADERS NAME IN THE SAME ORIENTATION
    if (dialog.exec() == QDialog::Accepted) {
        for (unsigned int i = 0; i < rowsHeadersInputs.size(); i++)
        {
            QVariant newHeader = rowsHeadersInputs[i]->text();
            if (newHeader != "") static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->setHeaderData(i, Qt::Vertical, newHeader);
        }
        for (unsigned int i = 0; i < columnsHeadersInputs.size(); i++)
        {
            QVariant newHeader = columnsHeadersInputs[i]->text();
            if (newHeader != "") static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->setHeaderData(i, Qt::Horizontal, newHeader);
        }
    }
    else dialog.reject();
}

void View::changeCurrentChart(int index)
{
    static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->setChart(index);
}

void View::insertRowTriggered()
{
    controller.insertRowReceived(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel());
    dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart())->insertSeries();
}

void View::removeRowTriggered()
{
    try
    {
        controller.removeRowReceived(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel());
        dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart())->removeSeries(); // TOFIX: ERRORE QUANDO SI PROVA A RIMUOVERE ULTIMA RIGA RIMASTA
    }
    catch (const QString &errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage);
    }


}

void View::insertColumnTriggered()
{
    controller.insertColumnReceived(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel());
    dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart())->insertSeriesValue();
}

void View::removeColumnTriggered()
{
    try
    {
        controller.removeColumnReceived(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel());
        dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart())->removeSeriesValue();
    }
    catch (const QString &errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage);
    }
}

/*

void View::importFile(){
    QString import = QFileDialog::getOpenFileName(nullptr, tr("Select a JSON Document"),"/home", tr("Json document(*.json)"));
    //if(import == "") throw Error;              ===>   ECCEZIONE, TODO
    Parser* parser = new JsonParser();
    createNewTab(parser->load(import));
}

void View::saveFile(){ // TO-DO: AGGIUNGERE AUTOMATICAMENTE ESTENSIONE
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Select a directory"), "/home" );
    QFile f(fileName);
    f.open( QIODevice::WriteOnly );
    Parser* parser = new JsonParser();

    // ======================= TEST
        int cols = 2;
        int rows= 3;
        vector<vector<double>> val;
        vector<vector<string>> head;
        vector<double> first = {2,3,4};
        vector<double> second = {23, 4,1};
        vector<double> third = {4, 5, 7};
        val.push_back(first);
        val.push_back(second);
        val.push_back(third);
        vector<string> primo = {"tony", "montana"};
        vector<string> secondo = {"agosto", "settembre", "novembre"};
        head.push_back(primo);
        head.push_back(secondo);

    // ====================== FINE TEST

    parser->save(new DataTableModel(0,rows,cols,val,head), f);
    //TODO
    f.close();
}
*/
View::~View()
{
}

