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

using namespace std;

class LineChart : public Chart
{
private:
    DataTableModel *model;
    QValueAxis *XAxis;
    QValueAxis *YAxis;

    vector<QLineSeries *> m_series;
    vector<QHXYModelMapper *> m_mappers;
public:
    LineChart(DataTableModel *c_model);

    virtual void insertSeries() override;
    virtual void removeSeries() override;
    virtual void updateAxis() override;
};

#endif // LINECHART_H
