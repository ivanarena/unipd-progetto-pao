#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QModelIndex>


using namespace QtCharts;

class Chart : public QChart
{
    Q_OBJECT
public:
    Chart();

    virtual void mapData();
    virtual void insertSeries();
    virtual void removeSeries();
    virtual void updateAxis();

    virtual ~Chart();

public slots:
    virtual void replaceValue(QModelIndex, QModelIndex);
    virtual void updateSeriesName(Qt::Orientation, int, int);
};

#endif // CHART_H
