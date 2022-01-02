#ifndef PIECHART_H
#define PIECHART_H

#include "Graph.h"

#include <QObject>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>


class PieChart : public Graph
{
public:
    PieChart();
};

#endif // PIECHART_H
