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
    QChart *PieChart = new QChart();
    QVPieModelMapper *piemapper = new QVPieModelMapper();
    PieChart->setTitle("Pie chart");
    QPieSeries *series = new QPieSeries(PieChart);

    piemapper->setSeries(series);
    piemapper->setModel(model); //TODO: capire come implementare il piechart con questo set di dati
    piemapper->setLabelsColumn(0); // a quale colonna associare  label
    piemapper->setValuesColumn(1); // a quale colonna associare valore
    piemapper->setFirstRow(0); //da che riga del model inizio
    piemapper->setRowCount(model->rowCount()); //una riga -> una slice

    PieChart->addSeries(series);
    series->setPieSize(5);
    series->setHoleSize(0.5);


    return PieChart;
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


    // IMPLEMENTAZIONE CHARTS
    QChart *lineChart = createLineChart(model);
    QChart *piechart = createPieChart(model);


    // VISUALIZER E SELETTORE GRAFICI (DA FARE)
    // TODO: CREARE UNA QLIST DI PUNTATORI A CHARVIEW PER SCORRERE I GRAFICI
    QChartView *chartView = new QChartView(lineChart);
    QChartView *chart1View = new QChartView(piechart);
    chartView->setMinimumSize(320, 240);
    chart1View->setMinimumSize(320, 240);



    // MAIN LAYOUT + ADJUST LAYOUT AUTOMATICALLY
    QTabWidget *tabView= new QTabWidget;

    QWidget *mainWindow = new QWidget;

    QGridLayout *sceneLayout = new QGridLayout(mainWindow);

    sceneLayout->addWidget(tableView, 1, 0);
    sceneLayout->addWidget(chartView, 1, 1);
    sceneLayout->addWidget(chart1View,1,2);
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


    // Sezione relativa ai progetti, TODO:  pulsante per crearne uno nuovo dovrebbe stare da un altra parte

    QToolBar *Projects = new QToolBar;
    Projects ->setOrientation(Qt::Horizontal);

    Projects->addAction("Project1");  // Il nome del progetto dovrebbe essere scelto dall'utente tramite pulsante new
    Projects->addAction("Project2");
    Projects->addAction("+");

    mainLayout->addWidget(Projects,0,1);
    mainLayout->addWidget(toolBar, 1, 0);
    mainLayout->addWidget(tabView, 1, 1);
    setLayout(mainLayout);

    // ! TUTTO QUELLO QUA SOPRA FUNZIONA




}

View::~View()
{
}

