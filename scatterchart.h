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
    void insertSeries() override;
    void removeSeries() override;
    void updateChartView() override;
    void insertSeriesValue() override;
    void removeSeriesValue() override;
    void clearChart() override;
public slots:
    virtual void replaceValue(QModelIndex, QModelIndex) override;
    virtual void updateSeriesName(Qt::Orientation, int, int) override;
};

#endif // SCATTERCHART_H
