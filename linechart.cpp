#include "linechart.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>
#include <QModelIndex>
#include <QValueAxis>
#include <QHXYModelMapper>
#include <QCategoryAxis>
#include <iostream>

using namespace std;
using namespace QtCharts;

void LineChart::mapData()
{
    vector<vector<double>> data = model->getData();
    for (int i = 0; i < model->rowCount(); i++)
    {
        QLineSeries *series = new QLineSeries;
        series->setName(model->getRowsHeaders().at(i).toString());
        double k = 0.5;
        for (int j = 0; j < model->columnCount(); j++)
        {
            series->append(QPointF(k, data[i].at(j)));
            k++;
        }
        addSeries(series);

        series->attachAxis(XAxis);
        series->attachAxis(YAxis);

        m_series.push_back(series);
    }

    LineChart::updateAxis();
}

LineChart::LineChart(DataTableModel *c_model) : model(c_model), XAxis(new QCategoryAxis), YAxis(new QValueAxis)
{
    //legend()->hide(); LEGENDA
    setTitle("Line Chart");
    setAnimationOptions(QChart::AllAnimations);


    for (int i = 0; i < model->columnCount(); i++)
    {
        XAxis->append(model->getColumnsHeaders().at(i).toString(), i+1);
    }

    addAxis(XAxis, Qt::AlignBottom);
    addAxis(YAxis, Qt::AlignLeft);

    LineChart::mapData();

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(replaceValue(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(updateSeriesName(Qt::Orientation,int,int)));
}

void LineChart::insertSeries()
{
    vector<vector<double>> data = model->getData();
    QLineSeries *series = new QLineSeries;
    series->setName(model->getRowsHeaders().at(model->columnCount()).toString());
    int k = 0;
    for (int j = 0; j < model->columnCount(); j++)
    {
        series->append(QPointF(k, data[model->columnCount()].at(j)));
        k++;
    }
    addSeries(series);

    series->attachAxis(XAxis);
    series->attachAxis(YAxis);

    m_series.push_back(series);
    updateAxis();
}

void LineChart::removeSeries()
{
    if (m_series.back())
        QChart::removeSeries(dynamic_cast<QLineSeries *>(m_series.back()));
    else return;

    delete m_series.back();

    m_series.pop_back();

    updateAxis();
}

void LineChart::updateAxis()
{
    XAxis->setRange(0, model->columnCount()); // set max and min
    YAxis->applyNiceNumbers();
}

void LineChart::replaceValue(QModelIndex i, QModelIndex j)
{
    vector<vector<double>> data = model->getData();
    const QPointF oldPoint = m_series[i.row()]->at(j.column());
    const QPointF newPoint = QPointF(oldPoint.x(), data.at(i.row()).at(j.column()));
    m_series[i.row()]->replace(oldPoint.x(), oldPoint.y(), newPoint.x(), newPoint.y());
    updateAxis();
}

void LineChart::updateSeriesName(Qt::Orientation orientation, int first, int last)
{
    if (orientation == Qt::Horizontal)
    {
        XAxis->replaceLabel(m_series.at(first)->name(), model->getColumnsHeaders().at(last).toString());
        m_series.at(first)->setName(model->getColumnsHeaders().at(last).toString());
    }
}
