#include "scene.h"
#include "barchart.h"

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
    chart = new BarChart(model);

    switch (chartIndex)
    {
        case 0:
            chart = new LineChart(model);
            break;
        case 1:
            chart = new BarChart(model);
            break;
        default:
            break;
    }

    chartView->setChart(chart);
    delete oldChart;
}
