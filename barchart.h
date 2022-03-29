#ifndef BARCHART_H
#define BARCHART_H

#include "chart.h"
#include "model.h"
#include <QBarCategoryAxis>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>

class BarChart : public Chart
{
    Q_OBJECT
private:
    //DataTableModel *model;
    QBarCategoryAxis *XAxis;
    QValueAxis *YAxis;

    QBarSeries *m_series;
    vector<QBarSet *> m_sets;
public:
    BarChart(DataTableModel *c_model);

    virtual void mapData() override;
    virtual void updateChartView() override;
    virtual void insertSeries() override; // add row
    virtual void removeSeries() override;
    virtual void insertSeriesValue() override; // add column
    virtual void removeSeriesValue() override;

public slots:
    virtual void replaceValue(QModelIndex, QModelIndex) override;
    virtual void updateSeriesName(Qt::Orientation, int, int) override;
};

#endif // BARCHART_H
