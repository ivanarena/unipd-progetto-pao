#include <QModelIndex>
#include "chart.h"
#include <iostream>
using namespace std;

Chart::Chart(DataTableModel* m): model(m)
{
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(replaceValue(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(updateSeriesName(Qt::Orientation,int,int)));
    //setAnimationOptions(QChart::NoAnimation);
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

void Chart::clearChart() {}

void Chart::checkState(){
    if(model->rowCount()<1 || model->columnCount()<1){
        state=inconsistent;
        clearChart();
    }
    else if(state==inconsistent){
        mapData();
        state=consistent;
    }
}
