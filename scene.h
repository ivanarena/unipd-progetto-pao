#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include "model.h"


class Scene : public QWidget
{
    Q_OBJECT
private:


public:
    explicit Scene(DataTableModel *c_model = new DataTableModel, QWidget *parent = nullptr);

    DataTableModel *model;
    QTableView *table;
    QChartView *chart;

signals:

};

#endif // SCENE_H
