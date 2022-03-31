#include <QModelIndex>
#include "chart.h"


Chart::Chart(DataTableModel* m): model(m)
{
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(replaceValue(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(updateSeriesName(Qt::Orientation,int,int)));
}

void Chart::mapData() {}
void Chart::insertSeries() {}
void Chart::removeSeries() {}
void Chart::updateChartView() {}
void Chart::insertSeriesValue() {}
void Chart::removeSeriesValue() {}

void Chart::replaceValue(QModelIndex, QModelIndex) {}
void Chart::updateSeriesName(Qt::Orientation, int, int) {}

Chart::~Chart()
{

}

