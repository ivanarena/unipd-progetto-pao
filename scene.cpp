#include "scene.h"

Scene::Scene(DataTableModel *c_model, QWidget *parent)
    : QWidget{parent},
      model(c_model), table(new QTableView), chart(new QChartView)
{
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    chart->setMinimumSize(640, 480);
    chart->setRenderHint(QPainter::Antialiasing);
}
