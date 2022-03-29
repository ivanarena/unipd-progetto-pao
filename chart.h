#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QModelIndex>
#include "model.h"

using namespace QtCharts;

class Chart : public QChart
{
    Q_OBJECT
public:
    Chart(DataTableModel*);

    virtual void mapData();
    virtual void insertSeries(); // usalo quando aggiungi righe
    virtual void removeSeries(); // '''' rimuovi ''
    virtual void updateChartView();
    virtual void insertSeriesValue(); // usalo quando aggiungi colonne
    virtual void removeSeriesValue(); // '''' rimuovi ''

    virtual ~Chart();

public slots:
    virtual void replaceValue(QModelIndex, QModelIndex);
    virtual void updateSeriesName(Qt::Orientation, int, int);
protected:
    DataTableModel* model;
};

#endif // CHART_H
