#ifndef POLARCHART_H
#define POLARCHART_H

#include <QObject>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCharts/QSplineSeries>
#include <QCategoryAxis>
#include "chart.h"
#include "model.h"


class PolarChart : public Chart, virtual public QPolarChart
{
private:
    QCategoryAxis *XAxis;
    QValueAxis *YAxis;
    vector<QSplineSeries*> SplineSeries;
public:
    PolarChart(DataTableModel*);
    ~PolarChart();

    void mapData() override;
    void insertSeries() override; // usalo quando aggiungi righe
    void removeSeries() override; // '''' rimuovi ''
    void updateChartView() override;
    void insertSeriesValue() override; // usalo quando aggiungi colonne
    void removeSeriesValue() override; // '''' rimuovi ''
    void clearChart() override;
public slots:
    virtual void replaceValue(QModelIndex, QModelIndex) override;
    virtual void updateSeriesName(Qt::Orientation, int, int) override;
};

#endif // POLARCHART_H

