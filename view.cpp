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

using namespace std;

// TODO: FARE UNA CLASSE PER OGNI CHART ED IMPLEMENTARE QUESTO METODO COME UNICO createChart POLIMORFO
QChart * View::createLineChart(DataTableModel *model)
{
    QChart *lineChart = new QChart();
    //lineChart->legend()->hide(); LEGENDA
    lineChart->setTitle("Title");
    lineChart->setAnimationOptions(QChart::AllAnimations);

    // mapper table->chart
    for (int i = 1; i < model->columnCount(); i++) {
        QLineSeries *series = new QLineSeries;
        QVXYModelMapper *mapper = new QVXYModelMapper(this);
        series->setName(QString("%1").arg(i));
        mapper->setXColumn(0);
        mapper->setYColumn(i);
        mapper->setSeries(series);
        mapper->setModel(model);
        lineChart->addSeries(series);
    }

    lineChart->createDefaultAxes();

    return lineChart;
}

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
    QComboBox *chartSelectionBox = new QComboBox;
    chartSelectionBox->addItem("Line Chart");
    chartSelectionBox->addItem("Pie Chart");

    //toolBar->setOrientation(Qt::Vertical);
    toolBar->addSeparator();
    toolBar->addAction(newTab);
    toolBar->addAction(openModel);
    toolBar->addAction(saveModel);
    toolBar->addSeparator();
    toolBar->addAction(insertRow);
    toolBar->addAction(removeRow);
    toolBar->addSeparator();
    toolBar->addAction(insertColumn);
    toolBar->addAction(removeColumn);
    toolBar->addSeparator();
    toolBar->addWidget(chartSelectionBox);
    toolBar->addSeparator();

    toolBar->setIconSize(QSize(36, 36));

}

void View::setMenus()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newTab);
    fileMenu->addAction(openModel);
    fileMenu->addAction(saveModel);
    fileMenu->addSeparator();
    fileMenu->addAction(exitApp);

    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(insertRow);
    editMenu->addAction(removeRow);
    editMenu->addSeparator();
    editMenu->addAction(insertColumn);
    editMenu->addAction(removeColumn);
    editMenu->addSeparator();
}

QTableView * View::createTableView(DataTableModel *model)
{
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    return tableView;
}

// IMPORTANTISSIMO!!!!! IMPLEMENTARE UN VETTORE CHE SCORRE I MODELLI E GESTISCE I MODELLI DI OGNI TAB
View::View(QWidget *parent)
    : QWidget(parent), mainLayout(new QGridLayout), tabView(new QTabWidget), toolBar(new QToolBar),
      menuBar(new QMenuBar), fileMenu(new QMenu), editMenu(new QMenu),
      newTab(new QAction(QIcon(":/res/new-file.png"), "New", this)),
      openModel(new QAction(QIcon(":/res/open-file.png"), "Open", this)),
      saveModel(new QAction(QIcon(":/res/save-file.png"), "Save", this)),
      insertRow(new QAction(QIcon(":/res/insert-row.png"), "Insert row", this)),
      removeRow(new QAction(QIcon(":/res/remove-row.png"), "Remove row", this)),
      insertColumn(new QAction(QIcon(":/res/insert-column.png"), "Insert column", this)),
      removeColumn(new QAction(QIcon(":/res/remove-column.png"), "Remove column", this)),
      exitApp(new QAction(QIcon(":/res/exit-app.png"), "Exit", this))
{
    connect(tabView, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    tabView->setTabsClosable(true);

    // QActions shortcuts
    // TODO ADD MORE SHORTCUTS
    QList<QKeySequence> newTabShortcuts;
    newTabShortcuts << QKeySequence::New << QKeySequence::AddTab;
    newTab->setShortcuts(newTabShortcuts);
    openModel->setShortcuts(QKeySequence::Open);
    saveModel->setShortcuts(QKeySequence::SaveAs);

    connect(newTab, SIGNAL(triggered()), this, SLOT(newTabDialog()));
    // non funzia dc
    // connect(addRow, SIGNAL(triggered()), &controller, SLOT(addRowPressed(tabModels.at(tabView->currentIndex()))));
    connect(openModel, SIGNAL(triggered()), this, SLOT(importFile()));
    connect(saveModel, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(exitApp, SIGNAL(triggered()), this, SLOT(QApplication::quit())); // non funzia

    setToolBar();
    setMenus();

    // VISUALIZER E SELETTORE GRAFICI (DA FARE)
    // TODO: CREARE UNA QLIST DI PUNTATORI A CHARVIEW PER SCORRERE I GRAFICI

    // TOGLIERE LA DEFAULT TAB UNA VOLTA CHE IL PROGETTO È FINITO PERCHÈ È STUPIDO PARTIRE DA UN SAMPLE
    DataTableModel *model = new DataTableModel();
    QWidget *defaultTab = createNewTab(model);
    tabView->addTab(defaultTab, "Table 1");
    mainLayout->addWidget(menuBar, 0, 0);
    mainLayout->addWidget(toolBar, 1, 0);
    mainLayout->addWidget(tabView, 2, 0);
    setLayout(mainLayout);

}


//======================== PUBLIC SLOTS =========================================


QWidget * View::createNewTab(DataTableModel *model)
{
    QWidget *newTab = new QWidget;
    QGridLayout *sceneLayout = new QGridLayout(newTab);

    QTableView *tableView = createTableView(model);

    // SOLUZIONE TEMPORANEA (poi si dovrà implementare quella che scorre e sceglie il grafico voluto)
    QChartView *chartView = new QChartView(createLineChart(model));
    chartView->setMinimumSize(640, 480);
    chartView->setRenderHint(QPainter::Antialiasing);

    sceneLayout->addWidget(tableView, 1, 0);
    sceneLayout->addWidget(chartView, 1, 1);
    sceneLayout->setColumnStretch(0, 2);
    sceneLayout->setColumnStretch(1, 3);

    newTab->setLayout(sceneLayout);
    tabView->addTab(newTab, QString("Table %1").arg((tabView->currentIndex() + 2))); // !!!TOFIX
    tabView->setCurrentIndex(tabView->currentIndex() + 1);

    return newTab;
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
            createNewTab(new DataTableModel(rows, cols));
        else dialog.reject();
    }
}

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


View::~View()
{
}

