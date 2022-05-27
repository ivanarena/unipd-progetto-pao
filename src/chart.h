#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QModelIndex>
#include "model.h"

using namespace QtCharts;

class Chart :public QChart
{
    Q_OBJECT
public:
    Chart(DataTableModel* m);

    virtual void mapData();
    virtual void insertSeries();
    virtual void removeSeries();
    virtual void updateChartView();
    virtual void insertSeriesValue();
    virtual void removeSeriesValue();
    virtual void clearChart();

    virtual ~Chart();
protected:
    DataTableModel* model;
public slots:
    virtual void replaceValue(QModelIndex, QModelIndex);
    virtual void updateSeriesName(Qt::Orientation, int, int);
};

#endif // CHART_H
