#ifndef LINECHART_H
#define LINECHART_H


#include "chart.h"
#include "model.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>
#include <QHXYModelMapper>
#include <QCategoryAxis>

using namespace std;

class LineChart : public Chart
{
    Q_OBJECT
private:
    DataTableModel *model;
    QCategoryAxis *XAxis;
    QValueAxis *YAxis;

    vector<QLineSeries *> m_series;
public:
    LineChart(DataTableModel *c_model);

    // TODO: BIND MODEL SIGNALS TO LINECHART SLOTS TO UPDATE SERIES with replace

    virtual void mapData() override;
    virtual void updateAxes() override;
    virtual void insertSeries() override; // add row
    virtual void removeSeries() override;
    virtual void insertSeriesValue() override; // add column
    virtual void removeSeriesValue() override;

public slots:
    virtual void replaceValue(QModelIndex, QModelIndex) override;
    virtual void updateSeriesName(Qt::Orientation, int, int) override;
};

#endif // LINECHART_H
