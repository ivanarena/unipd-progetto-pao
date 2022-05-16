#ifndef SCATTERCHART_H
#define SCATTERCHART_H

#include "chart.h"
#include <QCategoryAxis>
#include <QScatterSeries>

class ScatterChart : public Chart
{
    Q_OBJECT;
private:
    QCategoryAxis *XAxis;
    QValueAxis *YAxis;
    vector<QScatterSeries*> ScatterSeries;
public:
    ScatterChart(DataTableModel*);
    ~ScatterChart();

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

#endif // SCATTERCHART_H
