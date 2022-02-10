#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QWidget>
#include <QWidget>
#include <QTableView>
#include <QGridLayout>
#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include "model.h"


class Scene : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *sceneLayout;
    DataTableModel *model;
    QTableView *table;
    QChartView *chart;

public:
    explicit Scene(DataTableModel *c_model = new DataTableModel, QWidget *parent = nullptr);
    DataTableModel *getModel();
signals:

};

#endif // SCENE_H
