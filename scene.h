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
#include "linechart.h"
#include "barchart.h"


class Scene : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *sceneLayout;
    DataTableModel *model;
    QTableView *table;
    QChart *chart;
    QChartView *chartView;

public:
    explicit Scene(DataTableModel *c_model = new DataTableModel, QChart *c_chart = new QChart(), QWidget *parent = nullptr);
    DataTableModel *getModel() const;
    QChart *getChart() const;
    QChartView *getChartView() const;

    void setActiveChart(int chartIndex);

signals:

};

#endif // SCENE_H
