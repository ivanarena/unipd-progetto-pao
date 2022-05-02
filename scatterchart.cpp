#include "scatterchart.h"

void ScatterChart::mapData()
{
    vector<vector<double>> data = model->getData();
    for (int i = 0; i < model->rowCount(); i++)
    {
        QScatterSeries *series = new QScatterSeries;
        series->setName(model->getRowsHeaders().at(i).toString());

        for (int j = 0; j < model->columnCount(); j++){
            series->append(QPointF(j, data[i].at(j)));
            series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        }

        addSeries(series);
        ScatterSeries.push_back(series);

        series->attachAxis(XAxis);
        series->attachAxis(YAxis);

    }

    ScatterChart::updateChartView();
}

void ScatterChart::updateChartView()
{
    double min = model->min();
    if (min >= 0)
        YAxis->setRange(0, model->max()*1.3);
    else
        YAxis->setRange(min, model->max()*1.3);
    XAxis->setRange(-0.5, model->columnCount()-0.5); // set max and min
}

ScatterChart::ScatterChart(DataTableModel *c_model)
    : Chart(c_model), XAxis(new QCategoryAxis), YAxis(new QValueAxis)
{

    setTitle("Scatter Chart");
    setAnimationOptions(QChart::NoAnimation);

    for (int i = 0; i < model->columnCount(); i++)
        XAxis->append(model->getColumnsHeaders().at(i).toString(), i);
    XAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    addAxis(XAxis, Qt::AlignBottom);
    addAxis(YAxis, Qt::AlignLeft);


    ScatterChart::mapData();

}

void ScatterChart::insertSeries()
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    QScatterSeries *series = new QScatterSeries;
    series->setName(model->getRowsHeaders().at(model->rowCount() - 1).toString());

    for (int j = 0; j < model->columnCount(); j++)
    {
        series->append(QPointF(j, data[model->rowCount() - 1].at(j)));
        series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    }

    addSeries(series);
    ScatterSeries.push_back(series);

    series->attachAxis(XAxis);
    series->attachAxis(YAxis);

    updateChartView();
}

void ScatterChart::removeSeries()
{
    setAnimationOptions(QChart::SeriesAnimations);

    if (ScatterSeries.back())
        QChart::removeSeries(dynamic_cast<QScatterSeries *>(ScatterSeries.back()));
    else return;

    delete ScatterSeries.back();

    ScatterSeries.pop_back();

    updateChartView();
}

void ScatterChart::insertSeriesValue()
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    int i = 0;
    for (auto it = ScatterSeries.begin(); it != ScatterSeries.end(); it++)
    {
        (*it)->append(QPointF(model->columnCount() - 1,
                              data[i].at(model->columnCount() - 1)));
        i++;
    }

    XAxis->append(model->getColumnsHeaders().at(model->columnCount() - 1).toString(), model->columnCount() - 1);
    updateChartView();
}

void ScatterChart::removeSeriesValue()
{
    setAnimationOptions(QChart::SeriesAnimations);

    for (auto it = ScatterSeries.begin(); it != ScatterSeries.end(); it++)
        (*it)->remove(model->columnCount());

    const QString labelToRemove = *XAxis->categoriesLabels().rbegin();
    XAxis->remove(labelToRemove);
    updateChartView();
}

void ScatterChart::replaceValue(QModelIndex i, QModelIndex j) // i == j
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    const QPointF oldPoint = ScatterSeries[i.row()]->at(j.column());
    const QPointF newPoint = QPointF(oldPoint.x(), data.at(i.row()).at(j.column()));
    setAnimationOptions(QChart::SeriesAnimations);
    ScatterSeries[i.row()]->replace(oldPoint.x(), oldPoint.y(), newPoint.x(), newPoint.y());
    updateChartView();
}

void ScatterChart::updateSeriesName(Qt::Orientation orientation, int first, int last) // first == last
{
    setAnimationOptions(QChart::SeriesAnimations);

    if (orientation == Qt::Vertical)
        ScatterSeries.at(first)->setName(model->getRowsHeaders().at(last).toString());
    else
        XAxis->replaceLabel(XAxis->categoriesLabels().at(first), model->getColumnsHeaders().at(last).toString());
}
