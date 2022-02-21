#include "linechart.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>
#include <QValueAxis>
#include <QHXYModelMapper>
#include <iostream>

using namespace std;
using namespace QtCharts;

LineChart::LineChart(DataTableModel *c_model) : model(c_model), XAxis(new QValueAxis), YAxis(new QValueAxis)
{
    //legend()->hide(); LEGENDA
    setTitle("Line Chart");
    setAnimationOptions(QChart::AllAnimations);

    addAxis(XAxis, Qt::AlignBottom);
    addAxis(YAxis, Qt::AlignLeft);

    // mapper table->chart
    for (int i = 1; i < model->rowCount(); i++) {
        QLineSeries *series = new QLineSeries;
        QHXYModelMapper *mapper = new QHXYModelMapper;
        //series->setName(QString("%1").arg(i)); SET NAME AS HEADERS
        mapper->setXRow(0);
        mapper->setYRow(i);
        mapper->setSeries(series);
        mapper->setModel(model);
        addSeries(series);

        series->attachAxis(XAxis);
        series->attachAxis(YAxis);

        m_series.push_back(series);
        m_mappers.push_back(mapper);
    }

    LineChart::updateAxis();
}

void LineChart::insertSeries()
{
    QLineSeries *series = new QLineSeries;
    QHXYModelMapper *mapper = new QHXYModelMapper;
    mapper->setXRow(0);
    mapper->setYRow(model->rowCount() - 1);
    mapper->setSeries(series);
    mapper->setModel(model);
    addSeries(series);

    series->attachAxis(XAxis);
    series->attachAxis(YAxis);

    m_series.push_back(series);
    m_mappers.push_back(mapper);

    updateAxis();
}

void LineChart::removeSeries() // it gives some error but it works perfectly
{
    QChart::removeSeries(dynamic_cast<QLineSeries *>(m_series.back()));

    delete m_series.back();
    delete m_mappers.back();

    m_series.pop_back();
    m_mappers.pop_back();

    updateAxis();
}

void LineChart::updateAxis()
{
    XAxis->setRange(0,10); // set max and min
    YAxis->setRange(0,10); // set max and min
}

