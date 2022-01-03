#include "view.h"
#include "model.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QLineSeries>
#include <QGridLayout>
#include <QVXYModelMapper>
#include <QHeaderView>
#include <QTabWidget>
#include <QToolButton>
#include <QToolBar>
#include <QMenuBar>
#include <QVPieModelMapper>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>
#include <QMenu>

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

QToolBar * View::createToolBar()
{
    QToolBar *toolBar = new QToolBar;

    QAction *newTab = new QAction("New", this);
    newTab->setShortcuts(QKeySequence::New);
    connect(newTab, SIGNAL(triggered()), this, SLOT(createNewTab()));



    toolBar->setOrientation(Qt::Vertical);
    toolBar->addAction(newTab);
    toolBar->addAction("Open");
    toolBar->addAction("Save");
    toolBar->addAction("+Tab");
    toolBar->addAction("-Tab");
    toolBar->addAction("+row");
    toolBar->addAction("-row");
    toolBar->addAction("+col");
    toolBar->addAction("-col");
    toolBar->addAction("Line");

    return toolBar;
}

QTableView * View::createTableView(DataTableModel *model)
{
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    return tableView;
}

// DA SPOSTARE NEL CONTROLLER PROBABILMENTE
QWidget * View::createNewTab(DataTableModel *model)
{
    QWidget *newTab = new QWidget;

    QGridLayout *sceneLayout = new QGridLayout(newTab);

    // SOLUZIONE TEMPORANEA (poi si dovrà implementare quella che scorre e sceglie il grafico voluto)
    QChartView *chartView = new QChartView(createLineChart(model));
    chartView->setMinimumSize(640, 480);
    chartView->setRenderHint(QPainter::Antialiasing);


    sceneLayout->addWidget(createTableView(model), 1, 0);
    sceneLayout->addWidget(chartView, 1, 1);
    sceneLayout->setColumnStretch(0, 2);
    sceneLayout->setColumnStretch(1, 3);

    newTab->setLayout(sceneLayout);
    tabView->addTab(newTab, "test");
    tabView->setCurrentIndex(tabView->currentIndex() + 1);

    return newTab;
}

View::View(QWidget *parent)
    : QWidget(parent), tabView(new QTabWidget), mainLayout(new QGridLayout)
{
    // LOAD (CREATE ACTUALLY) MODEL AND TABLE
    DataTableModel *model = new DataTableModel;

    // VISUALIZER E SELETTORE GRAFICI (DA FARE)
    // TODO: CREARE UNA QLIST DI PUNTATORI A CHARVIEW PER SCORRERE I GRAFICI


    // TODO: IMPLEMENTARE NEW TAB WITH DEFAULT MODEL -- DOVE?????
    QWidget *defaultTab = createNewTab(model);
    tabView->addTab(defaultTab, "Model");

    mainLayout->addWidget(tabView, 0, 1);
    mainLayout->addWidget(createToolBar(), 0, 0);
    setLayout(mainLayout);


    // ! TUTTO QUELLO QUA SOPRA FUNZIONA

}

View::~View()
{
}

