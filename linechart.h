#ifndef LINECHART_H
#define LINECHART_H


#include "chart.h"
#include "model.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>
#include <QVXYModelMapper>

using namespace std;


class LineChart : public Chart
{
private:
    QChart *chart;
    DataTableModel *model;

    vector<QLineSeries *> m_series;
    vector<QVXYModelMapper *> m_mappers;
public:
    LineChart(DataTableModel *c_model);
    QChart *getChart() const;
};

#endif // LINECHART_H
