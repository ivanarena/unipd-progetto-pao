#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QModelIndex>
#include "model.h"

using namespace QtCharts;
enum consistency{consistent, inconsistent};

class Chart :public QChart
{
    Q_OBJECT
public:
    Chart(DataTableModel* m);

    virtual void mapData();
    virtual void insertSeries(); // usalo quando aggiungi righe
    virtual void removeSeries(); // '''' rimuovi ''
    virtual void updateChartView();
    virtual void insertSeriesValue(); // usalo quando aggiungi colonne
    virtual void removeSeriesValue(); // '''' rimuovi ''
    virtual void clearChart();
    virtual void checkState();

    virtual ~Chart();
protected:
    DataTableModel* model;
    consistency state = consistent;
public slots:
    virtual void replaceValue(QModelIndex, QModelIndex);
    virtual void updateSeriesName(Qt::Orientation, int, int);
};

#endif // CHART_H
