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

        for (int j = 0; j < model->columnCount(); j++)
            series->append(QPointF(j, data[i].at(j)));

        addSeries(series);
        m_series.push_back(series);

        series->attachAxis(XAxis);
        series->attachAxis(YAxis);

    }

    LineChart::updateChartView();
}

void LineChart::updateChartView()
{
    //setAnimationOptions(QChart::NoAnimation);
    XAxis->setRange(0, model->columnCount()-1 > 0 ? model->columnCount()-1 : model->columnCount()); // set max and min
    //YAxis->applyNiceNumbers();
    double min = model->min();
    double max = model->max();
    if (min < max) YAxis->setRange(model->min(), model->max());
    else YAxis->setRange(model->min(), model->min()+1);
}

LineChart::LineChart(DataTableModel *c_model)
    : Chart(c_model), XAxis(new QCategoryAxis), YAxis(new QValueAxis)
{

    setTitle("Line Chart");
    setAnimationOptions(QChart::NoAnimation);

    for (int i = 0; i < model->columnCount(); i++)
        XAxis->append(model->getColumnsHeaders().at(i).toString(), i);
    XAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    addAxis(XAxis, Qt::AlignBottom);
    addAxis(YAxis, Qt::AlignLeft);


    LineChart::mapData();

}

void LineChart::insertSeries()
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    QLineSeries *series = new QLineSeries;
    series->setName(model->getRowsHeaders().at(model->rowCount() - 1).toString());

    for (int j = 0; j < model->columnCount(); j++)
    {
        series->append(QPointF(j, data[model->rowCount() - 1].at(j)));
    }

    addSeries(series);
    m_series.push_back(series);

    series->attachAxis(XAxis);
    series->attachAxis(YAxis);

    updateChartView();
}

void LineChart::removeSeries()
{
    setAnimationOptions(QChart::SeriesAnimations);


    if (m_series.back())
        QChart::removeSeries(dynamic_cast<QLineSeries *>(m_series.back()));
    else return;

    m_series.back()->clear();
    delete m_series.back();

    m_series.pop_back();

    updateChartView();
}

void LineChart::insertSeriesValue()
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    int i = 0;
    for (auto it = m_series.begin(); it != m_series.end(); it++)
    {
        (*it)->append(QPointF(model->columnCount() - 1,
                              data[i].at(model->columnCount() - 1)));
        i++;
    }

    XAxis->append(model->getColumnsHeaders().at(model->columnCount() - 1).toString(), model->columnCount() - 1);
    updateChartView();
}

void LineChart::removeSeriesValue()
{
    setAnimationOptions(QChart::SeriesAnimations);

    for (auto it = m_series.begin(); it != m_series.end(); it++)
        (*it)->remove(model->columnCount());

    const QString labelToRemove = XAxis->categoriesLabels().last();
    XAxis->remove(labelToRemove);
    updateChartView();
}

void LineChart::replaceValue(QModelIndex i, QModelIndex j) // i == j
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    const QPointF oldPoint = m_series[i.row()]->at(j.column());
    const QPointF newPoint = QPointF(oldPoint.x(), data.at(i.row()).at(j.column()));
    m_series[i.row()]->replace(oldPoint.x(), oldPoint.y(), newPoint.x(), newPoint.y());
    updateChartView();
}

void LineChart::updateSeriesName(Qt::Orientation orientation, int first, int last) // first == last
{
    setAnimationOptions(QChart::SeriesAnimations);

    if (orientation == Qt::Vertical)
        m_series.at(first)->setName(model->getRowsHeaders().at(last).toString());
    else
        XAxis->replaceLabel(XAxis->categoriesLabels().at(first), model->getColumnsHeaders().at(last).toString());

    updateChartView();
}

void LineChart::clearChart(){
    for(auto it : m_series) {
        it->clear();
        delete it;
    }
    m_series.clear();
    delete XAxis;
    delete YAxis;
}

LineChart::~LineChart(){
    LineChart::clearChart();
}
