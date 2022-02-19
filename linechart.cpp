#include "linechart.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>
#include <QVXYModelMapper>

LineChart::LineChart(DataTableModel *c_model) : chart(new QChart), model(c_model)
{
    //chart->legend()->hide(); LEGENDA
    chart->setTitle("Line Chart");
    chart->setAnimationOptions(QChart::AllAnimations);

    // mapper table->chart
    for (int i = 1; i < model->columnCount(); i++) {
        QLineSeries *series = new QLineSeries;
        QVXYModelMapper *mapper = new QVXYModelMapper;
        series->setName(QString("%1").arg(i));
        mapper->setXColumn(0);
        mapper->setYColumn(i);
        mapper->setSeries(series);
        mapper->setModel(model);
        chart->addSeries(series);

        m_series.push_back(series);
        m_mappers.push_back(mapper);
    }

    chart->createDefaultAxes(); // usalo anche quando fai update ez
}


QChart *LineChart::getChart() const
{
    return chart;
}
