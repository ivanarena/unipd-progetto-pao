#ifndef PIE_CHART_H
#define PIE_CHART_H

#include "chart.h"

#include <QObject>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>


class PieChart : public Chart
{
public:
    PieChart();
};

#endif // PIE_CHART_H
