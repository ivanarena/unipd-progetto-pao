#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>

using namespace QtCharts;

class Chart : public QChart
{
public:
    Chart();

    virtual void insertSeries();
    virtual void removeSeries();
    virtual void updateAxis();

    virtual ~Chart();

};

#endif // CHART_H
