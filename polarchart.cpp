#include "polarchart.h"

void PolarChart::mapData()
{
    vector<vector<double>> data = model->getData();
    for (int i = 0; i < model->rowCount(); i++)
    {
        QSplineSeries *series = new QSplineSeries;
        series->setName(model->getRowsHeaders().at(i).toString());

        for (int j = 0; j < model->columnCount(); j++)
            series->append(QPointF(j, data[i].at(j)));

        QPolarChart::addSeries(series);
        SplineSeries.push_back(series);

        series->attachAxis(XAxis);
        series->attachAxis(YAxis);

    }

    PolarChart::updateChartView();
}

void PolarChart::updateChartView()
{
    XAxis->setRange(0, model->columnCount());
    YAxis->setRange(model->min(), model->max());
}

PolarChart::PolarChart(DataTableModel *c_model)
    : Chart(c_model), XAxis(new QCategoryAxis), YAxis(new QValueAxis)
{
    QPolarChart::setTitle("Polar Chart");
    QPolarChart::setAnimationOptions(QChart::NoAnimation);

    for (int i = 0; i < model->columnCount(); i++)
        XAxis->append(model->getColumnsHeaders().at(i).toString(), i);
    XAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    QPolarChart::addAxis(XAxis, QPolarChart::PolarOrientationAngular);
    QPolarChart::addAxis(YAxis, QPolarChart::PolarOrientationRadial);


    PolarChart::mapData();

}

void PolarChart::insertSeries()
{

    QPolarChart::setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    QSplineSeries *series = new QSplineSeries;
    series->setName(model->getRowsHeaders().at(model->rowCount() - 1).toString());

    for (int j = 0; j < model->columnCount(); j++)
    {
        series->append(QPointF(j, data[model->rowCount() - 1].at(j)));
    }

    QPolarChart::addSeries(series);
    SplineSeries.push_back(series);

    series->attachAxis(XAxis);
    series->attachAxis(YAxis);

    updateChartView();
}

void PolarChart::removeSeries()
{
    QPolarChart::setAnimationOptions(QChart::SeriesAnimations);

    if(!SplineSeries.empty()) {
        delete SplineSeries.back();
        SplineSeries.pop_back();
    }
    else SplineSeries.clear();

    updateChartView();
}

void PolarChart::insertSeriesValue()
{
    QPolarChart::setAnimationOptions(QChart::SeriesAnimations);


    vector<vector<double>> data = model->getData();
    int i = 0;
    for (auto it = SplineSeries.begin(); it != SplineSeries.end(); it++)
    {
        (*it)->append(QPointF(model->columnCount() - 1,
                              data[i].at(model->columnCount() - 1)));
        i++;
    }

    XAxis->append(model->getColumnsHeaders().at(model->columnCount() - 1).toString(), model->columnCount() - 1);
    updateChartView();
}

void PolarChart::removeSeriesValue()
{
    QPolarChart::setAnimationOptions(QChart::SeriesAnimations);


    for (auto it = SplineSeries.begin(); it != SplineSeries.end(); it++)
        (*it)->remove(model->columnCount());

    const QString labelToRemove = *XAxis->categoriesLabels().rbegin();
    XAxis->remove(labelToRemove);
    updateChartView();
}

void PolarChart::replaceValue(QModelIndex i, QModelIndex j)
{
    QPolarChart::setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    const QPointF oldPoint = SplineSeries[i.row()]->at(j.column());
    const QPointF newPoint = QPointF(oldPoint.x(), data.at(i.row()).at(j.column()));
    QPolarChart::setAnimationOptions(QChart::SeriesAnimations);
    SplineSeries[i.row()]->replace(oldPoint.x(), oldPoint.y(), newPoint.x(), newPoint.y());
    updateChartView();
}

void PolarChart::updateSeriesName(Qt::Orientation orientation, int first, int last)
{
    QPolarChart::setAnimationOptions(QChart::SeriesAnimations);

    if (orientation == Qt::Vertical)
        SplineSeries.at(first)->setName(model->getRowsHeaders().at(last).toString());
    else
        XAxis->replaceLabel(XAxis->categoriesLabels().at(first), model->getColumnsHeaders().at(last).toString());
}

void PolarChart::clearChart(){
    for(auto it : SplineSeries){
        it->clear();
        delete it;
    }
    SplineSeries.clear();
    delete XAxis;
    delete YAxis;
}


PolarChart::~PolarChart(){
    clearChart();
}
