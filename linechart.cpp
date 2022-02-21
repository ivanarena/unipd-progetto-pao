#include "linechart.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>
#include <QValueAxis>
#include <QVXYModelMapper>
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
    for (int i = 1; i < model->columnCount(); i++) {
        QLineSeries *series = new QLineSeries;
        QVXYModelMapper *mapper = new QVXYModelMapper;
        //series->setName(QString("%1").arg(i)); SET NAME AS HEADERS
        mapper->setXColumn(0);
        mapper->setYColumn(i);
        mapper->setSeries(series);
        mapper->setModel(model);
        addSeries(series);

        series->attachAxis(XAxis);
        series->attachAxis(YAxis);

        m_series.push_back(series);
        m_mappers.push_back(mapper);
    }


    //createDefaultAxes(); // usalo anche quando fai update ez
}

void LineChart::insertSeries()
{
    QLineSeries *series = new QLineSeries;
    QVXYModelMapper *mapper = new QVXYModelMapper;
    mapper->setXColumn(0);
    mapper->setYColumn(model->columnCount() - 1);
    mapper->setSeries(series);
    mapper->setModel(model);
    addSeries(series);

    m_series.push_back(series);
    m_mappers.push_back(mapper);
}

void LineChart::removeSeries() // it gives some error but it works perfectly
{
    QChart::removeSeries(dynamic_cast<QLineSeries *>(m_series.back()));

    delete m_series.back();
    delete m_mappers.back();

    m_series.pop_back();
    m_mappers.pop_back();

}

void LineChart::updateAxis()
{
    XAxis->setRange(0,30); // set max and min
    YAxis->setRange(0,50); // set max and min
}

