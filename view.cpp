#include "view.h"
#include "model.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QGridLayout>
#include <QHeaderView>

View::View(QWidget *parent)
    : QWidget(parent)
{


    // LOAD (CREATE ACTUALLY) MODEL AND TABLE
    DataTableModel *model = new DataTableModel;
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    // CHART
    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);

    // SERIES

    //chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

    /* TODO:
     * INCLUDE CHARTS
     * (READ EVERY CHART DOCUMENTATION)




    ************/
    // MAIN LAYOUT + ADJUST LAYOUT AUTOMATICALLY
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->setColumnStretch(0, 2);
    mainLayout->setColumnStretch(1, 3);
    setLayout(mainLayout);



}

View::~View()
{
}

