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

View::View(QWidget *parent)
    : QWidget(parent)
{


    // LOAD (CREATE ACTUALLY) MODEL AND TABLE
    DataTableModel *model = new DataTableModel;
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    // IMPLEMENTAZIONE LINE CHART
    QChart *lineChart = createLineChart(model);


    // VISUALIZER E SELETTORE GRAFICI (DA FARE)
    // TODO: CREARE UNA QLIST DI PUNTATORI A CHARVIEW PER SCORRERE I GRAFICI
    QChartView *chartView = new QChartView(lineChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);





    // MAIN LAYOUT + ADJUST LAYOUT AUTOMATICALLY
    QTabWidget *tabView= new QTabWidget;

    QWidget *mainWindow = new QWidget;

    QGridLayout *sceneLayout = new QGridLayout(mainWindow);
    sceneLayout->addWidget(tableView, 1, 0);
    sceneLayout->addWidget(chartView, 1, 1);
    sceneLayout->setColumnStretch(0, 2);
    sceneLayout->setColumnStretch(1, 3);

    mainWindow->setLayout(sceneLayout);

    tabView->addTab(mainWindow, "Model");
    //tabView->show(); // PROBABILMENTE NON SERVE PERCHÉ HO FIXATO


    QGridLayout *mainLayout = new QGridLayout;

    QToolBar *toolBar = new QToolBar;
    toolBar->setOrientation(Qt::Vertical);

    // TODO: LE AZIONI DOVREBBERO ESSERE CREATE ALTROVE ED ESSERE USATE UGUALI ANCHE NEL MENU
    toolBar->addAction("New");
    toolBar->addAction("Open");
    toolBar->addAction("Save");
    toolBar->addAction("+Tab");
    toolBar->addAction("-Tab");
    toolBar->addAction("+row");
    toolBar->addAction("-row");
    toolBar->addAction("+col");
    toolBar->addAction("-col");

    mainLayout->addWidget(toolBar, 1, 0);
    mainLayout->addWidget(tabView, 1, 1);
    setLayout(mainLayout);

    // ! TUTTO QUELLO QUA SOPRA FUNZIONA




}

View::~View()
{
}

