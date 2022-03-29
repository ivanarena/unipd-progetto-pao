#include "scene.h"
#include "barchart.h"
#include "piechart.h"
#include "linechart.h"
#include <typeinfo>

Scene::Scene(DataTableModel *c_model, QChart *c_chart, QWidget *parent)
    : QWidget{parent}, sceneLayout(new QGridLayout(this)),
      model(c_model), table(new QTableView), chart(c_chart), chartView(new QChartView(c_chart))
{
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    chartView->setMinimumSize(640, 480);
    chartView->setRenderHint(QPainter::Antialiasing);

    sceneLayout->addWidget(table, 1, 0);
    sceneLayout->addWidget(chartView, 1, 1);
    sceneLayout->setColumnStretch(0, 2);
    sceneLayout->setColumnStretch(1, 3);

    setLayout(sceneLayout);
}

DataTableModel *Scene::getModel() const
{
    return model;
}

QChart *Scene::getChart() const
{
    return chart;
}

QChartView *Scene::getChartView() const
{
    return chartView;
}

void Scene::setActiveChart(int chartIndex)
{
    QChart *oldChart = chart;

    switch (chartIndex)
    {
        case 0:
            if(typeid(*chart) != typeid(LineChart)) chart = new LineChart(model);
            else return;
            break;
        case 1:
            if(typeid(*chart) != typeid(BarChart)) chart = new BarChart(model);
            else return;
            break;
        case 2:
            if(typeid(*chart) != typeid(PieChart)) chart = new PieChart(model);
            else return;
            break;
        default:
            break;
    }

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    delete oldChart;
}
