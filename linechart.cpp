#include "linechart.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>
#include <QVXYModelMapper>

LineChart::LineChart(DataTableModel *c_model) : model(c_model)
{
    //legend()->hide(); LEGENDA
    setTitle("Line Chart");
    setAnimationOptions(QChart::AllAnimations);

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

        m_series.push_back(series);
        m_mappers.push_back(mapper);
    }

    createDefaultAxes(); // usalo anche quando fai update ez
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

    createDefaultAxes();
}

void LineChart::removeSeries() // it gives some error but it works perfectly
{
    QChart::removeSeries(dynamic_cast<QLineSeries *>(m_series.back()));

    delete m_series.back();
    delete m_mappers.back();

    m_series.pop_back();
    m_mappers.pop_back();

    createDefaultAxes();
}

