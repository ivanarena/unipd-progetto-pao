#include "scene.h"

Scene::Scene(DataTableModel *c_model, QChartView *c_chart, QWidget *parent)
    : QWidget{parent}, sceneLayout(new QGridLayout(this)),
      model(c_model), table(new QTableView), chart(c_chart)
{
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    chart->setMinimumSize(640, 480);
    chart->setRenderHint(QPainter::Antialiasing);

    sceneLayout->addWidget(table, 1, 0);
    sceneLayout->addWidget(chart, 1, 1);
    sceneLayout->setColumnStretch(0, 2);
    sceneLayout->setColumnStretch(1, 3);

    setLayout(sceneLayout);
}

DataTableModel *Scene::getModel() const
{
    return model;
}

QChartView *Scene::getChart() const
{
    return chart;
}
